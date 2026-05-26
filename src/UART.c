#include "hal_data.h"

void UART0_Init(void) // 串口初始化
{
	fsp_err_t err = FSP_SUCCESS;
    err = R_SCI_UART_Open(&g_uart0_ctrl, &g_uart0_cfg);
    assert(FSP_SUCCESS == err);
}

