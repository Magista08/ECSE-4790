This project is a base project for the MPS Final Project.  
The configuration of the project is similar to Lab 1.  
In order to modify for your application, you will need to enable
all the peripherals you'll need, minus the defaults here.  To do so,
you need to perform two steps.  

1) In the file inc/stm32f7xx_hal_conf.h, uncomment any line that applies
to your desired peripherals. For example, for I2C, uncomment:
	// #define HAL_I2C_MODULE_ENABLED
2) In the stm32lib/STM32F7xx_HAL_Driver/Src folder, unexclude any
applicable source file for your desired peripherals.  Note that you
generally do not need the low-level (LL_*) or Extension (*_ex.c)
files, but you may.

Additionally, In this project, you are provided additional librarires
within the Libraries/ folder.  To use these libraries, copy the
applicable *.h files into the inc/ folder and *.c files into the
src/ folder.  Note: In the BSP library, there is LCD support
libraries (among other things).
