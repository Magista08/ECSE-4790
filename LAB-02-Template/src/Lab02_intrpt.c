//----------------------------------
// Lab 2 - Timer Interrupts - Lab02.c
//----------------------------------
// Objective:
//   Build a small game that records user's reaction time.
//

//
//
// -- Imports ---------------
//
#include "init.h"

//EXTI_HandleTypeDef EXTI_InitStruct = {0};
//
//
// -- Prototypes ------------
//
void blinkScreen();
void Init_GPIO();
void Init_Timer();
void HAL_Init_GPIO();
void flash_screen();

//
//
// -- Code Body -------------
//

TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim7;

volatile uint8_t timeUpdated = 0;
volatile uint8_t buttonPressed = 0;
volatile uint8_t buttonReleased = 0;
volatile uint32_t elapsed = 0;


int32_t  randomNumber = 0;
uint32_t startTime    = 0;
uint32_t EXTI0_POSI   = 6;
float averageScore    = 0;
unsigned int iterations = 0;

//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

int main() {
	Sys_Init();
	HAL_Init();
	Init_Timer();
	HAL_Init_GPIO();
	Init_GPIO();
	flash_screen();
	//HAL_Init_GPIO();
	/*
	while (1) {
		// Main loop code goes here
		printf("\033c\033[36m\033[2J");
		printf("Blink!\r\n");
		HAL_Delay(1000);
		// Sample Code + Sample Test
		blinkScreen(); // Alternatively: in some terminals, the BELL can be configured to produce
					   // 			a "visual bell" ... a blink.\

		int ReadSignal = HAL_GPIO_ReadPin(GPIOJ,GPIO_PIN_0);
		if (ReadSignal != 0){
			HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_13, GPIO_PIN_SET);
		}else if(ReadSignal == 0){
			HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_13, GPIO_PIN_RESET);
		}
		// /
		HAL_Delay(1000);
	}
	*/
	while(1);
}

//
//
// -- Utility Functions ------
//
void blinkScreen(){
	printf("\033[30;47m");
	// Clear and redraw display (flash it & sound the bell).
	printf("\a\033[s\033[2J\033[u");
	fflush(stdout);
	HAL_Delay(100);

	printf("\033[37;40m");
	// Clear and redraw display (flash it).
	printf("\033[s\033[2J\033[u");
	fflush(stdout);
}


//
//
// -- Init Functions ----------
//

// Register Version (TIM6)
void Init_Timer() {
	// Enable the TIM6 interrupt.
	// Looks like HAL hid this little gem, this register isn't mentioned in
	//   the STM32F7 ARM Reference Manual....
	// NVIC->ISER = ???
	// Not sure for that,doubt for the correctness for the interrupt

	NVIC->ISER[1] |= 0x00400000; // TIM6 posi is at 54

	// Enable TIM6 clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	asm ( "nop" );
	asm ( "nop" );

	// Set pre-scaler to slow down ticlks
	TIM6->PSC   = 10800;

	// Set the Auto-reload Value for 10Hz overflow
	TIM6->ARR   = 20000;

	// Generate update events to auto reload.
	TIM6->EGR  |= 0x0001U;

	// Enable Update Interrupts.
	TIM6->DIER |= 0x0001U;

	// Start the timer.
	// TIM6->CR1
	TIM6->CR1 |= 0x0001U;
}

//HAL Version (TIM7)
void HAL_Init_GPIO(){
	//Enable TIM7
	htim7.Instance = TIM7;
	htim7.Init.Prescaler = 10800; //
	htim7.Init.Period = 20000; //2HZ / 20 = 0.1Hz = 10s
	htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
	__HAL_RCC_TIM7_CLK_ENABLE();

	HAL_NVIC_SetPriority(TIM7_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM7_IRQn);

	HAL_TIM_Base_Init(&htim7);
	HAL_TIM_Base_Start_IT(&htim7);

}


void Init_GPIO() {
	// Enable GPIO clocks?
	// Looks like GPIO reg updates are synced to a base clock.
	//  for any changes to appear the clocks need to be running.
	//RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	//RCC->AHB1ENR |= RCC_AHB1ENR_GPIOJEN;

	// Enable clock to SYSCONFIG module to enable writing of EXTICRn registers
	//RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	// or __HAL_RCC_SYSCFG_CLK_ENABLE();

	// Enable the RCC clock by HAL
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_SYSCFG_CLK_ENABLE();
	__HAL_RCC_GPIOJ_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	// Delay after an RCC peripheral clock enabling
	asm ("nop");
	asm ("nop");

	// Set Pin 13/5 to output. (LED1 and LED2)
	// Enable the output LED1
	GPIO_InitStruct.Pin   = GPIO_PIN_13;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

	// Enable the output LED2
	GPIO_InitStruct.Pin   = GPIO_PIN_5;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

	// Enable the output LED3
	GPIO_InitStruct.Pin   = GPIO_PIN_12;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	// Turn off LEDs
	HAL_GPIO_WritePin(GPIOJ,GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOJ,GPIO_PIN_5,  GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12, GPIO_PIN_RESET);

	// GPIO Interrupt
	// By default pin PA0 will trigger the interrupt, change EXTICR1 to route proper pin
	//SYSCFG->EXTICR[0] // EXTICR1-4 are confusingly an array [0-3].

	// Set Pin 0 as input (button) with pull-down.
	//GPIOA->PUPDR
	GPIO_InitStruct.Pin  = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	// Set interrupt enable for EXTI0.
	// NVIC->ISER

	// Unmask interrupt.
	// EXTI->IMR

	// Register for rising edge.
	// EXTI->RTSR

	// And register for the falling edge.
	// EXTI->FTSR

	//HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

//
//
// -- ISRs (IRQs) -------------
//

void TIM6_DAC_IRQHandler() {
	// Clear Interrupt Bit
	//TIM6->SR &= 0xFFFE;
	TIM6->SR = ~TIM_SR_UIF;

	// Other code here:
	HAL_GPIO_TogglePin(GPIOJ, GPIO_PIN_5);
	elapsed++;
	printf("\rOverflows occurs, now the time is : %d ms", elapsed);

}
void TIM7_IRQHandler(){
	HAL_TIM_IRQHandler(&htim7);
}


// Non-HAL GPIO/EXTI Handler
void XXX_IRQHandler() {
	// Clear Interrupt Bit by setting it to 1.
	//EXTI->PR |= ;

	// Other code here:

}

//HAL - GPIO/EXTI Handler
void EXTI0_IRQHandler() {
	//HAL_GPIO_EXTI_IRQHandler(???);
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	// ISR code here.
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)){
		HAL_GPIO_TogglePin(GPIOJ, GPIO_PIN_13);
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM7){
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_12);
		timeUpdated++;
		printf("\rOverflows occurs, now the time is : %d ms", timeUpdated);
	}
}

// Assitance Function

void flash_screen(){
	printf("\033[30;47m"); // Erase screen & move cursor to home position
	//printf("\033[0;44m");       // Let the screen become blue.
	//printf("\033[2J\033[;H");
	fflush(stdout);
}
// For the HAL timer interrupts, all of the associated Callbacks need to exist,
// otherwise during assembly, they will generate compiler errors as missing symbols
// Below are the ones that are not used.

// void HAL_TIMEx_BreakCallback(TIM_HandleTypeDef *htim){};
// void HAL_TIMEx_CommutationCallback(TIM_HandleTypeDef *htim){};
