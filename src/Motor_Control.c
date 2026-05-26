#include "hal_data.h"
#include "Motor_Control.h"

void Motor_PWM_Init(void)//电机初始化
{
	R_GPT_Open(&g_timer3_ctrl,&g_timer3_cfg);//初始化定时器模块，并应用相关配置
	R_GPT_Open(&g_timer1_ctrl,&g_timer1_cfg);

	R_GPT_Start(&g_timer3_ctrl);//定时器开始工作
	R_GPT_Start(&g_timer1_ctrl);
}


void Motor_Left_Speed(uint8_t Num)//左电机速度调节
{
    timer_info_t info;
    uint32_t duty_count;
    if(Num > 100)
        Num = 100;// 限制占空比范围为0~100%
    R_GPT_InfoGet(&g_timer3_ctrl,&info);// 获取定时器信息

    duty_count = (info.period_counts * Num) / 100;// 计算占空比对应的计数值

    R_GPT_DutyCycleSet(&g_timer3_ctrl,duty_count,GPT_IO_PIN_GTIOCA);// 设置占空比
}


void Motor_Right_Speed(uint8_t Num)//右电机速度调节
{
    timer_info_t info;
    uint32_t duty_count;
    if(Num > 100)
        Num = 100;// 限制占空比范围为0~100%
    R_GPT_InfoGet(&g_timer1_ctrl,&info);// 获取定时器信息

    duty_count = (info.period_counts * Num) / 100;// 计算占空比对应的计数值

    R_GPT_DutyCycleSet(&g_timer1_ctrl,duty_count,GPT_IO_PIN_GTIOCB);// 设置占空比
}

