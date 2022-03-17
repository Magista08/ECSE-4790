/*
 * helper_functions.c
 *
 *  Created on: Oct 28, 2020
 *      Author: suris
 */

#include "stm32f769i_discovery_lcd.h"
#include "jpeg_utils.h"

#include "helper_functions.h"
#include "init.h"

JPEG_YCbCrToRGB_Convert_Function pConvert_Function;

uint8_t *colorConversion(uint8_t *jpeg_addr, uint32_t num_bytes)
{
	uint8_t *raw_out_buf = jpeg_addr + num_bytes;
	uint32_t total_raw_data;
	pConvert_Function(jpeg_addr, raw_out_buf, 0, num_bytes, &total_raw_data);

	return raw_out_buf;
}

void printPutty(uint8_t *raw_addr, JPEG_ConfTypeDef *jpeg_info)
{
	uint32_t *raw_out_words = (uint32_t *)raw_addr;
	uint32_t width = jpeg_info->ImageWidth;
	uint32_t height = jpeg_info->ImageHeight;

	if(jpeg_info->ChromaSubsampling == JPEG_420_SUBSAMPLING)
	{
		if((jpeg_info->ImageWidth % 16) != 0)
			width += (16 - (jpeg_info->ImageWidth % 16));

		if((jpeg_info->ImageHeight % 16) != 0)
			height += (16 - (jpeg_info->ImageHeight % 16));
	}

	if(jpeg_info->ChromaSubsampling == JPEG_422_SUBSAMPLING)
	{
		if((jpeg_info->ImageWidth % 16) != 0)
			width += (16 - (jpeg_info->ImageWidth % 16));

		if((jpeg_info->ImageHeight % 8) != 0)
			height += (8 - (jpeg_info->ImageHeight % 8));
	}

	if(jpeg_info->ChromaSubsampling == JPEG_444_SUBSAMPLING)
	{
		if((jpeg_info->ImageWidth % 8) != 0)
			width += (8 - (jpeg_info->ImageWidth % 8));

		if((jpeg_info->ImageHeight % 8) != 0)
			height += (8 - (jpeg_info->ImageHeight % 8));
	}

    printf("\033[2J\033[;H"); // Erase screen & move cursor to home position
    printf("\033c"); // Reset device
    fflush(stdout);
	for (int i = 0; i < width*height; i++)
	{
		uint8_t b = ((*(raw_out_words + i)) & 0x000000ff);
		uint8_t g = ((*(raw_out_words + i)) & 0x0000ff00) >> 8;
		uint8_t r = ((*(raw_out_words + i)) & 0x00ff0000) >> 16;
		//uint8_t a = ((*(raw_out_words + i)) & 0xff000000) >> 24;

		if (i % width == 0)
		{
			if (i > 0)
			{
				printf("\r\n");
			}
		}

		printf("\033[48;2;%d;%d;%dm", r, g, b);
		printf(" ");

		HAL_Delay(2);
	}
	printf("\033[0m");
	printf("\r\n");
}

void printPutty2D(uint8_t *base_addr, uint16_t x, uint16_t y, JPEG_ConfTypeDef *jpeg_info)
{
	uint32_t width = jpeg_info->ImageWidth;
	uint32_t height = jpeg_info->ImageHeight;


	if(jpeg_info->ChromaSubsampling == JPEG_420_SUBSAMPLING)
	{
		if((jpeg_info->ImageWidth % 16) != 0)
			width += (16 - (jpeg_info->ImageWidth % 16));

		if((jpeg_info->ImageHeight % 16) != 0)
			height += (16 - (jpeg_info->ImageHeight % 16));
	}

	if(jpeg_info->ChromaSubsampling == JPEG_422_SUBSAMPLING)
	{
		if((jpeg_info->ImageWidth % 16) != 0)
			width += (16 - (jpeg_info->ImageWidth % 16));

		if((jpeg_info->ImageHeight % 8) != 0)
			height += (8 - (jpeg_info->ImageHeight % 8));
	}

	if(jpeg_info->ChromaSubsampling == JPEG_444_SUBSAMPLING)
	{
		if((jpeg_info->ImageWidth % 8) != 0)
			width += (8 - (jpeg_info->ImageWidth % 8));

		if((jpeg_info->ImageHeight % 8) != 0)
			height += (8 - (jpeg_info->ImageHeight % 8));
	}


	uint32_t * start = (uint32_t *)(base_addr + (y * BSP_LCD_GetXSize() + x) * 4);
	int row_offset = 0;

    printf("\033[2J\033[;H"); // Erase screen & move cursor to home position
    printf("\033c"); // Reset device
    fflush(stdout);
	for (int i = 0; i < width*height; i++)
	{
		uint32_t *addr = start + row_offset + i;
		uint8_t b = ((*addr) & 0x000000ff);
		uint8_t g = ((*addr) & 0x0000ff00) >> 8;
		uint8_t r = ((*addr) & 0x00ff0000) >> 16;
		//uint8_t a = ((*(start + row_offset + i)) & 0xff000000) >> 24;

		if (i % width == 0)
		{
			if (i > 0)
			{
				printf("\r\n");
				//row_offset += BSP_LCD_GetXSize();
				row_offset += BSP_LCD_GetXSize() - width;
			}
		}

		printf("\033[48;2;%d;%d;%dm", r, g, b);
		printf(" ");

		HAL_Delay(2);
	}
	printf("\033[0m");
	printf("\r\n");
}
