#include "init.h"
GPIO_InitTypeDef       GPIO_InitStruct;
ADC_HandleTypeDef      HADC;
ADC_ChannelConfTypeDef sConfig;

DAC_HandleTypeDef      HDAC;
DAC_ChannelConfTypeDef configDAC;

// Listed Function
// Normalize
void flush_screen();

// Init basic parameter function
void configureADC();
void configureDAC();

void SmallTask1();
void SmallTask2();

int main(){
	Sys_Init();
	configureADC();
	configureDAC();
	flush_screen();

	// Do the first test
	// SmallTask1();

	// Do the second test
	SmallTask2();
}

void flush_screen(){
	printf("\033[2J\033[;H");
	fflush(stdout);
}

/* PART FOR INITIALIZATION */
void configureADC(){
    // Enable the ADC Clock.
	__HAL_RCC_ADC1_CLK_ENABLE();
	HADC.Instance = ADC1;

	HADC.Init.ClockPrescaler 		= ADC_CLOCK_SYNC_PCLK_DIV2; // Unknown
	HADC.Init.Resolution     		= ADC_RESOLUTION_12B;
	HADC.Init.ScanConvMode          = DISABLE;
	HADC.Init.ContinuousConvMode    = DISABLE;
	HADC.Init.DiscontinuousConvMode = DISABLE;
	HADC.Init.DataAlign				= ADC_DATAALIGN_RIGHT;
	HADC.Init.NbrOfConversion		= 1;
	HADC.Init.DMAContinuousRequests = DISABLE;
	HADC.Init.EOCSelection			= ADC_EOC_SEQ_CONV;
    HAL_ADC_Init(&HADC); // Initialize the ADC

    // Configure the ADC channel
    sConfig.Channel      = ADC_CHANNEL_6;
    sConfig.Rank         = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
    HAL_ADC_ConfigChannel(&HADC, &sConfig);
}

void configureDAC(){
	// Enable the DAC Clock
	__HAL_RCC_DAC_CLK_ENABLE();

	// Configure DAC Handler
	HDAC.Instance			   = DAC;
	HAL_DAC_Init(&HDAC);

	// Configure DAC channel
	configDAC.DAC_Trigger	   = DAC_TRIGGER_NONE;
	configDAC.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
	HAL_DAC_ConfigChannel(&HDAC, &configDAC, DAC_CHANNEL_1);
}

void HAL_DAC_MspInit(DAC_HandleTypeDef *hdac){
	// Init GPIO A1
    GPIO_InitStruct.Pin  = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc){
	// Init GPIO A0
    GPIO_InitStruct.Pin  = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Init the pushbuttom
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/* PART FOR FUNCTIONS*/
void SmallTask1(){
	unsigned int uOutput = 0;
	HAL_DAC_Start(&HDAC, DAC_CHANNEL_1);
	while(1){
		if (uOutput == 4095) uOutput = 0;
		else uOutput++;
		HAL_DAC_SetValue(&HDAC, DAC_CHANNEL_1, DAC_ALIGN_12B_R, uOutput);
	}
}

void SmallTask2(){
	unsigned int uReceive = 0;

	HAL_DAC_Start(&HDAC, DAC_CHANNEL_1);
	while(1){
		// Begin to read adc and wait for it's ready
		HAL_ADC_Start(&HADC);
		HAL_ADC_PollForConversion(&HADC, HAL_MAX_DELAY);

		// Read the volts
		uReceive = HAL_ADC_GetValue(&HADC);

		//Give it back to the DAC
		HAL_DAC_SetValue(&HDAC, DAC_CHANNEL_1, DAC_ALIGN_12B_R, uReceive);

		HAL_ADC_Stop(&HADC);
	}
}
