/*************************************************************************************************/
/* filename:  config.h
 *
 * content:   Definition of LED matrix parameters
 *
 * CREATED
 * date:      12.02.2015
 * version:   1.1
 * author:    Harald Netzer, FH Technikum Wien, ew13b123
 * remarks:  -
 **************************************************************************************************/

#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#include <XMC4500.h>	// XMC Lib
#include <xmc_gpio.h>	// XMC Lib
#include <xmc_uart.h>	// XMC Lib

#include "L0_gpio_init.h"
#include "L0_uart_init.h"
#include "L0_uart.h"
#include "L0_matrix_driver.h"
#include "L1_image_processing.h"

// ADAFRUIT RGB MATRIX CONFIGURATION
#define MATRIX_HEIGHT 		(32U)
#define MATRIX_WIDTH 		(32U*PANEL_COL)
#define MATRIX_SIZE 		(MATRIX_HEIGHT*MATRIX_WIDTH)
#define SCAN_RATE 			16U

// PANEL COLUMN
#define PANEL_COL			1U				// 2 = 2 panels connected in series
// COLORDEPTH FOR WHOLE DISPLAY
#define COLORDEPTH	 		8U			// 8 Bit colordepth per color and 24Bit in total
// GAMMA CORRECTION
#define GAMMA_COR			1U				// 1 = gamma correction on, 0 = gamma correction off

// define selected display color depth
#if COLORDEPTH == 1
#define RGB_PWM				(2) - 1
#elif COLORDEPTH == 2
#define RGB_PWM				(2*2) - 1
#elif COLORDEPTH == 3
#define RGB_PWM				(2*2*2) - 1
#elif COLORDEPTH == 4
#define RGB_PWM				(2*2*2*2) - 1
#elif COLORDEPTH == 5
#define RGB_PWM				(2*2*2*2*2) - 1
#elif COLORDEPTH == 6
#define RGB_PWM				(2*2*2*2*2*2) - 1
#elif COLORDEPTH == 7
#define RGB_PWM				(2*2*2*2*2*2*2) - 1
#elif COLORDEPTH == 8
#define RGB_PWM				(2*2*2*2*2*2*2*2) - 1
#else
/*
 * !! ERROR !!
 * Not supported colordepth
 */
#endif

// bitmap offset
#define FRAME_OFFSET		8 - COLORDEPTH

#endif /* CONFIG_H_ */
