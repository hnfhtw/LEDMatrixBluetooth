/*************************************************************************************************/
/* filename:  L0_uart_init.h
 *
 * content:   Function prototype to initialize the UART
 *
 * CREATED
 * date:      06.01.2015
 * version:   1.0
 * author:    Harald Netzer, FH Technikum Wien, ew13b123
 * remarks:  -
 **************************************************************************************************/


#ifndef L0_UART_INIT_H_
#define L0_UART_INIT_H_

#include "config.h"

#define UART_TX P5_1
#define UART_RX P1_5
#define UART_0_RX_HANDLER  IRQ_Hdlr_84

void uart_init(void);

#endif /* L0_UART_INIT_H_ */
