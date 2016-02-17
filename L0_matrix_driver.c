/*************************************************************************************************/
/* filename:  L0_matrix_driver.c
 *
 * content:   Functions to drive the LED matrix
 *
 * CREATED
 * date:      06.01.2015
 * version:   1.0
 * author:    Harald Netzer, FH Technikum Wien, ew13b123
 * remarks:  -
 **************************************************************************************************/

#include "config.h"

extern uint32_t framebuff[COLORDEPTH][MATRIX_SIZE/2];

// Function to show a full frame on the panel
// Drive one address (two rows) 255 times and then move to next address
void RGBMatrixDriver(void) 									
{
	uint16_t i, j = 1, k = 0, l = 0;
	static uint16_t addr = 0;
	
	for(addr=0; addr<SCAN_RATE; addr++)		// outer loop scans through all addresses 
	{																			// (two pixel rows per address)
		
		PORT1->OUT = addr;	// set GPIO pins to the current address 
	  
		for(i=0; i<RGB_PWM; i++)		// inner loop decides based on the BCM if the individual pixels 
		{														// (R, G and B) are 0 or 1 (k=0 is executed 1 time, k=7 is 
			if(i>=j)									// executed 128 times)
			{
				k++;
				l++;
				j = j + (1<<l);
			}
				
			DriveDisplay(&framebuff[k][addr*MATRIX_WIDTH]);	 // load RGB data of two lines in shift regs
			STB_H;	// set STB / LATCH high
			OE_H;		// disable panel by setting OE high
			STB_L;	// falling edge of STB loads values from the shift registers to the output regs
			OE_L;		// enable the panel
		}		
		
		// reset the variables used to determine k
		j=1;
		k=0;
		l=0;
	}
}

/**
 * MACRO PEW includes
 *
 * PORT0->OMR = p_framebuff[]                             
 * writes stored BCM bit map in the output modification register (OMR).
 * The frame buffer already includes a clock toggle therefore only
 * CLK_T [PORT0->OMR=0x10001000U] should be called afterwards to complete a clock period.
 *
 * The loops are unrolled to access more performance. Furthermore the usage of constant
 * values instead a variables reduces memory access and keeps the shifting program sequence short.
 *
 */
#define PEW(__i__) PORT0->OMR = p_framebuff[__i__]; CLK_T;


// shifts the RGB data into the shift registers of the LED panel (via RGB0/1 and SCLK)
void DriveDisplay(uint32_t *p_framebuff) {							

	// loop unrolled for more performance
	if(PANEL_COL >= 1) {
		PEW(0);  PEW(1);  PEW(2);  PEW(3);  PEW(4);  PEW(5);  PEW(6);  PEW(7);
		PEW(8);  PEW(9);  PEW(10); PEW(11); PEW(12); PEW(13); PEW(14); PEW(15);
		PEW(16); PEW(17); PEW(18); PEW(19); PEW(20); PEW(21); PEW(22); PEW(23);
		PEW(24); PEW(25); PEW(26); PEW(27); PEW(28); PEW(29); PEW(30); PEW(31);
	}
	if(PANEL_COL >= 2) {
		p_framebuff += 32;
		PEW(0);  PEW(1);  PEW(2);  PEW(3);  PEW(4);  PEW(5);  PEW(6);  PEW(7);
		PEW(8);  PEW(9);  PEW(10); PEW(11); PEW(12); PEW(13); PEW(14); PEW(15);
		PEW(16); PEW(17); PEW(18); PEW(19); PEW(20); PEW(21); PEW(22); PEW(23);
		PEW(24); PEW(25); PEW(26); PEW(27); PEW(28); PEW(29); PEW(30); PEW(31);
	}
	if(PANEL_COL >= 3) {
		p_framebuff += 32;
		PEW(0);  PEW(1);  PEW(2);  PEW(3);  PEW(4);  PEW(5);  PEW(6);  PEW(7);
		PEW(8);  PEW(9);  PEW(10); PEW(11); PEW(12); PEW(13); PEW(14); PEW(15);
		PEW(16); PEW(17); PEW(18); PEW(19); PEW(20); PEW(21); PEW(22); PEW(23);
		PEW(24); PEW(25); PEW(26); PEW(27); PEW(28); PEW(29); PEW(30); PEW(31);
	}
	if(PANEL_COL >= 4) {
		p_framebuff += 32;
		PEW(0);  PEW(1);  PEW(2);  PEW(3);  PEW(4);  PEW(5);  PEW(6);  PEW(7);
		PEW(8);  PEW(9);  PEW(10); PEW(11); PEW(12); PEW(13); PEW(14); PEW(15);
		PEW(16); PEW(17); PEW(18); PEW(19); PEW(20); PEW(21); PEW(22); PEW(23);
		PEW(24); PEW(25); PEW(26); PEW(27); PEW(28); PEW(29); PEW(30); PEW(31);
	}
	if(PANEL_COL >= 5) {
		p_framebuff += 32;
		PEW(0);  PEW(1);  PEW(2);  PEW(3);  PEW(4);  PEW(5);  PEW(6);  PEW(7);
		PEW(8);  PEW(9);  PEW(10); PEW(11); PEW(12); PEW(13); PEW(14); PEW(15);
		PEW(16); PEW(17); PEW(18); PEW(19); PEW(20); PEW(21); PEW(22); PEW(23);
		PEW(24); PEW(25); PEW(26); PEW(27); PEW(28); PEW(29); PEW(30); PEW(31);
	}
}
