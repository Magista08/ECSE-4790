//------------------------------------
// Lab 3 - Part 1: UART - Lab03_uart.c
//------------------------------------
//
#include <string.h>

#include "init.h"
UART_HandleTypeDef huart6;
// Main Execution Loop

void TestMainOutput(void);
void initInterrupt();
void Task1(void);
void Task2(void);


char output[1] = {0};
char old_output[1] = {0};


int main(void) {

    // Lost? Check out uart.c!
	Task2();
}

void Task1(void) {
    Sys_Init();

    initUart(&huart6, 115200, USART6);
    //HAL_UART_MspInit(&huart6);
    //NVIC->ISER[1] |= 0x00000040U; // UASTR1: posi 37
    //NVIC->ISER[2] |= 0x00004000U; // UASTR6: posi 77

    char Tranmittion[1] = {0};
    char original[1] = {0};
    while (1) {
        HAL_UART_Receive(&huart6, (uint8_t *) Tranmittion, 1, 10);
        if (Tranmittion[0] != 27 && strcmp(original, Tranmittion) != 0) {
            uart_putchar(&huart6, Tranmittion);
            uart_putchar(&USB_UART, Tranmittion);
        } else if (Tranmittion[0] == 27) {
            uart_print(&huart6, "stop the program");
            uart_print(&USB_UART, "stop the program");
            break;
        }

        HAL_UART_Receive(&USB_UART, (uint8_t *) Tranmittion, 1, 10);
        if (Tranmittion[0] != 27 && strcmp(original, Tranmittion) != 0) {
            uart_putchar(&huart6, Tranmittion);
            uart_putchar(&USB_UART, Tranmittion);
        } else if (Tranmittion[0] == 27) {
            uart_print(&huart6, "stop the program");
            uart_print(&USB_UART, "stop the program");
            break;
        }

        strcpy(original, Tranmittion);
    }
}

void Task2(void) {

	Sys_Init();
	initUart(&huart6, 38400, USART6);
	HAL_UART_MspInit(&huart6);

	initInterrupt();
	HAL_UART_Receive_IT(&huart6, (uint8_t *) output, 1);
	HAL_UART_Receive_IT(&USB_UART, (uint8_t *) output, 1);

	while(1) {
		if(output[0] == 27){
			uart_print(&USB_UART, "STOP HERE!");
			uart_print(&huart6,   "STOP HERE!");
			break;
		}else if(output[0] == 27){
			uart_print(&USB_UART, "STOP HERE!");
			uart_print(&huart6,   "STOP HERE!");
			break;
		}
	}
}


void initInterrupt(){
	HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART1_IRQn);

	HAL_NVIC_SetPriority(USART6_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART6_IRQn);
	/*
	NVIC->ISER[1] |= 0x00000040U; // UASTR1: posi 37
	NVIC->ISER[2] |= 0x00004000U; // UASTR6: posi 77
	*/
}

void USART1_IRQHandler(){
	HAL_UART_IRQHandler(&USB_UART);
}

void USART6_IRQHandler(){
	HAL_UART_IRQHandler(&huart6);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle){

	if (UartHandle->Instance == USART1){
		if (strcmp(output, old_output) != 0 ){
			uart_putchar(&huart6, output);
			uart_putchar(&USB_UART, output);
		}
		HAL_UART_Receive_IT(&USB_UART, (uint8_t *) output, 1);

	}else if (UartHandle->Instance == USART6){
		if (strcmp (output, old_output) != 0){
			uart_putchar(&huart6, output);
			uart_putchar(&USB_UART, output);
		}

		HAL_UART_Receive_IT(&huart6, (uint8_t *) output, 1);

	}
	strcpy(old_output, output);
}

void TestMainOutput() {
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin       = GPIO_PIN_9;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
