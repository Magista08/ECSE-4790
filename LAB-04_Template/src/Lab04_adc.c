//--------------------------------
// Lab 4 - Sample - Lab04_sample.c
//--------------------------------
//
//

#include "init.h"
GPIO_InitTypeDef       GPIO_InitStruct;
ADC_HandleTypeDef      HADC;
ADC_ChannelConfTypeDef sConfig;

void flush_screen();
void configureADC();

// Main Execution Loop
int main(void) {
    //Initialize the system
    Sys_Init();
    configureADC();

    double nMax = 0.0, nMin = 10.0, nAverage = 0.0, nSum = 0.0;
    int nCount = 1;

    HAL_ADC_Start(&HADC);
    HAL_ADC_PollForConversion(&HADC, HAL_MAX_DELAY);
    unsigned int ADCValue = HAL_ADC_GetValue(&HADC);
    HAL_ADC_Stop(&HADC);
    while(1){
    	HAL_Delay(300);
    	HAL_ADC_Start(&HADC);

    	HAL_ADC_PollForConversion(&HADC, HAL_MAX_DELAY);
    	ADCValue = HAL_ADC_GetValue(&HADC);
    	double GetVoltage = (double)ADCValue * 3.3 / 4095;


    	if (nMax < GetVoltage){
    		nMax = GetVoltage;
    	}else if (nMin > GetVoltage){
    		nMin = GetVoltage;
    	}
    	nSum += GetVoltage;
    	nAverage = nSum / nCount;

    	printf("The original data is:%d, the transformed data is: %f\r\n", ADCValue, GetVoltage);
    	printf("The max voltage now detected is: %f\r\n", nMax);
    	printf("The min voltage now detected is: %f\r\n", nMin);
    	printf("The ave voltage now detected is: %f\r\n", nAverage);
    	printf("It is now counts: %d\r\n\n\n\n\n\n", nCount);

    	nCount++;
    	HAL_ADC_Stop(&HADC);
    }


    // Code goes here
}

// Normalize the function
void flush_screen(){
	printf("\033[2J\033[;H");
	fflush(stdout);
}

// Init the adc
void configureADC() {
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


    /*  Available sampling times:

    	ADC_SAMPLETIME_3CYCLES
     // ADC_SAMPLETIME_15CYCLES
    	ADC_SAMPLETIME_28CYCLES
    	ADC_SAMPLETIME_56CYCLES
    	ADC_SAMPLETIME_84CYCLES
    	ADC_SAMPLETIME_112CYCLES
    	ADC_SAMPLETIME_144CYCLES
    	ADC_SAMPLETIME_480CYCLES

    */

    // Configure the ADC channel
    sConfig.Channel      = ADC_CHANNEL_6;
    sConfig.Rank         = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
    HAL_ADC_ConfigChannel(&HADC, &sConfig);
}


void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc) {



    // GPIO init
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    //__HAL_RCC_GPIOJ_CLK_ENABLE();
    GPIO_InitStruct.Pin   = GPIO_PIN_6;
    GPIO_InitStruct.Mode  = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // PushButton
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    /*
    GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull =  GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	*/

}
