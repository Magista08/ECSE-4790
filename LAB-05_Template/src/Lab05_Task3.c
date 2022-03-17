#include "init.h" // Always need init.h, otherwise nothing will work.
#include<stdint.h>
#include<stdlib.h>

GPIO_InitTypeDef       GPIO_InitStruct;

ADC_HandleTypeDef      HADC;
ADC_ChannelConfTypeDef sConfig;

DAC_HandleTypeDef      HDAC;
DAC_ChannelConfTypeDef configDAC;

DMA_HandleTypeDef 	   HDMA_ADC;

// Normalize
void flush_screen();

// Init Function
void configureADC();
void configureDAC();
void configureDMA();

// Main Function
int  c_ADC2DAC(int _ADCValue, int _ADCValuePre1, int _ADCValuePre2, int _ConversionValuePre1);

// Global Variable
int  ConversionValue = 0;
char READSIGNAL		 = 0;
int  ADCValue 			= 0;
int  ADCValuePre1 		= 0;
int  ADCValuePre2 		= 0;
int  ConversionValuePre1 = 0;

int main(){
	Sys_Init();
	configureDMA();
	configureADC();
	configureDAC();

	HAL_DAC_Start(&HDAC, DAC_CHANNEL_1);
	HAL_ADC_Start_DMA(&HADC, &ConversionValue, 1);


	while(1){
		while (!READSIGNAL);
		READSIGNAL = 0;
		HAL_ADC_Start_DMA(&HADC, &ConversionValue, 1);
		ADCValue = HAL_ADC_GetValue(&HADC);

		ConversionValue = c_ADC2DAC(ADCValue, ADCValuePre1, ADCValuePre2, ConversionValuePre1);

		HAL_DAC_SetValue(&HDAC, DAC_CHANNEL_1, DAC_ALIGN_12B_R, ConversionValue);

		ADCValuePre2 = ADCValuePre1;
		ADCValuePre1 = ADCValue;
		ConversionValuePre1 = ConversionValue;
	}

}

void configureADC(){
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

void configureDAC(){
    // Enable the ADC Clock.
	__HAL_RCC_ADC1_CLK_ENABLE();
	HADC.Instance = ADC1;

	HADC.Init.ClockPrescaler 		= ADC_CLOCK_SYNC_PCLK_DIV2; // Unknown
	HADC.Init.Resolution     		= ADC_RESOLUTION_12B;
	HADC.Init.ScanConvMode          = DISABLE;
	HADC.Init.ContinuousConvMode    = ENABLE;
	HADC.Init.DiscontinuousConvMode = DISABLE;
	HADC.Init.DataAlign				= ADC_DATAALIGN_RIGHT;
	HADC.Init.NbrOfConversion		= 1;
	HADC.Init.DMAContinuousRequests = ENABLE;
	HADC.Init.EOCSelection			= ADC_EOC_SEQ_CONV;
    HAL_ADC_Init(&HADC); // Initialize the ADC

    // Configure the ADC channel
    sConfig.Channel      = ADC_CHANNEL_6;
    sConfig.Rank         = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
    HAL_ADC_ConfigChannel(&HADC, &sConfig);
}

void configureDMA(){
	__HAL_RCC_DMA2_CLK_ENABLE();
	HDMA_ADC.Instance				  = DMA2_Stream0;
	HDMA_ADC.Init.Channel			  = DMA_CHANNEL_0;
	HDMA_ADC.Init.Direction			  = DMA_PERIPH_TO_MEMORY;
	HDMA_ADC.Init.Mode				  = DMA_CIRCULAR;
	HDMA_ADC.Init.Priority			  = DMA_PRIORITY_LOW;
	HDMA_ADC.Init.MemInc			  = DMA_MINC_DISABLE;
	HDMA_ADC.Init.PeriphInc			  = DMA_PINC_DISABLE;
	HDMA_ADC.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	HDMA_ADC.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	HDMA_ADC.Init.FIFOMode			  = DMA_FIFOMODE_DISABLE;
	HAL_DMA_Init(&HDMA_ADC);

	HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
	__HAL_LINKDMA(&HADC, DMA_Handle, HDMA_ADC);
}

void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc) {
    // GPIO init
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // ADC Pin
    GPIO_InitStruct.Pin  = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // DAC Pin
    GPIO_InitStruct.Pin  = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // PushButton
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void DMA2_Stream0_IRQHandler(){
	HAL_DMA_IRQHandler(&HDMA_ADC);
}


/*
 * Call back Function
 */

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	READSIGNAL = 1;
}

/*
 * Main Function
 */


int c_ADC2DAC(int _ADCValue, int _ADCValuePre1, int _ADCValuePre2, int _ConversionValuePre1){
	// Init the output
	int y 	   = 0;
	double   y_temp = 0.0;

	y_temp  = (double)0.312500 * (double)_ADCValue;
	y_temp += (double)0.240385 * (double)_ADCValuePre1;
	y_temp += (double)0.312500 * (double)_ADCValuePre2;
	y_temp += (double)0.296875 * (double)_ConversionValuePre1;

	y = (int) y_temp;

	return y;
}
