################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Device/ST/STM32F7xx/Source/Templates/system_stm32f7xx.c 

OBJS += \
./stm32lib/CMSIS/Device/ST/STM32F7xx/Source/Templates/system_stm32f7xx.o 

C_DEPS += \
./stm32lib/CMSIS/Device/ST/STM32F7xx/Source/Templates/system_stm32f7xx.d 


# Each subdirectory must supply rules for building sources it contributes
stm32lib/CMSIS/Device/ST/STM32F7xx/Source/Templates/system_stm32f7xx.o: D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Device/ST/STM32F7xx/Source/Templates/system_stm32f7xx.c stm32lib/CMSIS/Device/ST/STM32F7xx/Source/Templates/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DUSE_STM32F769I_DISCO -c -I"D:/STM32CubeIDE_1.7.0/workspace/LAB-03_Template/inc" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Include" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Inc" -Og -ffunction-sections -Wall -Wdouble-promotion -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-stm32lib-2f-CMSIS-2f-Device-2f-ST-2f-STM32F7xx-2f-Source-2f-Templates

clean-stm32lib-2f-CMSIS-2f-Device-2f-ST-2f-STM32F7xx-2f-Source-2f-Templates:
	-$(RM) ./stm32lib/CMSIS/Device/ST/STM32F7xx/Source/Templates/system_stm32f7xx.d ./stm32lib/CMSIS/Device/ST/STM32F7xx/Source/Templates/system_stm32f7xx.o

.PHONY: clean-stm32lib-2f-CMSIS-2f-Device-2f-ST-2f-STM32F7xx-2f-Source-2f-Templates

