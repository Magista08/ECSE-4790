#include "init.h"
GPIO_InitTypeDef       GPIO_InitStruct;
ADC_HandleTypeDef      HADC;
ADC_ChannelConfTypeDef sConfig;

// Listed Function
// Normalize
void flush_screen();

// Set 1
void addition();
void multiplication();
void set1_function(int32_t _x);
void set1_function_mac(int32_t _x);

// Set 2
void float_multiplication();
void set2_function(float _x);
void set2_function_mac(float _x);


int main(){
	Sys_Init();

	// Task3 Set1
	flush_screen();
	printf("Begin the Task3, Set1\r\n\n");
	addition();
	multiplication();
	set1_function(6);
	set1_function_mac(6);
	printf("\r\n");

	// Task 3 Set2
	printf("Begin the Task3, Set2\r\n\n");
	float_multiplication();
	set2_function(6.0);
	set2_function_mac(6.0);
}

// Normalize the function
void flush_screen(){
	printf("\033[2J\033[;H");
	fflush(stdout);
}

// Set 1
void addition(){
	// Use of the assembly instr
	int addition = 0;
	asm("LDR r1, =0x00000080");
	asm("LDR r2, =0x00000080");
	asm("ADD r3, r1, r2");

	// asm("LDR r1, =0x00000080 \r\n LDR r2, =0x00000080 \r\n ADD r3, r1, r2")
	// If need one line to do the summation
	asm("STR r3,%0" : "=m" (addition));

	printf("The addition result is: Dec: %d, Hex: %x\r\n", addition, addition);
}

void multiplication(){
	int32_t Multi1 = 100, Multi2 = 300;
	volatile int32_t Multiplication = 0;
	asm volatile ("MUL %[out] ,%[in1] ,%[in2]"
				  :[out] "=&r" (Multiplication)
				  :[in1] "r" (Multi1),[in2] "r" (Multi2));
	printf("The multiplication of %ld and %ld is: %ld\r\n", Multi1, Multi2, Multiplication);

}

void set1_function(int32_t _x){
	// Set the final output
	volatile int32_t y = 0;

	// Division by 3
	asm("SDIV %[out] ,%[in1] ,%[in2]"
		:[out] "=&r" (y)
		:[in1] "r" (_x),[in2] "r" (3));

	// Multiply by 2
	asm("MUL %[out] ,%[in1] ,%[in2]"
		:[out] "=&r" (y)
		:[in1] "r" (y),[in2] "r" (2));

	// Addition by 5
	asm("ADD %[out] ,%[in1] ,%[in2]"
		:[out] "=&r" (y)
		:[in1] "r" (y),[in2] "r" (5));

	// Show the result
	printf("The result of 2x/3 + 5 when x = %ld is: %ld\r\n", _x, y);
}

void set1_function_mac(int32_t _x){
	// set the final output
	volatile int32_t y = 0;

	// Init the basic parameters
	asm("LDR r1, = 2");
	asm("LDR r2, = 3");
	asm("LDR r3, = 5");
	asm("LDR r4, %0" : "=m" (_x));

	// Divide, mutiply and add
	asm("SDIV r4, r4, r2");
	asm("MUL  r4, r4, r1");
	asm("ADD  r4, r4, r3");

	// Passing the value and print the result
	asm("STR r4,%0" : "=m" (y));
	printf("The result of 2x/3 + 5 when x = %ld is: %ld\r\n", _x, y);
}

// Set 2

void float_multiplication(){
	// Init the addition
	float fMulti1 = 0.3;
	float fMulti2 = 0.5;
	float fResult = 0.0;

	// Mutiplication
	asm volatile ("VMUL.F32 %[out] ,%[in1] ,%[in2]"
				  :[out] "+w" (fResult)
				  :[in1] "w" (fMulti1),[in2] "w" (fMulti2));

	// Print the result
	printf("The multiplication of %f and %f is: %f\r\n", fMulti1, fMulti2, fResult);
}

void set2_function(float _x){
	// Init the addition
	float dResult = 0.0;

	float dConstant = 5.0;
	float dCoeffe1 = 2.0;
	float dCoeffe2 = 3.0;


	// Mutiply first
	asm volatile ("VMUL.F32 %[out] ,%[in1] ,%[in2]"
					  :[out] "+w" (dResult)
					  :[in1] "w" (_x),[in2] "w" (dCoeffe1));

	// Divide
	asm volatile ("VDIV.F32 %[out] ,%[in1] ,%[in2]"
				  :[out] "+w" (dResult)
				  :[in1] "w"  (dResult),[in2] "w" (dCoeffe2));

	// Addition
	asm volatile ("VADD.F32 %[out] ,%[in1] ,%[in2]"
				  :[out] "+w" (dResult)
				  :[in1] "w"  (dResult),[in2] "w" (dConstant));

	// Print the result
	printf("The result of 2x/3 + 5 when x = %f is: %f\r\n", _x, dResult);
}

void set2_function_mac(float _x){
	// Init the vatiables
	float dResult  = 5.0;
	float dCoeffe1 = 2.0;
	float dCoeffe2 = 3.0;

	float dCoeffe  = dCoeffe1 / dCoeffe2;

	// Do the function
	asm volatile ("VMLA.F32 %[out] ,%[in1] ,%[in2]"
				  :[out] "+w" (dResult)
				  :[in1] "w"  (_x),[in2] "w" (dCoeffe));

	printf("The result of 2x/3 + 5 when x = %f is: %f\r\n", _x, dResult);
}

