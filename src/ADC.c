#include "hal_data.h"
#include "ADC.h"

uint16_t adc_raw[8];              // ADC原始值（0~4095）
float adc_voltage[8];           // 转换后的电压值
const uint8_t adc_channel_list[8] = {0,1,5,6,7,8,12,13}; // 读取通道号
fsp_err_t err = FSP_SUCCESS;       // 错误判断的变量
const uint8_t ADC_Read_err[] = "ADC_Read_err";
const uint8_t ADC_scanstart_err[] = "ADC_scanstart_err";

volatile bool scan_complete_flag = false; // ADC扫描完成标志位

void adc0_Callback(adc_callback_args_t *p_args) // ADC读取结束之后会调用回调函数，并且把scan_complete_flag 给至true，代表ADC读取结束
{
	// 宏将告诉编译器回调函数不使用参数 p_args，从而避免编译器发出警告
	// FSP_PARAMETER_NOT_USED(p_args);
	if(ADC_EVENT_SCAN_COMPLETE == p_args -> event) // 扫描完成
	{
		scan_complete_flag = true;
	}
}

// 启动ADC扫描并读取8路数据
void adc_scan_start(void)
{
	err = R_ADC_ScanStart(&g_adc0_ctrl); // 开启一次ADC0扫描
	if(FSP_SUCCESS != err)
	{
		R_SCI_UART_Write(&g_uart0_ctrl,ADC_scanstart_err,sizeof(ADC_scanstart_err)-1);
		return;
	}
	scan_complete_flag = false;         // 把扫描完成标志位至false
	while(!scan_complete_flag);        // 等待扫描完成
    // 读取8个通道的结果
    for(uint8_t i = 0; i < 8; i++)
    {
        err = R_ADC_Read(&g_adc0_ctrl, adc_channel_list[i], &adc_raw[i]);
		if(FSP_SUCCESS != err) // 异常时输出错误信息
		{
			R_SCI_UART_Write(&g_uart0_ctrl,ADC_Read_err,sizeof(ADC_Read_err)-1);
			return;
		}
		if(0 == i)
		{
			adc_raw[i] = adc_raw[i] + 320;
		}
        adc_voltage[i] = (adc_raw[i] / 4095.0f) * 3.3f; // 转换为实际电压值（公式：电压 = (ADC值/4095)*3.3V）
    }
}

