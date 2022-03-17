#include "init.h" // Always need init.h, otherwise nothing will work.
#include<stdint.h>
#include<stdlib.h>


// Init structure
DMA_HandleTypeDef hdma_in;

// Control of the Buffer size and the variable type

unsigned int u8BUFFERSIZE  = 100; // Buffer size (NOT DATA SIZE)
uint8_t 	 u8InputBuffer[100];
uint16_t	 u16InputBuffer[100];
uint32_t	 u32InputBuffer[100];

uint8_t		 u8OutputBuffer[100];
uint16_t	 u16OutputBuffer[100];
uint32_t	 u32OutputBuffer[100];

// Normal Funciton
void flush_screen();
void init_input_malloc();
void clear_data();

// Initialize the clock
void initDWT();
void initDMA();

// Main Function
void software_copy();
void DMA_copy();

// Certification
int check_data_uint8_t();
int check_data_uint16_t();
int check_data_uint32_t();

int main(){
	Sys_Init();
	initDWT();
	init_input_malloc();
	flush_screen();


	initDMA();
	DMA_copy();

	// Do the DMA transformation
	int nCheckSign_uint8_t  = check_data_uint8_t();
	int nCheckSign_uint16_t = check_data_uint16_t();
	int nCheckSign_uint32_t = check_data_uint32_t();

	if (!nCheckSign_uint8_t)  printf("The copied data in uint8_t  is incorrect\r\n");
	else 					  printf("The copied data in uint8_t  is correct\r\n");

	if (!nCheckSign_uint16_t) printf("The copied data in uint16_t is incorrect\r\n");
	else 					  printf("The copied data in uint16_t is correct\r\n");

	if (!nCheckSign_uint32_t) printf("The copied data in uint32_t is incorrect\r\n");
	else 					  printf("The copied data in uint32_t is correct\r\n");

	clear_data();

	nCheckSign_uint8_t  = check_data_uint8_t();
	nCheckSign_uint16_t = check_data_uint16_t();
	nCheckSign_uint32_t = check_data_uint32_t();

	if (!nCheckSign_uint8_t)  printf("The copied data in uint8_t  is incorrect\r\n");
	else 					  printf("The copied data in uint8_t  is correct\r\n");

	if (!nCheckSign_uint16_t) printf("The copied data in uint16_t is incorrect\r\n");
	else 					  printf("The copied data in uint16_t is correct\r\n");

	if (!nCheckSign_uint32_t) printf("The copied data in uint32_t is incorrect\r\n");
	else 					  printf("The copied data in uint32_t is correct\r\n");

	printf("DMA Copy Finished\r\n\n");

	// Do the software copy and output the time inside the function
	software_copy();

	nCheckSign_uint8_t  = check_data_uint8_t();
	nCheckSign_uint16_t = check_data_uint16_t();
	nCheckSign_uint32_t = check_data_uint32_t();

	if (!nCheckSign_uint8_t)  printf("The copied data in uint8_t  is incorrect\r\n");
	else 					  printf("The copied data in uint8_t  is correct\r\n");

	if (!nCheckSign_uint16_t) printf("The copied data in uint16_t is incorrect\r\n");
	else 					  printf("The copied data in uint16_t is correct\r\n");

	if (!nCheckSign_uint32_t) printf("The copied data in uint32_t is incorrect\r\n");
	else 					  printf("The copied data in uint32_t is correct\r\n");

}

/*
 * Normalization Function
 */

void flush_screen(){
	printf("\033[2J\033[;H");
	fflush(stdout);
}

void init_input_malloc(){
	for(unsigned int i = 0; i < u8BUFFERSIZE; i++){
		u8InputBuffer[i]  = (uint8_t)  i;
		u16InputBuffer[i] = (uint16_t) i;
		u32InputBuffer[i] = (uint32_t) i;
	}

}

void clear_data(){
	for(unsigned int i = 0; i < u8BUFFERSIZE; i++){
		u8OutputBuffer[i]  = 0;
		u16OutputBuffer[i] = 0;
		u32OutputBuffer[i] = 0;
	}
}

/*
 * Initlization Function
 */

void initDWT(){
	// Enable the DWT_CYCCNT register
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->LAR = 0xC5ACCE55;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

void initDMA(){
	__HAL_RCC_DMA2_CLK_ENABLE();

	// Memory input
	hdma_in.Instance				 = DMA2_Stream1;

	// Init structure
	hdma_in.Init.Channel			 = DMA_CHANNEL_0;
	hdma_in.Init.Direction			 = DMA_MEMORY_TO_MEMORY;
	hdma_in.Init.Mode				 = DMA_NORMAL;
	hdma_in.Init.Priority			 = DMA_PRIORITY_LOW;
	hdma_in.Init.MemInc				 = DMA_MINC_ENABLE;
	hdma_in.Init.PeriphInc			 = DMA_PINC_ENABLE;
	hdma_in.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	hdma_in.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_in.Init.FIFOMode			 = DMA_FIFOMODE_DISABLE;

	HAL_DMA_Init(&hdma_in);
}

/*
 * Main Function
 */

void software_copy(){

	DWT->CYCCNT = 0;
	for (int i = 0; i < u8BUFFERSIZE; i++)	u8InputBuffer[i] = u8OutputBuffer[i];
	uint32_t llSoftwareTime = DWT->CYCCNT;
	printf("The program using the time to transfer the data size: %u, unint32_t: %ld\r\n",
			u8BUFFERSIZE,
			llSoftwareTime);

	DWT->CYCCNT = 0;
	for (int i = 0; i < u8BUFFERSIZE; i++)	u16InputBuffer[i] = u16OutputBuffer[i];
	llSoftwareTime = DWT->CYCCNT;
	printf("The program using the time to transfer the data size: %u, unint32_t: %ld\r\n",
			u8BUFFERSIZE,
			llSoftwareTime);

	DWT->CYCCNT = 0;
	for (int i = 0; i < u8BUFFERSIZE; i++)	u32InputBuffer[i] = u32OutputBuffer[i];
	llSoftwareTime = DWT->CYCCNT;
	printf("The program using the time to transfer the data size: %u, unint32_t: %ld\r\n",
			u8BUFFERSIZE,
			llSoftwareTime);
}

void DMA_copy(){
	DWT->CYCCNT = 0;
	HAL_DMA_Start(&hdma_in, (uint32_t)&u8InputBuffer, (uint32_t) u8OutputBuffer, u8BUFFERSIZE * sizeof(uint8_t));
	HAL_DMA_PollForTransfer(&hdma_in, HAL_DMA_FULL_TRANSFER, HAL_MAX_DELAY);
	uint32_t llSoftwareTime = DWT->CYCCNT;

	printf("The program using the time to transfer the data size: %u, unint8_t:  %ld\r\n",
			u8BUFFERSIZE,
			llSoftwareTime);

	DWT->CYCCNT = 0;
	HAL_DMA_Start(&hdma_in, (uint32_t)&u16InputBuffer, (uint32_t) u16OutputBuffer, u8BUFFERSIZE * sizeof(uint16_t));
	HAL_DMA_PollForTransfer(&hdma_in, HAL_DMA_FULL_TRANSFER, HAL_MAX_DELAY);
	llSoftwareTime = DWT->CYCCNT;

	printf("The program using the time to transfer the data size: %u, unint16_t: %ld\r\n",
			u8BUFFERSIZE,
			llSoftwareTime);


	DWT->CYCCNT = 0;
	HAL_DMA_Start(&hdma_in, (uint32_t)&u32InputBuffer, (uint32_t) u32OutputBuffer, u8BUFFERSIZE * (sizeof(uint32_t)));
	HAL_DMA_PollForTransfer(&hdma_in, HAL_DMA_FULL_TRANSFER, HAL_MAX_DELAY);
	llSoftwareTime = DWT->CYCCNT;

	printf("The program using the time to transfer the data size: %u, unint32_t: %ld\r\n",
			u8BUFFERSIZE,
			llSoftwareTime);
}

/*
 * Certification Function
 */

int check_data_uint8_t(){
	for(unsigned int i = 0; i < u8BUFFERSIZE; i++)
		if (u8InputBuffer[i] != u8OutputBuffer[i]) return 0;

	return 1;
}

int check_data_uint16_t(){
	for(unsigned int i = 0; i < u8BUFFERSIZE; i++)
		if (u16InputBuffer[i] != u16OutputBuffer[i]) return 0;

	return 1;
}

int check_data_uint32_t(){
	for(unsigned int i = 0; i < u8BUFFERSIZE; i++)
		if (u32InputBuffer[i] != u32OutputBuffer[i]) return 0;

	return 1;
}
