/*************************************************************************************************/
/* filename:  L0_uart_init.c
 *
 * content:   Functions to initialize the UART
 *
 * CREATED
 * date:      06.01.2015
 * version:   1.0
 * author:    Harald Netzer, FH Technikum Wien, ew13b123
 * remarks:  -
 **************************************************************************************************/

#include "config.h"

void uart_init(void) 
{
		XMC_GPIO_CONFIG_t uart_tx =
		{
			.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT1,		
			.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
			.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
		};

		XMC_GPIO_CONFIG_t uart_rx =
		{
			.mode = XMC_GPIO_MODE_INPUT_TRISTATE
		};
		
		XMC_UART_CH_CONFIG_t uart_config =
		{
			.baudrate = 115200U,
			.data_bits = 8U,
			.frame_length = 8U,
			.stop_bits = 1U,		
			.parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
		};
		
		XMC_GPIO_Init(UART_TX,&uart_tx);
		XMC_GPIO_Init(UART_RX,&uart_rx);
		
		XMC_UART_CH_Init(XMC_UART0_CH0, &uart_config);
		
		// use whole available FIFO for the receive path
		XMC_USIC_CH_RXFIFO_Configure(XMC_UART0_CH0, 0U, XMC_USIC_CH_FIFO_SIZE_64WORDS, 63U);		
			
		XMC_UART_CH_SetInputSource(XMC_UART0_CH0, XMC_UART_CH_INPUT_RXD, USIC0_C0_DX0_P1_5);
		XMC_UART_CH_Start(XMC_UART0_CH0);
}


