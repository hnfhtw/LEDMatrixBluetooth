/*************************************************************************************************/
/* filename:  L0_uart.h
 *
 * content:   Function prototypes to communicate via UART
 *
 * CREATED
 * date:      12.02.2015
 * version:   1.1
 * author:    Harald Netzer, FH Technikum Wien, ew13b123
 * remarks:  -
 **************************************************************************************************/
 
 #ifndef L0_UART_H_
#define L0_UART_H_

#include "config.h"

// get a UART packet and update framebuffer
// if clear panel command is received -> clear frame buffer
// if start streaming command is received -> receive full image and update frame buffer
void getPixelsFromUART(void);

#endif /* L0_UART_H_ */
