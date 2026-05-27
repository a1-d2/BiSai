#ifndef __MOTOR_CONTROL_H__
#define __MOTOR_CONTROL_H__

#include "hal_data.h"

//R_BSP_SoftwareDelay(915,BSP_DELAY_UNITS_MILLISECONDS);//左转90度

void Motor_PWM_Init(void);//电机初始化
void Motor_Left_Speed(uint8_t Num);//左电机速度调节
void Motor_Right_Speed(uint8_t Num);//右电机速度调节


//配置电机驱动引脚

/*	IN1：1，IN2：0。左电机前进
 *	IN1：0，IN2：1。左电机后退
 *	IN1：0，IN2：0。左电机停止
 *	右电机同理
 */

#define ENA_PIN    BSP_IO_PORT_04_PIN_03//左边电机使能引脚，注：PWM模式下此引脚接单片机PWM输出引脚
#define IN1_PIN    BSP_IO_PORT_00_PIN_01//IN1 -> 001
#define IN2_PIN    BSP_IO_PORT_00_PIN_02//IN2 -> 002
#define IN3_PIN    BSP_IO_PORT_00_PIN_03//IN3 -> 003
#define IN4_PIN    BSP_IO_PORT_00_PIN_04//IN4 -> 004
#define ENB_PIN    BSP_IO_PORT_04_PIN_06//右边电机使能引脚，注：PWM模式下此引脚接单片机PWM输出引脚

// ===================== 小车整体动作 =====================
#define Car_Forward() \
    do { \
        Motor_L_Forward(); \
        Motor_R_Forward(); \
    } while(0)//小车前进

#define Car_Backward() \
    do { \
        Motor_L_Backward(); \
        Motor_R_Backward(); \
    } while(0)//小车后退
	
#define Car_Turn_L() \
    do { \
        Motor_L_Backward(); \
        Motor_R_Forward(); \
    } while(0)//小车左转

#define Car_Turn_R() \
    do { \
        Motor_L_Forward(); \
        Motor_R_Backward(); \
    } while(0)//小车右转

#define Car_Stop() \
    do { \
        Motor_L_Stop(); \
        Motor_R_Stop(); \
    } while(0)//小车停止


//操作宏定义	

#define Motor_L_Forward()   R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_01, BSP_IO_LEVEL_HIGH);  \
							R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_02, BSP_IO_LEVEL_LOW)
							
#define Motor_L_Backward()  R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_01, BSP_IO_LEVEL_LOW);   \
							R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_02, BSP_IO_LEVEL_HIGH)
							
#define Motor_L_Stop()      R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_01, BSP_IO_LEVEL_LOW);   \
							R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_02, BSP_IO_LEVEL_LOW)

#define Motor_R_Forward()   R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_03, BSP_IO_LEVEL_HIGH);  \
							R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_04, BSP_IO_LEVEL_LOW)
							
#define Motor_R_Backward()  R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_03, BSP_IO_LEVEL_LOW);   \
							R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_04, BSP_IO_LEVEL_HIGH)
							
#define Motor_R_Stop()      R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_03, BSP_IO_LEVEL_LOW);   \
							R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_04, BSP_IO_LEVEL_LOW)

#endif

