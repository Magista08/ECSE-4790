//------------------------------------------------------------------------------------
// Hello.c
//------------------------------------------------------------------------------------
//
// Test program to demonstrate serial port I/O.  This program writes a message on
// the console using the printf() function, and reads characters using the getchar()
// function.  An ANSI escape sequence is used to clear the screen if a '2' is typed.
// A '1' repeats the message and the program responds to other input characters with
// an appropriate message.
//
// Any valid keystroke turns on the green LED on the board; invalid entries turn it off
//


//------------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include "stm32f769xx.h"
#include "hello.h"

#include<stdint.h>

#define USE_DMA_Transfer
//------------------------------------------------------------------------------------
// MAIN Routine
//------------------------------------------------------------------------------------
void GPIO_init();
int is_printable(char cChar);
int main(void)
{
    Sys_Init(); // This always goes at the top of main (defined in init.c)

    char choice;
	//char in[3];
    //int size = 3;

    printf("\033[2J\033[;H"); // Erase screen & move cursor to home position
    printf("\033[0;44m");       // Let the screen become blue.
    printf("\033[2J\033[;H");
    fflush(stdout); // Need to flush stdout after using printf that doesn't end in \n
    //printf("Test of the printf() 	function.\n\n");

    // Need to enable clock for peripheral bus on GPIO Port J
    //__HAL_RCC_GPIOJ_CLK_ENABLE(); 	// Through HAL
    //RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    //// Below two lines are example on how to access a register by knowing it's memory address
    // volatile uint32_t * RCC_AHB1_CLOCK_ENABLE = (uint32_t*) 0x40023830U; // Enable clock for peripheral bus on GPIO Port J
    //*RCC_AHB1_CLOCK_ENABLE |= 512U; // Bitmask for RCC AHB1 initialization: 0x00000200U or 512U in decimal


    //RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;		//Enable clock for PORT I
    //RCC->AHB1RSTR |= RCC_AHB1RSTR_GPIOIRST;		//Reset PORT I
    //RCC->AHB1RSTR &= ~RCC_AHB1RSTR_GPIOIRST;
    //GPIOJ->MODER |= 0x00000500;		//Set mode register PIN 1, PORT I
    //GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR1;	//Set speed register PIN 1, PORT I
    //GPIOJ->ODR |= GPIO_ODR_ODR_1;				//Set output data register PIN 1, PORT I
    //GPIOJ->MODER |= 0xFFFFFFFFU;

    //GPIOJ->MODER &=  0x00000040U;

    //GPIOC->MODER  = ~0x000000C0U;
    //GPIOF->MODER  =  0x00000040U;

    //GPIOJ->BSRR |= (uint16_t)GPIO_PIN_5; // Turn on Green LED (LED2)
    //GPIOJ->BSRR |= (uint16_t)GPIO_PIN_0;


// It doesn't get lower level than this!
//    volatile uint32_t * GREENLEDMODER = (uint32_t*) 0x40022400U; // Init GPIO J Pin 5 (LED2 with no Alt. func.) to Output
//    *GREENLEDMODER |= 1024U; // Bitmask for GPIO J Pin 5 initialization: 0x00000400U or 1024U in decimal

    //volatile uint32_t * GREENLEDBSRR = (uint32_t*) 0x40022418U; // Address of GPIO J Bit Set/Reset Register
    //*GREENLEDBSRR = (uint16_t)0x0020U; // Turn on Green LED (LED2)

    HAL_Delay(1000); // Pause for a second
    /*
    volatile uint32_t * GREENLEDODR = (uint32_t*) 0x40022414U; // Address of GPIO J Output Data Register
    *GREENLEDODR ^= (uint16_t)0x0060U; // Toggle Green LED (LED2)
	*/
    // Temple Try

    //RCC->AHB2ENR |= 0x00002222;
    HAL_Delay(1000);
    // Professor's Orignal code for software installation confirmation
    /*
    while(1)
    {

        printf("Hello World!\r\n\n");
        printf("( Welcome to Microprocessor Systems )\r\n\n\n");
        printf("1=repeat, 2=clear, 0=quit.\r\n\n"); // Menu of choices
				// Don't forget to end printf with newline or run fflush(stdout) after it!

//        choice = uart_getchar(&USB_UART, 1);
				choice = getchar();
				putchar(choice);

// Messing around with stuff:
//        putchar('9'); // Putchar is weird, man.
//				choice = uart_getchar(&USB_UART, 0);
//				uart_putchar(&USB_UART, &choice);
//				puts("stuff\r\n");

        // select which option to run
//        HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_5, GPIO_PIN_SET);         // Turn green LED on (GPIO_PIN_SET == 1)
        *GREENLEDBSRR = (uint16_t)0x0020U; // Turn on Green LED (LED2)
        if (choice == '0')
            return 1;
        else if(choice == '1')
            printf("\r\n\nHere we go again.\r\n\n");
        else if(choice == '2')          // clear the screen with <ESC>[2J
        {
            printf("\033[2J\033[;H");
            fflush(stdout);
        }
        else
        {
            // inform the user how bright he is
            *GREENLEDBSRR = (uint32_t)0x0020U << 16; // Turn off Green LED (LED2)
            printf("\r\nA \"");
						putchar(choice);
//						uart_print(&USB_UART, choice);
            printf("\" is not a valid choice.\r\n\n");
        }

// Messing around with more stuff
				printf("Enter an alphanumeric sequence (press <enter> if you want to send less than %d characters): \r\n", size + 1);
				int a = uart_getline(&USB_UART, in, size);
				printf("\r\nuart_getline result: %d\r\n", a);
	}

    //serial_print_things();
	*/


    // Task 1
    /*
    while (1) {
    	// Print the instruction
    	printf("n\rPress any words to repreat. (<ESC> or ctrl + [ is to halt)");

    	// Get the character
    	choice = getchar();

    	// Break the loop or print the characters
    	// 27 is the value of the button escape
    	if ( choice == '^[' || choice == 27){
    		printf("\n\rIn break session");
    		break;
    	}else{
    		printf("\n\rThe keyboard character is %c\r",choice);
    	}
    	//HAL_Delay(1000);
    }
    */

    //serial_print_things();

    // Task 2

    GPIO_init();
    choice = '\0';
    int nLoopingSignal = 0;
    printf("\033[33m \r\n%56s","PRESS <ESC> OR <CTRL> + [ TO QUIT\r\n");
    int nPtrLineNum = 2;
    while (!nLoopingSignal){
    	choice = getchar();
    	if (choice == '^[' || choice == 27){
    		nLoopingSignal = 1;
    	}else if (is_printable(choice) == 0){
    		if (nPtrLineNum < 12){
    			for ( int i = nPtrLineNum; i < 12; i++)
    				printf("\n");
    			nPtrLineNum = 12;
    		}
    		printf("\a\033[33m%s $%02x is \033[4m%s\033[24m\r\n", "The keyboard character", choice, "not printable");
    	}else{
    		if (nPtrLineNum == 2){
    			printf("\n\n\n\r");
    		}
    		printf("\033[33mThe keyboard character is:\033[31m %c\r\n", choice);
    	}
    	nPtrLineNum++;
    	if (nPtrLineNum >= 24 && !nLoopingSignal){

    		// Erase the screen
    		printf("\033[2J\033[;H");
    		fflush(stdout);

    		// Print the instr info on line 2 and reset the line numbers
    		printf("\033[33m \r\n%56s","PRESS <ESC> OR <CTRL> + [ TO QUIT\n\r");
    		nPtrLineNum = 2;
    	}
    }

    //When break the code, earse the screen
    printf("\033[2J\033[;H");
    fflush(stdout);



   // Task 3
    /*
    GPIO_init();
    HAL_Delay(3000);

    // Set the basic Parameter
    unsigned int nD0Input = 0;
    unsigned int nD1Input = 0;
    unsigned int nD2Input = 0;
    unsigned int nD3Input = 0;
    while(1){
    	nD0Input = 0xFFFF - (0xFF7F | (GPIOC->IDR));
    	nD1Input = 0xFFFF - (0xFFBF | (GPIOC->IDR));
    	nD2Input = 0xFFFF - (0xFFFD | (GPIOJ->IDR));
    	nD3Input = 0xFFFF - (0xFFBF | (GPIOF->IDR));
    	//printf("%u %u %u %u\n",nD0Input, nD1Input, nD2Input, nD3Input);

    	// D0
    	if (nD0Input){
    		GPIOJ->ODR |=   GPIO_PIN_13;  // Turn on
    	}else if(!nD0Input){
    		GPIOJ->ODR &= ~(GPIO_PIN_13); // Turn off
    	}

    	// D1
    	if (nD1Input){
    	    GPIOJ->ODR |=   GPIO_PIN_5;  // Turn on
    	}else if(!nD1Input){
    	    GPIOJ->ODR &= ~(GPIO_PIN_5); // Turn off
    	}

    	// D2
    	if (nD2Input){
    		GPIOA->ODR |=   GPIO_PIN_12;  // Turn on
    	}else if(!nD2Input){
    		GPIOA->ODR &= ~(GPIO_PIN_12); // Turn off
    	}

    	// D3
    	if (nD3Input){
    		GPIOD->ODR &= ~(GPIO_PIN_4);  // Turn on
    	}else if(!nD3Input){
    		GPIOD->ODR |=   GPIO_PIN_4;   // Turn off
    	}
    }
    // initUart(&Second_UART, 9600, USART6);
    //initUart(&Second_UART, 9600, USART6);
    //GPIOH->MODER &= 0xFFFF7FFF;
	*/
}

//------------------------------------------------------------------------------------
//Extra thing to consider...
//------------------------------------------------------------------------------------
int is_printable(char cChar){
	if (cChar > 0x20 && cChar < 0x7E)
		return 1;
	return 0;
}

void GPIO_init(){
	// CLK Enable
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOJEN; // or through registers
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;

	// LEDs Init
	// Output init
	GPIOJ->MODER  |= 0x04000400U;// LED 1 & 2
	GPIOA->MODER  |= 0x01000000U;// LED 3
	GPIOD->MODER  |= 0x00000100U;// LED 4

	// Output Push-pull mode
	GPIOJ->OTYPER &= 0xFFFFDFDFU;// LED 1 & 2
	GPIOA->OTYPER &= 0xFFFEFFFFU;// LED 3
	GPIOD->OTYPER &= 0xFFFFFFBFU;// LED 4

	// GPIO Pin enable to output mode
	GPIOJ->BSRR   |= (uint16_t)GPIO_PIN_5;
	GPIOJ->BSRR   |= (uint16_t)GPIO_PIN_13;
	GPIOA->BSRR   |= (uint16_t)GPIO_PIN_12;
	GPIOD->BSRR   |= (uint16_t)GPIO_PIN_4;

	//Turn off all LEDs
	GPIOJ->ODR &= ~(GPIO_PIN_13);
	GPIOJ->ODR &= ~(GPIO_PIN_5);
	GPIOA->ODR &= ~(GPIO_PIN_12);
	GPIOD->ODR |=   GPIO_PIN_4;


	// PINs init
	// Input init
	GPIOC->MODER  &= 0xFFFF0FFFU;// D0 & 1
	GPIOJ->MODER  &= 0xFFFFFFF3U;// D2
	GPIOF->MODER  &= 0xFFFFCFFFU;// D3

	// Input Open Drain Mode
	GPIOJ->OTYPER |= 0x00000002U;// D0 & 1
	GPIOC->OTYPER |= 0x000000C0U;// D2
	GPIOF->OTYPER |= 0x00001000U;// D3

	// Input Pull-up Mode
	GPIOC->PUPDR  |= 0x00005000U;// D0 & 1
	GPIOJ->PUPDR  |= 0x00000004U;// D2
	GPIOF->PUPDR  |= 0x00001000U;// D3
}

void serial_print_things(void) {
	//Input Buffer
	char input[2];
	input[0]=0;
	input[1]=0;

	//Initialize the system
	Sys_Init();
	initUart(&Second_UART, 9600, USART6); // Allow printing over USART6 (Arduino pins D0 - Rx and D1 - TX)
	uart_print(&USB_UART, "\033[2J\033[;H");
	uart_print(&Second_UART, "\033[2J\033[;H");
	uart_print(&USB_UART, "Hello World: This is the USB Serial Connection\r\n");
	uart_print(&Second_UART, "Hello World: This is the other UART Connection\r\n");
	uart_print(&USB_UART, "In order to send newlines to this terminal,\r\n");
	uart_print(&USB_UART, "Press <ESC> and type \"[20h\" (without quotes)\r\n");
	uart_print(&USB_UART, "To get out of newline mode and back to line feed mode,\r\n");
	uart_print(&USB_UART, "Press <ESC> and type \"[20l\" (without quotes)\r\n");
	uart_print(&USB_UART, "\"Thanks for Playing!\"\r\n");

	printf("THIS SENTENCE USES PRINTF!!!\r\n");
  // Don't forget to end printf with newline or run fflush(stdout) after it!
	while(1) {
		input[0]=uart_getchar(&USB_UART, 0);
		uart_print(&USB_UART, input);
		uart_print(&Second_UART, input);

	}

	while(1);// HALT AND CATCH FIRE

}
