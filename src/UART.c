#include "hal_data.h"

volatile bool uart_complete_flag = false;

void UART0_Init(void) // 串口初始化
{
	fsp_err_t err = FSP_SUCCESS;
    err = R_SCI_UART_Open(&g_uart0_ctrl, &g_uart0_cfg);
    assert(FSP_SUCCESS == err);
}

void uart0_Callback(uart_callback_args_t * p_args)
{
	if(UART_EVENT_TX_COMPLETE == p_args -> event) // 串口数据发送完成
	{
		uart_complete_flag = true;
	}
}

