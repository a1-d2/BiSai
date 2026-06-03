#include "hal_data.h"
#include "Duo_Ji.h"

void Duo_Ji_Init(void) // 定时器初始化
{
	R_GPT_Open(&g_timer2_ctrl,&g_timer2_cfg);//初始化定时器模块，并应用相关配置
	R_GPT_Start(&g_timer2_ctrl);//定时器开始工作
}

void Duo_Ji_PWM(float Num) // 舵机控制函数
{
    timer_info_t info;
    uint32_t duty_count;
    if(Num > 100)
        Num = 100; // 限制占空比范围为0-100%
    R_GPT_InfoGet(&g_timer2_ctrl,&info); // 获取定时器信息

    duty_count = (uint32_t)( (float)info.period_counts * Num / 100.0f ); // 计算占空比对应的数值

    R_GPT_DutyCycleSet(&g_timer2_ctrl,duty_count,GPT_IO_PIN_GTIOCB); // 设置占空比
}
