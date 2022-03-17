#include "init.h"

GPIO_InitTypeDef       GPIO_InitStruct;

ADC_HandleTypeDef      HADC;
ADC_ChannelConfTypeDef sConfig;

DAC_HandleTypeDef      HDAC;
DAC_ChannelConfTypeDef configDAC;

char READSIGNAL = 1;

// Normalize
void flush_screen();

// Init Function
void configureADC();
void configureDAC();

// Conversion Function
int asm_ADC2DAC(int _ADCValue, int _ADCValuePre1, int _ADCValuePre2, int _ConversionValuePre1);
int   c_ADC2DAC(int _ADCValue, int _ADCValuePre1, int _ADCValuePre2, int _ConversionValuePre1);

int main(){
	Sys_Init();
	configureADC();
	configureDAC();
	flush_screen();

	// Init the basic parameter
	int ADCValue 			= 0;
	int ADCValuePre1 		= 0;
	int ADCValuePre2 		= 0;
	int ConversionValuePre1 = 0;
	int ConversionValue     = 0;

	char cUserChoice 	= 0;
	char cUserChoicePre = 0;

	HAL_DAC_Start(&HDAC, DAC_CHANNEL_1);
	while(1){
		if (READSIGNAL){
			cUserChoicePre = cUserChoice;
			printf("Type '1' to choose the c equation mode\r\nType '2' to choose the asm mode\r\n\n");
			cUserChoice = getchar();
			printf("Begin the work with %c mode\r\n", cUserChoice);
			if (!cUserChoicePre) cUserChoicePre = cUserChoice;
			READSIGNAL = 0;
		}
		HAL_ADC_Start(&HADC);
		HAL_ADC_PollForConversion(&HADC, HAL_MAX_DELAY);

		ADCValue = HAL_ADC_GetValue(&HADC);

		if (cUserChoice == '1'){
			ConversionValue = c_ADC2DAC(ADCValue, ADCValuePre1, ADCValuePre2, ConversionValuePre1);
		}else if (cUserChoice == '2'){
			ConversionValue = asm_ADC2DAC(ADCValue, ADCValuePre1, ADCValuePre2, ConversionValuePre1);
		}else{
			continue;
		}

		HAL_DAC_SetValue(&HDAC, DAC_CHANNEL_1, DAC_ALIGN_12B_R, ConversionValue);
		HAL_ADC_Stop(&HADC);

		ADCValuePre2 = ADCValuePre1;
		ADCValuePre1 = ADCValue;
		ConversionValuePre1 = ConversionValue;
	}
}

void flush_screen(){
	printf("\033[2J\033[;H");
	fflush(stdout);
}

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

void EXTI0_IRQHandler(){
	EXTI->PR |= 0x00000001U;
	asm("nop");
	asm("nop");

	READSIGNAL = 1;
}

int asm_ADC2DAC(int _ADCValue, int _ADCValuePre1, int _ADCValuePre2, int _ConversionValuePre1){
	// Set the final output
	int   y      = 0;
	float y_temp = 0.0;
	float coeff1 = 0.0003125;
	float coeff2 = 0.000240385;
	float coeff3 = 0.000296875;

	float ADCValue     		  = (float) _ADCValue;
	float ADCValuePre1 		  = (float) _ADCValuePre1;
	float ADCValuePre2        = (float) _ADCValuePre2;
	float ConversionValuePre1 = (float) _ConversionValuePre1;

	// Part1
	// Multiplt the previous ADC value by 0.312500 and add to y_temp
	asm volatile ("VMLA.F32 %[out], %[in1], %[in2]"
		:[out] "+w" (y_temp)
		:[in1] "w" (ADCValue),[in2] "w" (coeff1));

	// Multiplt the previous ADC value by 10/13(0.240385) and add to y_temp
	asm volatile("VMLA.F32 %[out], %[in1], %[in2]"
		:[out] "+w" (y_temp)
		:[in1] "w" (ADCValuePre1),[in2] "w" (coeff2));

	// Multiplt the second last ADC value by 0.312500 and add to y_temp
	asm volatile("VMLA.F32 %[out], %[in1], %[in2]"
		:[out] "+w" (y_temp)
		:[in1] "w" (ADCValuePre2),[in2] "w" (coeff1));

	// Multiplt the previous conversion value by 19/20(0.296875) and add to y_temp
	asm volatile("VMLA.F32 %[out], %[in1], %[in2]"
		:[out] "+w" (y_temp)
		:[in1] "w" (ConversionValuePre1),[in2] "w" (coeff3));

	// Conversion into the integer part
	y_temp = y_temp * 1000;
	y = (int) y_temp;

	return y;
}

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
