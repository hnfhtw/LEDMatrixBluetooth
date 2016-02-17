/*************************************************************************************************/
/* filename:  L1_image_processing.c
 *
 * content:   Functions to create, clear and update the framebuffer
 *
 * CREATED
 * date:      06.01.2015
 * version:   1.0
 * author:    Harald Netzer, FH Technikum Wien, ew13b123
 * remarks:  -
 **************************************************************************************************/

#include "config.h"

static unsigned int width = 32;
static unsigned int height = 32;

// lookup table for gamma correction
const uint8_t gamma_map[] = {	
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255
};

// two dimensional framebuffer, dimension 1: BCM, dimension 2: Port 0 OMR values to drive panel 
uint32_t framebuff[COLORDEPTH][MATRIX_SIZE/2];

// for gamma correction using lookup table gamma_map[]
uint8_t gamma_cor(uint8_t value) {	
	if(value == 0) {
		return 0;
	} else if(value == 255U) {
		return value;
	} else if(value <= gamma_map[value]) {
		return gamma_map[value];
	} else if(value == gamma_map[value]) {
		return gamma_map[value - 1];
	} else if(value > gamma_map[value] && value <= 254U) {
		return gamma_map[value + 1];
	} else {
		// error loop
		while(1);
	}
}

// prepare empty framebuffer
void initEmptyPanel(void) {
	uint32_t i;
	uint8_t j;
	
	/* set frame buffer zero and write clock state */
	for(j=0;j<COLORDEPTH;j++) {
		for(i=0;i<MATRIX_SIZE/2;i++) {
			framebuff[j][i] = CLK|0x0FFF0000;							 
		}
	}
}

// update one pixel in the framebuffer
void framebuffer_update_1px(uint8_t x, uint8_t y, uint8_t R, uint8_t G, uint8_t B) {
	uint32_t i;
	uint32_t m_width = MATRIX_WIDTH;
	uint8_t j;
	uint8_t k = 1;
	uint32_t bit_buff;
	uint8_t color_buff_top[3];
	uint8_t color_buff_bot[3];

	/* BCM bit splitting */
	for(j=0;j<COLORDEPTH;j++) {
		
		// BCM prove
		k = 1<<(j+FRAME_OFFSET);
		
			bit_buff = 0;
		
			if(y >= 16)
				i = x + (y-16)*m_width;
			else
				i = x + y*m_width;
			
			
			// delete current color of this pixel (x, y) -> set output pins to zero
			if(y < height/2)
			{			
			framebuff[j][i] &= ~(1 << 11);		// R_top - clear SET bit
			framebuff[j][i] &= ~(1 << 10);		// G_top - clear SET bit
			framebuff[j][i] &= ~(1 << 9);			// B_top - clear SET bit
			framebuff[j][i] |= (1 << 27);			// R_top - set CLEAR bit
			framebuff[j][i] |= (1 << 26);			// G_top - set CLEAR bit
			framebuff[j][i] |= (1 << 25);			// B_top - set CLEAR bit
			}
			if(y >= height/2)
			{			
			framebuff[j][i] &= ~(1 << 8);
			framebuff[j][i] &= ~(1 << 7);
			framebuff[j][i] &= ~(1 << 6);
			framebuff[j][i] |= (1 << 24);
			framebuff[j][i] |= (1 << 23);
			framebuff[j][i] |= (1 << 22);
			}
					
			// continue the loop if the width of the image (width) or the matrix (MATRIX_WIDTH) is reached
			if(x >= width || x > MATRIX_WIDTH) {
				continue;
			}
			// break the loop if the height of the image (height) or the matrix (MATRIX_HEIGHT) is reached
			if(y >= height || y > MATRIX_HEIGHT) {
				break;
			}

			
			/* gamma correction */
			if(GAMMA_COR == true) {
				if(y < height/2)
				{
				color_buff_top[0] = gamma_cor(R);
				color_buff_top[1] = gamma_cor(G);
				color_buff_top[2] = gamma_cor(B);
				}
				if(y >= height/2)
				{
				color_buff_bot[0] = gamma_cor(R);
				color_buff_bot[1] = gamma_cor(G);
				color_buff_bot[2] = gamma_cor(B);
				}
			} else {
				if(y < height/2)
				{
				color_buff_top[0] = R;
				color_buff_top[1] = G;
				color_buff_top[2] = B;
				}
				if(y >= height/2)
				{
				color_buff_bot[0] = R;
				color_buff_bot[1] = G;
				color_buff_bot[2] = B;
				}
			}
			
			if(y < height/2)
			{			
					// TOP 16 lines
					// RED
					if((color_buff_top[0] & k) == k) {
						bit_buff |= RED_TOP;
					}

					// GREEN
					if((color_buff_top[1] & k) == k) {
						bit_buff |= GREEN_TOP;
					}

					// BLUE
					if((color_buff_top[2] & k) == k) {
						bit_buff |= BLUE_TOP;
					}
			}

			if(y >= height/2)
			{
					// BOTTOM 16 lines
					// RED
					if((color_buff_bot[0] & k) == k) {
						bit_buff |= RED_BOTTOM;
					}

					// GREEN
					if((color_buff_bot[1] & k) == k) {
						bit_buff |= GREEN_BOTTOM;
					}

					// BLUE
					if((color_buff_bot[2] & k) == k) {
						bit_buff |= BLUE_BOTTOM;
					}
			}

			/**
			 * @brief Prepare state for OMR.
			 * OMR design
			 * 32bit = [HIGH[16bit : clear pin]][LOW[16bit : set pin]]
			 */
			// write "set" states in bit space for panel chain 0
			framebuff[j][i] |= bit_buff;
			// negate state and write it in clear bit space of OMR
			framebuff[j][i] &= (~framebuff[j][i]<<16)|(uint16_t)framebuff[j][i]|CLK;
	}
}
