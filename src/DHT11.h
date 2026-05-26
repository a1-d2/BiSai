#ifndef __DHT11_H__
#define __DHT11_H__

#include "hal_data.h"

extern uint8_t humidity_integer;//湿度整数
extern uint8_t humidity_decimal;//湿度小数
extern uint8_t temp_integer ;//温度整数
extern uint8_t temp_decimal ;//温度小数

uint8_t DHT11_ReadByte(void);//逐位读取总线数据，拼接为1字节
uint8_t DHT11_Read(void);//读取DHT11温湿度数据并校验

#endif

