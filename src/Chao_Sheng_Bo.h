#ifndef __CHAO_SHENG_BO_H__
#define __CHAO_SHENG_BO_H__

// 引脚定义
#define TRIG_PIN      BSP_IO_PORT_04_PIN_13  // Trig引脚

void Chao_Sheng_Bo_GPT0_Init(void); // 超声波定时器初始化
uint32_t HC_SR04_Measure(void); // 超声波测距

#endif
