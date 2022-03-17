/*
 * helper_functions.h
 *
 *  Created on: Oct 28, 2020
 *      Author: suris
 */

#ifndef INC_HELPER_FUNCTIONS_H_
#define INC_HELPER_FUNCTIONS_H_

#include "stm32f769xx.h"
#include "stm32f7xx_hal.h"

extern JPEG_YCbCrToRGB_Convert_Function pConvert_Function;

void printPutty(uint8_t *raw_addr, JPEG_ConfTypeDef *jpeg_info);
void printPutty2D(uint8_t *base_addr, uint16_t x, uint16_t y, JPEG_ConfTypeDef *jpeg_info);
uint8_t *colorConversion(uint8_t *jpeg_addr, uint32_t num_bytes);

#endif /* INC_HELPER_FUNCTIONS_H_ */
