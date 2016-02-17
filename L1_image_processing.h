/*************************************************************************************************/
/* filename:  L1_image_processing.h
 *
 * content:   Function prototypes to create and update the framebuffer
 *
 * CREATED
 * date:      06.01.2015
 * version:   1.0
 * author:    Harald Netzer, FH Technikum Wien, ew13b123
 * remarks:  -
 **************************************************************************************************/

#ifndef L1_IMAGE_PROCESSING_H_
#define L1_IMAGE_PROCESSING_H_

#include "config.h"

/**
 * @note This function does the gamma correction with the lookuptable
 * defined in L1_image_processing.c
 *
 * @param value to correct
 * @return gamma corrected value
 */
uint8_t gamma_cor(uint8_t value);

// set framebuffer zero and write clock states
void initEmptyPanel(void);

// update one pixel in the framebuffer
void framebuffer_update_1px(uint8_t x, uint8_t y, uint8_t R, uint8_t G, uint8_t B);

#endif /* L1_IMAGE_PROCESSING_H_ */
