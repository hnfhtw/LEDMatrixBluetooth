/*************************************************************************************************/
/* filename:  L0_matrix_driver.h
 *
 * content:   Definition of GPIO pins to drive the LED matrix
 *
 * CREATED
 * date:      06.01.2015
 * version:   1.0
 * author:    Harald Netzer, FH Technikum Wien, ew13b123
 * remarks:  -
 **************************************************************************************************/

#ifndef L0_MATRIX_DRIVER_H_
#define L0_MATRIX_DRIVER_H_

#include "config.h"

// GPIO Pin bitmasks for LED panel driver
#define CLK 				0x10001000U	// OMR bitmask to toggle CLK pin

#define RED_TOP			0x800			// Pin P0.11 (0x800 = 2^11 = 2048)
#define GREEN_TOP		0x400			// Pin P0.10 (0x400 = 2^10 = 1024)
#define BLUE_TOP		0x200			// Pin P0.9 (0x200 = 2^9 = 512)

#define RED_BOTTOM		0x100		// Pin P0.8 (0x100 = 2^8 = 256)
#define GREEN_BOTTOM	0x80		// Pin P0.7 (0x80 = 2^7 = 128)
#define BLUE_BOTTOM		0x40		// Pin P0.6 (0x40 = 2^6 = 64)

// Pin macros to toggle, reset and set STB, CLK and OE pins
#define STB_T				(PORT1->OMR=0x00100010U)	// Toggle pin P1.4
#define STB_L				(PORT1->OMR=0x00100000U)	// Reset pin P1.4
#define STB_H				(PORT1->OMR=0x00000010U)	// Set pin P1.4
#define CLK_T 			(PORT0->OMR=0x10001000U)	// Toggle pin P0.12
#define OE_T				(PORT1->OMR=0x01000100U)	// Toggle pin P1.8
#define OE_L 				(PORT1->OMR=0x01000000U)	// Reset pin P1.8
#define OE_H 				(PORT1->OMR=0x00000100U)	// Set pin P1.8

/**
 * @note This function writes one frame with 24bit color depth
 */
void RGBMatrixDriver(void);

/**
 * @note This function filles the shift registers of one address
 */
void DriveDisplay(uint32_t *p_framebuff);

#endif /* L0_MATRIX_DRIVER_H_ */
