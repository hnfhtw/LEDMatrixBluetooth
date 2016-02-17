/*************************************************************************************************/
/* filename:  main.c
 *
 * content:   Main loop of the LED matrix driver application
 *
 * CREATED
 * date:      02.02.2015
 * version:   1.0
 * author:    Harald Netzer, FH Technikum Wien, ew13b123
 * remarks:  -
 **************************************************************************************************/
  
#include "config.h"

int main(void)
{
 	gpio_init();		// init GPIO settings for LED matrix driver
	uart_init();		// init UART settings
 		
	initEmptyPanel();	// prepare cleared frame buffer
		
	while(1) 				// main loop
	{				
		getPixelsFromUART();		// get a UART packet and update framebuffer, if start streaming command 
														// is received -> receive full image, if clear panel command is received 
														// -> clear frame buffer
		
		RGBMatrixDriver();			// drive display to show one complete frame
	}
	return 0;
}
