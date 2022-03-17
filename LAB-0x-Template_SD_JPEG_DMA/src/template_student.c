/*
 * template.c
 *
 *  Created on: Oct 14, 2020
 *      Author: suris
 */

#include "stm32f769xx.h"
#include "stm32f7xx_hal.h"
#include "stm32f769i_discovery_lcd.h"

#include "ff_gen_drv.h"
#include "sd_diskio.h"
#include "jpeg_utils.h"

#include "init.h"
#include "stdlib.h"
#include "helper_functions.h"

/* Defines */
#define LCD_FRAME_BUFFER        0xC0000000
#define JPEG_OUTPUT_DATA_BUFFER 0xC0200000

/* Global Variables */
uint32_t MCU_TotalNb = 0;
uint32_t num_bytes_decoded = 0;

uint32_t index_address = 0;
uint32_t file_size = 232330;
uint8_t ReadData[128] = {0};
uint8_t InputBuffer[128] = {0};
uint8_t OutputBuffer[4096] = {0};
uint8_t input = 0x1B;

unsigned char decode_signal = 0;
unsigned char pic_decode	= 1;
unsigned char finished_signal = 1;

JPEG_HandleTypeDef  jpeg_handle;
JPEG_ConfTypeDef    jpeg_info;
DMA2D_HandleTypeDef DMA2D_Handle;
UINT left_space;

FIL pic;

char path[]      = "0:/";
char file_path[] = "0";

void DMA2D_CopyBuffer(uint32_t *pSrc, uint32_t *pDst, uint16_t x, uint16_t y, JPEG_ConfTypeDef *jpeg_info);

int main(void)
{
	Sys_Init();

    printf("\033[2J\033[;H"); // Erase screen & move cursor to home position
    printf("\033c"); // Reset device
    fflush(stdout);


    /*
     * Leave this section even if you don't have an LCD
     */
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(0, LCD_FRAME_BUFFER);
    BSP_LCD_SelectLayer(0);
    BSP_LCD_Clear(LCD_COLOR_BLACK);

    /* Task 1 */
    /* List all the files in the top directory of the SD Card */
    // Init the basic parameters
    FATFS *fs;
    FIL fil;
    DIR dir;
    static FILINFO fno;
    fs = malloc(sizeof (FATFS));
    // Link FATFS Driver
    FATFS_LinkDriver(&SD_Driver, path);
    // Mount the disk
    FRESULT status = f_mount(fs, file_path, 0);
    while (status != FR_OK);
    // List the files
    status = f_opendir(&dir, path);
    while (status != FR_OK);
    while(1){
    	status = f_readdir(&dir, &fno);
    	if (status != FR_OK || fno.fname[0] == 0) break;
    	printf("%s\r\n", fno.fname);
    }

    // Select a file
    char choice = 18;
    char select_file[100] = {0};
    while(choice < 0 || choice > 10){
    	printf("Input a number from '0' to '9' to represent the files to choose\r\n");
    	choice = getchar();
    	select_file[0] = choice;
    	choice = atoi(choice);
    }

    // Print out it's contents
    strcat(select_file, ".txt");
    status = f_open(&fil, select_file, FA_READ);
    while(status);
    char line[100] = {0};
    while(f_gets(line, sizeof(line), &fil)){
    	printf("%s", line);
    }
    // Close the file
    f_close(&fil);

    printf("Task 1 completed! Press any key to continue \r\n");
    getchar();
    printf("\033[2J\033[;H"); // Erase screen & move cursor to home position
    printf("\033c"); // Reset device
    fflush(stdout);

    // Initialize JPEG
    jpeg_handle.Instance = JPEG;
    HAL_JPEG_Init(&jpeg_handle);
    // Decode the passed file without DMA
    status = f_open(&pic, "picture.jpg", FA_READ);
    if(status) {
    	printf("Cannot open the file named: picture.jpeg\r\n");
    	return 1;
    }
    f_read(&pic, ReadData, 128, &left_space);
    while(!finished_signal){
    	printf("%lu\r\n", num_bytes_decoded);
    	HAL_JPEG_Encode(&jpeg_handle, ReadData, sizeof(ReadData), (uint8_t *) JPEG_OUTPUT_DATA_BUFFER, sizeof(ReadData), HAL_MAX_DELAY);
    }
    printf("%lu\r\n", num_bytes_decoded);

    // Print out the image size
    HAL_JPEG_GetInfo(&jpeg_handle, &jpeg_info);
    printf("The data width is: %lu",  jpeg_info.ImageWidth);
    printf("The data height is: %lu", jpeg_info.ImageHeight);
    // Print the image in PuTTy
    uint8_t *raw_output = colorConversion((uint8_t *)JPEG_OUTPUT_DATA_BUFFER, num_bytes_decoded);
    if (input != 0x1B)
    	printPutty(raw_output, &jpeg_info);

    printf("\r\nTask 2 completed! Press any key to continue \r\n");
    getchar();
    printf("\033[2J\033[;H"); // Erase screen & move cursor to home position
    printf("\033c"); // Reset device
    fflush(stdout);

}

void DMA2D_CopyBuffer(uint32_t *pSrc, uint32_t *pDst, uint16_t x, uint16_t y, JPEG_ConfTypeDef *jpeg_info)
{
	//uint32_t destination =
	uint32_t source      = (uint32_t)pSrc;

	/*
	 * Provided: width offset calculation
	 * From DMA2D example and STM32 application note
	 */
	uint32_t width_offset = 0;
	if(jpeg_info->ChromaSubsampling == JPEG_420_SUBSAMPLING)
	{
		if((jpeg_info->ImageWidth % 16) != 0)
			width_offset = 16 - (jpeg_info->ImageWidth % 16);
	}

	if(jpeg_info->ChromaSubsampling == JPEG_422_SUBSAMPLING)
	{
		if((jpeg_info->ImageWidth % 16) != 0)
			width_offset = 16 - (jpeg_info->ImageWidth % 16);
	}

	if(jpeg_info->ChromaSubsampling == JPEG_444_SUBSAMPLING)
	{
		if((jpeg_info->ImageWidth % 8) != 0)
			width_offset = 8 - (jpeg_info->ImageWidth % 8);
	}

	/*##-1- Configure the DMA2D Mode, Color Mode and output offset #############*/
	//DMA2D_Handle.Init.Mode          =
	//DMA2D_Handle.Init.ColorMode     =
	//DMA2D_Handle.Init.OutputOffset  =
	//DMA2D_Handle.Init.AlphaInverted =
	//DMA2D_Handle.Init.RedBlueSwap   =

	/*##-2- DMA2D Callbacks Configuration ######################################*/
	DMA2D_Handle.XferCpltCallback  = NULL;

	/*##-3- Foreground Configuration ###########################################*/
	//DMA2D_Handle.LayerCfg[1].AlphaMode =
	//DMA2D_Handle.LayerCfg[1].InputAlpha =
	//DMA2D_Handle.LayerCfg[1].InputColorMode =
	DMA2D_Handle.LayerCfg[1].InputOffset = width_offset;
	//DMA2D_Handle.LayerCfg[1].RedBlueSwap =
	//DMA2D_Handle.LayerCfg[1].AlphaInverted =

	//DMA2D_Handle.Instance          =

	/* DMA2D Initialization */

	/* DMA2D Config Layer */

	/* DMA2D Start */

	/* DMA2D Poll for Transfer */

}

/*
 * Callback called whenever the JPEG needs more data
 */
void HAL_JPEG_GetDataCallback(JPEG_HandleTypeDef *hjpeg, uint32_t NbDecodedData)
{
	printf("Hello World\r\n");
	MCU_TotalNb += NbDecodedData;
	uint16_t ReadSize = 128;
	if (left_space <= 0){
		ReadSize = 0;
		finished_signal = 1;
	}else if(MCU_TotalNb + ReadSize > file_size){
		ReadSize = MCU_TotalNb - file_size;
	}
	f_read(&pic, ReadData, ReadSize, &left_space);
	HAL_JPEG_ConfigInputBuffer(hjpeg, ReadData, sizeof(ReadData));

}

void HAL_JPEG_DataReadyCallback(JPEG_HandleTypeDef *hjpeg, uint8_t *pDataOut, uint32_t OutDataLength)
{
	printf("Hello World\r\n");
	num_bytes_decoded += OutDataLength;
	HAL_JPEG_ConfigOutputBuffer(hjpeg, num_bytes_decoded, OutDataLength);

}

void HAL_JPEG_DecodeCpltCallback(JPEG_HandleTypeDef *hjpeg)
{
	printf("Hello World\r\n");
	decode_signal = 1;
}

// Provided code for callback
// Called when the jpeg header has been parsed
// Adjust the width to be a multiple of 8 or 16 (depending on image configuration) (from STM examples)
// Get the correct color conversion function to use to convert to RGB
void HAL_JPEG_InfoReadyCallback(JPEG_HandleTypeDef *hjpeg, JPEG_ConfTypeDef *pInfo)
{
	// Have to add padding for DMA2D
	if(pInfo->ChromaSubsampling == JPEG_420_SUBSAMPLING)
	{
		if((pInfo->ImageWidth % 16) != 0)
			pInfo->ImageWidth += (16 - (pInfo->ImageWidth % 16));

		if((pInfo->ImageHeight % 16) != 0)
			pInfo->ImageHeight += (16 - (pInfo->ImageHeight % 16));
	}

	if(pInfo->ChromaSubsampling == JPEG_422_SUBSAMPLING)
	{
		if((pInfo->ImageWidth % 16) != 0)
			pInfo->ImageWidth += (16 - (pInfo->ImageWidth % 16));

		if((pInfo->ImageHeight % 8) != 0)
			pInfo->ImageHeight += (8 - (pInfo->ImageHeight % 8));
	}

	if(pInfo->ChromaSubsampling == JPEG_444_SUBSAMPLING)
	{
		if((pInfo->ImageWidth % 8) != 0)
			pInfo->ImageWidth += (8 - (pInfo->ImageWidth % 8));

		if((pInfo->ImageHeight % 8) != 0)
			pInfo->ImageHeight += (8 - (pInfo->ImageHeight % 8));
	}

	if(JPEG_GetDecodeColorConvertFunc(pInfo, &pConvert_Function, &MCU_TotalNb) != HAL_OK)
	{
		printf("Error getting DecodeColorConvertFunct\r\n");
		while(1);
	}
}



DMA_HandleTypeDef hdmaIn;
DMA_HandleTypeDef hdmaOut;

void HAL_JPEG_MspInit(JPEG_HandleTypeDef *hjpeg)
{
	// Enable JPEG and DMA clock
	//__HAL_RCC_DMA2_CLK_ENABLE();
	//__HAL_RCC_JPEG_CLK_ENABLE();

	// Enable + setup JPEG IRQ
	//HAL_NVIC_SetPriority(JPEG_IRQn, 0, 0);
	//HAL_NVIC_EnableIRQ(JPEG_IRQn);

	// Input DMA Setup
	//hdmaIn.Init.Channel 		      = DMA_CHANNEL_9;
	//hdmaIn.Init.Direction 		  =
	//hdmaIn.Init.PeriphInc 		  =
	//hdmaIn.Init.MemInc 			  =
	//hdmaIn.Init.PeriphDataAlignment =
	//hdmaIn.Init.MemDataAlignment    =
	//hdmaIn.Init.Mode                =
	//hdmaIn.Init.Priority            =
	//hdmaIn.Init.FIFOMode            =
	//hdmaIn.Init.FIFOThreshold       =
	//hdmaIn.Init.MemBurst            =
	//hdmaIn.Init.PeriphBurst         =

	//hdmaIn.Instance                 = DMA2_Stream0;

	// Link hdmaIn

	// Enable + setup Input DMA IRQ

	// Output DMA Setup
	//hdmaOut.Init.Channel =
	//hdmaOut.Init.Direction =
	//hdmaOut.Init.PeriphInc =
	//hdmaOut.Init.MemInc =
	//hdmaOut.Init.PeriphDataAlignment =
	//hdmaOut.Init.MemDataAlignment =
	//hdmaOut.Init.Mode =
	//hdmaOut.Init.Priority =
	//hdmaOut.Init.FIFOMode =
	//hdmaOut.Init.FIFOThreshold =
	//hdmaOut.Init.MemBurst =
	//hdmaOut.Init.PeriphBurst =

	//hdmaOut.Instance =


	// Link hdmaOut

	// Enable + setup Output DMA IRQ
}


void JPEG_IRQHandler(void)
{
	HAL_JPEG_IRQHandler(&jpeg_handle);
}

void DMA2_Stream3_IRQHandler(void)
{
}

void DMA2_Stream4_IRQHandler(void)
{
}


