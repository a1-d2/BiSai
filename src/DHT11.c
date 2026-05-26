#include "hal_data.h"
#include "DHT11.h"

#define 	PIN		BSP_IO_PORT_02_PIN_01	//引脚替换

uint8_t DHT11_ReadByte(void)//逐位读取总线数据，拼接为1字节
{
    bsp_io_level_t state;				 // 定义变量，存储引脚电平状态
    uint8_t ans=0,ind;					// ans：存储最终读到的1字节；ind：循环计数器（0-7，读8位）
    for (ind=0;ind<8;ind++)
    {
        ans<<=1;						// ans左移1位，腾出最低位存新读的位
        do
        {
            R_IOPORT_PinRead(&g_ioport_ctrl, PIN, &state);
        }while(state==BSP_IO_LEVEL_LOW);//循环等待，直至识别低电平，开始接受数据
        R_BSP_SoftwareDelay(54, BSP_DELAY_UNITS_MICROSECONDS); //延时54us
        R_IOPORT_PinRead(&g_ioport_ctrl, PIN, &state);
        if (state==BSP_IO_LEVEL_HIGH)
            ans |= 1;				// 把ans的最低位设为1
        do{
            R_IOPORT_PinRead(&g_ioport_ctrl, PIN, &state);
        }while(state==BSP_IO_LEVEL_HIGH);
    }
    return ans;
}


 uint8_t humidity_integer;//湿度整数
 uint8_t humidity_decimal;//湿度小数
 uint8_t temp_integer ;//温度整数
 uint8_t temp_decimal ;//温度小数
// uint8_t dht11_check ;//校验值


uint8_t DHT11_Read(void)//读取DHT11温湿度数据并校验
{
    uint8_t dht11_check=0;
    bsp_io_level_t state;
    uint16_t delay_dht=0xffff;

    //DHT启动时序DATA设为输出状态
    R_IOPORT_PinCfg(&g_ioport_ctrl,PIN,((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_HIGH));
    //发送18ms低电平
    R_IOPORT_PinWrite(&g_ioport_ctrl, PIN, BSP_IO_LEVEL_LOW);
    R_BSP_SoftwareDelay(20, BSP_DELAY_UNITS_MILLISECONDS); //延时20ms
    //再输出20-40us高电平
    R_IOPORT_PinWrite(&g_ioport_ctrl, PIN, BSP_IO_LEVEL_HIGH);
//    R_BSP_SoftwareDelay(30, BSP_DELAY_UNITS_MICROSECONDS); //延时30us
    //DATA设为输入状态
    R_IOPORT_PinCfg(&g_ioport_ctrl,PIN,((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT));
    //等待DATA响应低电平,后变为高电平
    do{
        delay_dht--;
        if (!delay_dht)
            return 0;
        R_IOPORT_PinRead(&g_ioport_ctrl, PIN, &state);
    }while(state==BSP_IO_LEVEL_HIGH);
    do{
        delay_dht--;
        if (!delay_dht)
            return 0;
        R_IOPORT_PinRead(&g_ioport_ctrl, PIN, &state);
    }while(state==BSP_IO_LEVEL_LOW);
    do{
        delay_dht--;
        if (!delay_dht)
            return 0;
        R_IOPORT_PinRead(&g_ioport_ctrl, PIN, &state);
    }while(state==BSP_IO_LEVEL_HIGH);

    humidity_integer = DHT11_ReadByte();
    humidity_decimal = DHT11_ReadByte();
    temp_integer = DHT11_ReadByte();
    temp_decimal = DHT11_ReadByte();
    dht11_check = DHT11_ReadByte();
    if (((humidity_integer+humidity_decimal+temp_integer+temp_decimal)&0xff)==dht11_check)
        return 1;
    else
        return 0;
}

