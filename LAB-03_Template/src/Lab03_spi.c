//----------------------------------
// Lab 3 - Part 3: SPI - Lab03_spi.c
//----------------------------------
//

#include "init.h"
#include <stdlib.h>
SPI_HandleTypeDef HSPI;
GPIO_InitTypeDef  GPIO_InitStruct;
// If needed:
//#include <stdio.h>
//#include <stdlib.h>

/*
 * For convenience, configure the SPI handler here
 */
// See 769 Description of HAL drivers.pdf, Ch. 58.1 or stm32f7xx_hal_spi.c
void configureSPI()
{
//	[SPIHandler here].Instance = SPI2; // Please use SPI2!
//	[SPIHandler here].Init.Mode = SPI_MODE_MASTER; // Set master mode
//	[SPIHandler here].Init.TIMode = SPI_TIMODE_DISABLE; // Use Motorola mode, not TI mode
/*
 * ... You get the idea.
 */
	__SPI2_CLK_ENABLE();

	HSPI.Instance  = SPI2;

	HSPI.Init.Mode              = SPI_MODE_MASTER;
	HSPI.Init.NSS               = SPI_NSS_HARD_OUTPUT;
	HSPI.Init.TIMode            = SPI_TIMODE_DISABLE;
	HSPI.Init.DataSize          = SPI_DATASIZE_8BIT; // 8bits mode
	HSPI.Init.Direction         = SPI_DIRECTION_2LINES;
	HSPI.Init.CLKPolarity       = SPI_POLARITY_HIGH;
	HSPI.Init.CLKPhase          = SPI_PHASE_1EDGE;
	// HSPI.Init.FirstBit          = SPI_FIRSTBIT_LSB;
	HSPI.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;


	HAL_SPI_Init(&HSPI);
	//
	// Note: HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *hspi)
	//
	// HAL_SPI_Init() will call HAL_SPI_MspInit() after reading the properties of
	// the passed SPI_HandleTypeDef. After finishing the MspInit call, it will set
	// the SPI property bits. This is how all HAL_[peripheral]_Init() functions work.
}


/*
 * This is called upon SPI initialization. It handles the configuration
 * of the GPIO pins for SPI.
 */
 // Do NOT change the name of an MspInit function; it needs to override a
 // __weak function of the same name. It does not need a prototype in the header.
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
	// SPI GPIO initialization structure here

	if (hspi->Instance == SPI2)
	{
		// Enable SPI GPIO port clocks, set HAL GPIO init structure's values for each
		// SPI-related port pin (SPI port pin configuration), enable SPI IRQs (if applicable), etc.
		__HAL_RCC_SYSCFG_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
		// MISO      D12 PB14
		// MOSI      D11 PB15
		// NSS(CS)   D10 PA11
		// SCK(SCLK) D13 PA12

		// Enable MISO && MOSI
		GPIO_InitStruct.Pin       = GPIO_PIN_14 | GPIO_PIN_15;
		GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull      = GPIO_PULLUP;
		GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		// Enable NSS
		GPIO_InitStruct.Pin       = GPIO_PIN_12;
		GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull      = GPIO_PULLUP;
		GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		// Enable SCLK
		GPIO_InitStruct.Pin       = GPIO_PIN_11;
		GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull      = GPIO_PULLUP;
		GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	}
}

void Task3(void);

void configureSPI_1(void);

void Receive_char(void);
void Transmit_char(void);
void ClearTM(void);
void ReadFW(void);
void TransmitData(void);
void ReadTemp(void);
void ChangeID(void);
void Wait(void);

void Task4(void);
int main(void){
	Task3();
}


// Task 3


void Task3(void){
	Sys_Init();
	configureSPI();
	HAL_SPI_MspInit(&HSPI);
	unsigned char countings = 0;
	unsigned char Input = 0;
	while(1){
		Input = getchar();
		printf("\033[H");
		fflush(stdout);
		putchar(Input);
		fflush(stdout);

		HAL_SPI_TransmitReceive(&HSPI, &Input, &countings, 1, 10);

		printf("\033[12;0H");
		fflush(stdout);
		putchar(countings);
		fflush(stdout);
	}
}


// Task 4


void Task4(void){
	Sys_Init();
	configureSPI_1();
	HAL_SPI_MspInit(&HSPI);

	// Main Program Begins at Here
	Wait();

	printf("Ending For Task4");
}

void configureSPI_1(void){
	__SPI2_CLK_ENABLE();

	HSPI.Instance  = SPI2;

	HSPI.Init.Mode              = SPI_MODE_MASTER;
	HSPI.Init.NSS               = SPI_NSS_HARD_OUTPUT;
	HSPI.Init.TIMode            = SPI_TIMODE_DISABLE;
	HSPI.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
	HSPI.Init.DataSize          = SPI_DATASIZE_8BIT; // 8bits mode
	HSPI.Init.Direction         = SPI_DIRECTION_2LINES;
	HSPI.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
	HSPI.Init.CLKPolarity       = SPI_POLARITY_LOW;
	HSPI.Init.CLKPhase          = SPI_PHASE_2EDGE;
	HSPI.Init.FirstBit          = SPI_FIRSTBIT_MSB;
	HSPI.Init.NSS               = SPI_NSS_SOFT;
	HSPI.Init.CRCPolynomial     = 7;
	HSPI.Init.CRCLength         = SPI_CRC_LENGTH_DATASIZE;
	HSPI.Init.NSSPMode          = SPI_NSS_PULSE_DISABLE;

	HAL_SPI_Init(&HSPI);
}

void Transmit_char(void){
	unsigned char input = 0;
	printf("Please enter a char to transmit to the terminal\r\n");
	input = getchar();
	printf(" The char board gets is: %u\r\n", input);


	//read data from CH_Buf register
	unsigned char add_read = 5;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_SPI_Transmit(&HSPI, &add_read, 1, 10);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_SPI_Transmit(&HSPI, &input, 1,10);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
	for (int i = 0; i < 1000; i++) asm("nop");
}
void Receive_char(void){
	unsigned char read_status  =  0;
	unsigned char unused_char  =  0;
	unsigned char address      =  0;
	unsigned char output       = 0;

	// Wait until the board is ready to read
	address = 1;
	printf("Begin the process\r\n");
	while((read_status & 0x60) == 0){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
		for (int i = 0; i < 1000; i++) asm("nop");
		HAL_SPI_Transmit(&HSPI, &address, 1, 10);
		for (int i = 0; i < 1000; i++) asm("nop");
		HAL_SPI_Receive(&HSPI, &read_status, 1,10);
		for (int i = 0; i < 1000; i++) asm("nop");
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
		for (int i = 0; i < 1000; i++) asm("nop");
	}
	printf("End the status\r\n");
	// Read the data
	address = 5;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_SPI_Transmit(&HSPI, &address, 1, 10);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_SPI_TransmitReceive(&HSPI, &unused_char, &output, 1, 40);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
	for (int i = 0; i < 1000; i++) asm("nop");

	printf("The character print out is: %u\r\n\n", output);
}

void TransmitData(void){
	unsigned char input  = 0;
	printf("Please enter a char to transmit to the terminal");
	input = getchar();
	printf("%u\r\n", input);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&HSPI, &input, 1, 10);
}

void ClearTM(void){

	unsigned char address = 0;
	unsigned char CLR     = 0x08U;

	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_SPI_Transmit(&HSPI, &address, 1, 10);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_SPI_Transmit(&HSPI, &CLR, 1, 10);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
	for (int i = 0; i < 1000; i++) asm("nop");
}

void ReadFW(void){
	unsigned char v_min  = 0;
	unsigned char v_max  = 0;
	unsigned char address= 0;

	// Read v_min
	address = 0x08;
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_SPI_Transmit(&HSPI, &address, 1, 10);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_SPI_Receive(&HSPI, &v_min, 1, 10);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
	for (int i = 0; i < 1000; i++) asm("nop");

	// Read v_max
	address = 0x07;
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_SPI_Transmit(&HSPI, &address, 1, 10);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_SPI_Receive(&HSPI, &v_max, 1, 10);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
	for (int i = 0; i < 1000; i++) asm("nop");

	printf("The version of the machine is %u.%u\r\n\n", v_max, v_min);
}

int Celcius(unsigned char temp_low, unsigned char temp_high){
	int value = ((int) temp_high << 8) + temp_low;
	int output = 357.6 - 0.187 *  value;
	return ((int) output);
}

void ReadTemp(void){
	// Basic Parameter
	unsigned char add_read = 0x00;
	unsigned char read_status = 0;
	unsigned char Temp_low  = 0;
	unsigned char Temp_high = 0;

	// Request a temperature read
	add_read = 0x00;
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_SPI_Transmit(&HSPI, &add_read, 1, 10);
	for (int i = 0; i < 1000; i++) asm("nop");


	add_read = 0x02;
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_SPI_Transmit(&HSPI, &add_read, 1,10);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
	for (int i = 0; i < 1000; i++) asm("nop");

	// Wait until the terminal is ready for read
	add_read = 0x01;
	for (int i = 0; i < 1000; i++) asm("nop");
	while ((read_status&0x08U)==0){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
		for (int i = 0; i < 1000; i++) asm("nop");
		HAL_SPI_Transmit(&HSPI, &add_read, 1, 10);
		for (int i = 0; i < 1000; i++) asm("nop");
		HAL_SPI_Receive(&HSPI, &read_status, 1,10);
		for (int i = 0; i < 1000; i++) asm("nop");
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
		for (int i = 0; i < 1000; i++) asm("nop");
	}

	// Read the data from temp_low: bit3
	add_read = 0x03;
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_SPI_Transmit(&HSPI, &add_read, 1, 10);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_SPI_Receive(&HSPI, &Temp_low, 1,10);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
	for (int i = 0; i < 1000; i++) asm("nop");

	// Read the data from temp_high: bit4
	add_read = 0x04;
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_SPI_Transmit(&HSPI, &add_read, 1, 10);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_SPI_Receive(&HSPI, &Temp_high, 1,10);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
	for (int i = 0; i < 1000; i++) asm("nop");

	printf("Temperature Low: %u Temperature High: %u \r\n", Temp_low, Temp_high);

	int temp = Celcius(Temp_low, Temp_high);
	printf("The temperature measured is %u\r\n\n", temp);
}

void ChangeID(void){
	unsigned char ID_posi = 0x09;
	unsigned char CTR_posi = 0x00;
	unsigned char NewID_posi = 0x80;
	unsigned char ID  = 0;

	// Read the new ID
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11,GPIO_PIN_RESET);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_SPI_Transmit(&HSPI, &ID_posi, 1, 10);
	for (int i = 0; i < 1000; i++) asm("nop");

	HAL_SPI_Receive(&HSPI, &ID, 1, 10);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
	for (int i = 0; i < 1000; i++) asm("nop");

	printf("The old ID is: %u\r\n", ID);
	for (int i = 0; i < 1000; i++) asm("nop");

	printf("Please enter the new ID: ");
	for (int i = 0; i < 1000; i++) asm("nop");
	ID = getchar();
	for (int i = 0; i < 1000; i++) asm("nop");
	printf("%u\r\n", ID);
	for (int i = 0; i < 1000; i++) asm("nop");

	// Prepare for the change
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11,GPIO_PIN_RESET);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_SPI_Transmit(&HSPI, &CTR_posi, 1, 10);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_SPI_Transmit(&HSPI, &NewID_posi, 1, 10);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11,GPIO_PIN_SET);
	for (int i = 0; i < 1000; i++) asm("nop");

	// Change the ID
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11,GPIO_PIN_RESET);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_SPI_Transmit(&HSPI, &ID_posi, 1, 10);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_SPI_Transmit(&HSPI, &ID, 1, 10);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
	for (int i = 0; i < 1000; i++) asm("nop");

	printf("Change the ID Already\r\n");

	// Read the id to varify it is correct
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11,GPIO_PIN_RESET);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_SPI_Transmit(&HSPI, &ID_posi, 1, 10);
	for (int i = 0; i < 1000; i++) asm("nop");

	HAL_SPI_Receive(&HSPI, &ID, 1, 10);
	for (int i = 0; i < 1000; i++) asm("nop");
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
	for (int i = 0; i < 1000; i++) asm("nop");

	printf("The read ID is: %u\r\n\n", ID);
}

void Wait(void){
	unsigned char input = 0;
	printf("Press ESC to start the program\r\n\n");
	while(input != 27)
		input = getchar();
	while (input == 27){

		// Print the start menu for the basic usage
		printf("Press '2' to transmit and receive the characters\r\n"
			   "Press '3' to do the firmware version\r\n"
			   "Press '4' to do the temperature read\r\n"
			   "Press '5' to clear the terminal\r\n"
			   "Press '6' to change ID\r\n"
			   "Press 'ESC' to stop the loopings\r\n\n");
		char char_input[1] = {0};
		char_input[0] = getchar();

		// Get the task number
		if (char_input[0] == 27){
			input = 27;
		}else{
			input = atoi(char_input);
		}

		// Point to the specific task
		if (input == 2){
			Transmit_char();
			for (int i = 0; i <= 3000; i++) asm("nop");
			Receive_char();
		}else if(input == 3){
			ReadFW();
		}else if (input == 4){
			ReadTemp();
		}else if(input == 5){
			ClearTM();
		}else if (input == 6){
			ChangeID();
		}

		// Ending the program if the usr press ESC button
		if(input == 27){
			printf("Ending the program...\r\n");
			input = 0;
		}else{
			input = 27;
		}


	}
}
