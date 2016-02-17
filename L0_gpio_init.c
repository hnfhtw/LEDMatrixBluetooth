/*************************************************************************************************/
/* filename:  L0_gpio_init.c
 *
 * content:   Function to initialize the GPIO pins used to drive the LED matrix
 *
 * CREATED
 * date:      06.01.2015
 * version:   1.0
 * author:    Harald Netzer, FH Technikum Wien, ew13b123
 * remarks:  -
 **************************************************************************************************/

#include "config.h"

// Initialization of GPIO pins for LED panel driver using XMC Lib functions
void gpio_init(void) 
{	
	XMC_GPIO_CONFIG_t config_out = {
			XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
			XMC_GPIO_OUTPUT_LEVEL_LOW,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE
	};
	
		XMC_GPIO_CONFIG_t config_out1 = {
			XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
			XMC_GPIO_OUTPUT_LEVEL_HIGH,
			XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE
	};

	// Port 1:
	// Address lines A to D (A0 to A3)
	XMC_GPIO_Init(XMC_GPIO_PORT1,0,&config_out); 	// A
	XMC_GPIO_Init(XMC_GPIO_PORT1,1,&config_out);	// B
	XMC_GPIO_Init(XMC_GPIO_PORT1,2,&config_out); 	// C
	XMC_GPIO_Init(XMC_GPIO_PORT1,3,&config_out); 	// D
	
	// Strobe pin - on falling edge the values from shift registers are transfered to output registers
	XMC_GPIO_Init(XMC_GPIO_PORT1,4,&config_out);	// STB
	
	// Output enable pin - OE = low enables the panel
	XMC_GPIO_Init(XMC_GPIO_PORT1,8,&config_out1);		// OE		
	
	// Port 0
	// Clock generating for shift register
	XMC_GPIO_Init(XMC_GPIO_PORT0,12,&config_out); 	// CLK
	
	// Panel LINE 0 Data pins RGB 0
	XMC_GPIO_Init(XMC_GPIO_PORT0,11,&config_out);	// RED
	XMC_GPIO_Init(XMC_GPIO_PORT0,10,&config_out); 	// GREEN
	XMC_GPIO_Init(XMC_GPIO_PORT0,9,&config_out); 	// BLUE
	// Panel LINE 0 Data pins RGB 1
	XMC_GPIO_Init(XMC_GPIO_PORT0,8,&config_out); 	// RED
	XMC_GPIO_Init(XMC_GPIO_PORT0,7,&config_out);  	// GREEN
	XMC_GPIO_Init(XMC_GPIO_PORT0,6,&config_out);  	// BLUE
	
	// Panel LINE 1 Data pins RGB 0 - currently not used
	XMC_GPIO_Init(XMC_GPIO_PORT0,5,&config_out); 	// RED
	XMC_GPIO_Init(XMC_GPIO_PORT0,4,&config_out); 	// GREEN
	XMC_GPIO_Init(XMC_GPIO_PORT0,3,&config_out); 	// BLUE
	// Panel LINE 1 Data pins RGB 1 - currently not used
	XMC_GPIO_Init(XMC_GPIO_PORT0,2,&config_out); 	// RED
	XMC_GPIO_Init(XMC_GPIO_PORT0,1,&config_out);  	// GREEN
	XMC_GPIO_Init(XMC_GPIO_PORT0,0,&config_out);  	// BLUE
}
