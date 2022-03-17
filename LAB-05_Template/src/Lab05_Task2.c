#include "init.h" // Always need init.h, otherwise nothing will work.
#include<stdint.h>
#include<stdlib.h>

// Structure
GPIO_InitTypeDef GPIOInit;
SPI_HandleTypeDef HSPI;
DMA_HandleTypeDef SPI_rxHandle;
DMA_HandleTypeDef SPI_txHandle;

// globel Signal
unsigned char nSignal;
char inputs[20];
char outputs[20];

// Normal Function
void flush_screen();

// Init Function
void initDMA();
void initSPI();
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi);

void DMA1_Stream3_IRQHandler(){
	HAL_DMA_IRQHandler(&SPI_rxHandle);
}

void DMA1_Stream4_IRQHandler(){
	HAL_DMA_IRQHandler(&SPI_txHandle);
}

void SPI2_IRQHanlder(){
	HAL_SPI_IRQHandler(&HSPI);
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef* hspi){
	if(hspi -> Instance == SPI2)
		nSignal = 1;
	for (int i = 0; i < 10; i++) asm("nop");
}


int main(){
	Sys_Init();
	initSPI();
	initDMA();
	flush_screen();
	HAL_SPI_TransmitReceive_DMA(&HSPI, &inputs, outputs, sizeof(inputs));
	while(1){
		// Inputs
		nSignal = 0;
		printf("\033[1;1H\033[K");
		fflush(stdout);

		int len = uart_getline(&USB_UART,inputs,19);
		while(!nSignal);  // Wait for the signal

		// Output
		printf("\033[12;1H\033[K");
		fflush(stdout);

		for (int j = 0; j< len; j++){
			printf("%c",outputs[j]);
		}
		printf("\r\n");
		memset(inputs, 0, sizeof(inputs));
		//nSignal = 0;
	}
}
/*
 * Normal Function
 */

void flush_screen(){
	printf("\033[2J\033[;H");
	fflush(stdout);
}

/*
 * Init Function
 */

void initDMA(){
	__HAL_RCC_DMA1_CLK_ENABLE();

	// RX init
	SPI_rxHandle.Instance				  = DMA1_Stream3;
	SPI_rxHandle.Init.Channel			  = DMA_CHANNEL_0;
	SPI_rxHandle.Init.Direction			  = DMA_PERIPH_TO_MEMORY;
	SPI_rxHandle.Init.Mode				  = DMA_CIRCULAR;
	SPI_rxHandle.Init.Priority			  = DMA_PRIORITY_LOW;
	SPI_rxHandle.Init.MemInc			  = DMA_MINC_ENABLE;
	SPI_rxHandle.Init.PeriphInc			  = DMA_PINC_DISABLE;
	SPI_rxHandle.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	SPI_rxHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	SPI_rxHandle.Init.FIFOMode			  = DMA_FIFOMODE_DISABLE;

	// TX init
	SPI_txHandle.Instance				  = DMA1_Stream4;
	SPI_txHandle.Init.Channel			  = DMA_CHANNEL_0;
	SPI_txHandle.Init.Direction			  = DMA_MEMORY_TO_PERIPH;
	SPI_txHandle.Init.Mode				  = DMA_CIRCULAR;
	SPI_txHandle.Init.Priority			  = DMA_PRIORITY_LOW;
	SPI_txHandle.Init.MemInc			  = DMA_MINC_ENABLE;
	SPI_txHandle.Init.PeriphInc			  = DMA_PINC_DISABLE;
	SPI_txHandle.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	SPI_txHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	SPI_txHandle.Init.FIFOMode			  = DMA_FIFOMODE_DISABLE;
	HAL_DMA_Init(&SPI_txHandle);
	HAL_DMA_Init(&SPI_rxHandle);

	HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);

	__HAL_LINKDMA(&HSPI, hdmarx, SPI_rxHandle);
	__HAL_LINKDMA(&HSPI, hdmatx, SPI_txHandle);
}


void initSPI(){
	__SPI2_CLK_ENABLE();
	HSPI.Instance = SPI2;
	HSPI.Init.Mode = SPI_MODE_MASTER;
	HSPI.Init.NSS = SPI_NSS_SOFT;
	HSPI.Init.TIMode = SPI_TIMODE_DISABLE;
	HSPI.Init.DataSize = SPI_DATASIZE_8BIT;
	HSPI.Init.Direction = SPI_DIRECTION_2LINES;
	HSPI.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
	HSPI.Init.CLKPolarity = SPI_POLARITY_LOW;
	HSPI.Init.CLKPhase = SPI_PHASE_2EDGE;//Data is captured on the 1st edge of the clock,(the falling edge for this polarity)

	HAL_SPI_Init(&HSPI);//Invoke HAL SPI Init function

	//Enable Interrupt

	HAL_NVIC_EnableIRQ(SPI2_IRQn);
}

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi){


	if (hspi->Instance == SPI2)
	{
		// Enable SPI GPIO port clocks, set HAL GPIO init structure's values for each
		// SPI-related port pin (SPI port pin configuration), enable SPI IRQs (if applicable), etc.
		// No GPIO is needed for Task 3 therefore no GPIO setup here

		// SPI GPIO initialization structure here
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();

		GPIOInit.Mode = GPIO_MODE_AF_PP;//GPIO set to alternate function with Push-Pull
		GPIOInit.Pin = (GPIO_PIN_15 | GPIO_PIN_14);//Pin 14 and 15
		GPIOInit.Pull = GPIO_PULLUP;//Pull Up
		GPIOInit.Alternate =  GPIO_AF5_SPI2;

			HAL_GPIO_Init(GPIOB,&GPIOInit);//Initialize GPIO
			GPIOInit.Pin = (GPIO_PIN_11 | GPIO_PIN_12);//Pin 11 and 12 Enable SCLK
			HAL_GPIO_Init(GPIOA,&GPIOInit);//Initialize GPIO
	}
}
