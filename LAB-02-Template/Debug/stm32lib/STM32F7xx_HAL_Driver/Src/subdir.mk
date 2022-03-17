################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.c \
D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.c \
D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.c \
D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.c \
D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.c \
D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.c \
D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc_ex.c \
D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.c \
D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim_ex.c \
D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.c 

OBJS += \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.o \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.o \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.o \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.o \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.o \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.o \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc_ex.o \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.o \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim_ex.o \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.o 

C_DEPS += \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.d \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.d \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.d \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.d \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.d \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.d \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc_ex.d \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.d \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim_ex.d \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.d 


# Each subdirectory must supply rules for building sources it contributes
stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.o: D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.c stm32lib/STM32F7xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DUSE_STM32F769I_DISCO -c -I"D:/STM32CubeIDE_1.7.0/workspace/LAB-02-Template/inc" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Include" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Inc" -Og -ffunction-sections -Wall -Wdouble-promotion -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.o: D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.c stm32lib/STM32F7xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DUSE_STM32F769I_DISCO -c -I"D:/STM32CubeIDE_1.7.0/workspace/LAB-02-Template/inc" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Include" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Inc" -Og -ffunction-sections -Wall -Wdouble-promotion -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.o: D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.c stm32lib/STM32F7xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DUSE_STM32F769I_DISCO -c -I"D:/STM32CubeIDE_1.7.0/workspace/LAB-02-Template/inc" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Include" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Inc" -Og -ffunction-sections -Wall -Wdouble-promotion -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.o: D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.c stm32lib/STM32F7xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DUSE_STM32F769I_DISCO -c -I"D:/STM32CubeIDE_1.7.0/workspace/LAB-02-Template/inc" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Include" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Inc" -Og -ffunction-sections -Wall -Wdouble-promotion -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.o: D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.c stm32lib/STM32F7xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DUSE_STM32F769I_DISCO -c -I"D:/STM32CubeIDE_1.7.0/workspace/LAB-02-Template/inc" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Include" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Inc" -Og -ffunction-sections -Wall -Wdouble-promotion -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.o: D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.c stm32lib/STM32F7xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DUSE_STM32F769I_DISCO -c -I"D:/STM32CubeIDE_1.7.0/workspace/LAB-02-Template/inc" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Include" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Inc" -Og -ffunction-sections -Wall -Wdouble-promotion -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc_ex.o: D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc_ex.c stm32lib/STM32F7xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DUSE_STM32F769I_DISCO -c -I"D:/STM32CubeIDE_1.7.0/workspace/LAB-02-Template/inc" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Include" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Inc" -Og -ffunction-sections -Wall -Wdouble-promotion -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.o: D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.c stm32lib/STM32F7xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DUSE_STM32F769I_DISCO -c -I"D:/STM32CubeIDE_1.7.0/workspace/LAB-02-Template/inc" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Include" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Inc" -Og -ffunction-sections -Wall -Wdouble-promotion -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim_ex.o: D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim_ex.c stm32lib/STM32F7xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DUSE_STM32F769I_DISCO -c -I"D:/STM32CubeIDE_1.7.0/workspace/LAB-02-Template/inc" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Include" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Inc" -Og -ffunction-sections -Wall -Wdouble-promotion -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.o: D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.c stm32lib/STM32F7xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DUSE_STM32F769I_DISCO -c -I"D:/STM32CubeIDE_1.7.0/workspace/LAB-02-Template/inc" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Include" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Device/ST/STM32F7xx/Include" -I"D:/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Inc" -Og -ffunction-sections -Wall -Wdouble-promotion -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-stm32lib-2f-STM32F7xx_HAL_Driver-2f-Src

clean-stm32lib-2f-STM32F7xx_HAL_Driver-2f-Src:
	-$(RM) ./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.d ./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.o ./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.d ./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.o ./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.d ./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.o ./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.d ./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.o ./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.d ./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.o ./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.d ./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.o ./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc_ex.d ./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc_ex.o ./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.d ./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.o ./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim_ex.d ./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim_ex.o ./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.d ./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.o

.PHONY: clean-stm32lib-2f-STM32F7xx_HAL_Driver-2f-Src

