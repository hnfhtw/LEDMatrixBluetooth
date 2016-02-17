/*************************************************************************************************/
/* filename:  L0_gpio_init.h
 *
 * content:   Function prototype to initialize the GPIO pins used to drive the LED matrix
 *
 * CREATED
 * date:      06.01.2015
 * version:   1.0
 * author:    Harald Netzer, FH Technikum Wien, ew13b123
 * remarks:  -
 **************************************************************************************************/

#ifndef L0_GPIO_INIT_H_
#define L0_GPIO_INIT_H_

#include "config.h"


/**
* @brief Initialization of GPIO pins for LED panel driver
 *    (for Adafruit 32x32 RGB LED Matrix Panel).
 * 		R0,B0,G0 and R1,B1,B1 data pins for RGB color states
 * 		A,B,C,D address selection: 2^4 = 16 [demultiplexer]
 * 		CLK clock for RGB data transfer
 * 		STB strobe - transfer stored RGB states in shift registers to output registers
 * 		OE output enable (active low -> if OE is low, panel is active)
 */
void gpio_init(void);

#endif /* L0_GPIO_INIT_H_ */
