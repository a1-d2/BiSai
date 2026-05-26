#include "hal_data.h"
#include "Chao_Sheng_Bo.h"

// 超声波捕获全局变量
uint32_t echo_start = 0;    // 上升沿：Echo开始时间
uint32_t echo_end = 0;     // 下降沿：Echo结束时间
volatile uint8_t capture_flag = 0; // 捕获完成标志 0=未完成 1=完成



void g_timer0_callback(timer_callback_args_t *p_args)  // GPT0 中断回调函数
{
    // 捕获A：Echo 上升沿（高电平开始）
    if(p_args->event == TIMER_EVENT_CAPTURE_A)
    {
        echo_start = p_args->capture;  // 记录开始时间
    }
    else if(p_args->event == TIMER_EVENT_CAPTURE_A) // 捕获B：Echo 下降沿（高电平结束）
    {
        echo_end = p_args->capture;    // 记录结束时间
        capture_flag = 1;              // 标记捕获完成
    }
}


void Chao_Sheng_Bo_GPT0_Init(void) // 超声波定时器初始化
{
	R_GPT_Open(&g_timer0_ctrl,&g_timer0_cfg);//初始化定时器模块，并应用相关配置
	R_GPT_Start(&g_timer0_ctrl);//定时器开始工作
}


uint32_t HC_SR04_Measure(void) // 超声波测距
{
    // 重置标志
    capture_flag = 0; // 捕获完成标志 0 = 未完成 ，1 = 完成
    echo_start = 0;  // 上升沿：Echo开始时间
    echo_end = 0;   // 下降沿：Echo结束时间

    // 发送Trig触发信号（10us 高电平）
    R_IOPORT_PinWrite(&g_ioport_ctrl, TRIG_PIN, BSP_IO_LEVEL_HIGH);
    R_BSP_SoftwareDelay(11,BSP_DELAY_UNITS_MICROSECONDS);
    R_IOPORT_PinWrite(&g_ioport_ctrl, TRIG_PIN, BSP_IO_LEVEL_LOW);

    // 等待捕获完成（超时防止卡死）
    uint32_t timeout = 0;
    while(capture_flag == 0 && timeout < 30000)
    {
        timeout++;
		R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MICROSECONDS);
    }

    // 4. 计算距离
    if(timeout < 30000)
    {
		// Echo时间
		uint32_t echo_cnt = echo_end - echo_start;  

		// 公式：距离×100 (0.01cm)，纯整数，两位小数精度
		uint32_t distance_x100 = (echo_cnt * 17) / 100;  
		return distance_x100;
    }
    else
    {
		return 0;
    }
}
