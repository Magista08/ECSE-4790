################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.c \
E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_adc.c \
E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.c \
E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.c \
E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.c \
E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.c \
E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.c \
E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.c \
E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.c 

OBJS += \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.o \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_adc.o \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.o \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.o \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.o \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.o \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.o \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.o \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.o 

C_DEPS += \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.d \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_adc.d \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.d \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.d \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.d \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.d \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.d \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.d \
./stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.d 


# Each subdirectory must supply rules for building sources it contributes
stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.o: E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.c stm32lib/STM32F7xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DUSE_STM32F769I_DISCO -c -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/LAB-01-Template/inc" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Include" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Device/ST/STM32F7xx/Include" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Inc" -Og -ffunction-sections -Wall -Wdouble-promotion -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_adc.o: E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_adc.c stm32lib/STM32F7xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DUSE_STM32F769I_DISCO -c -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/LAB-01-Template/inc" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Include" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Device/ST/STM32F7xx/Include" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Inc" -Og -ffunction-sections -Wall -Wdouble-promotion -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.o: E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_cortex.c stm32lib/STM32F7xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DUSE_STM32F769I_DISCO -c -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/LAB-01-Template/inc" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Include" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Device/ST/STM32F7xx/Include" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Inc" -Og -ffunction-sections -Wall -Wdouble-promotion -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.o: E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_gpio.c stm32lib/STM32F7xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DUSE_STM32F769I_DISCO -c -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/LAB-01-Template/inc" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Include" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Device/ST/STM32F7xx/Include" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Inc" -Og -ffunction-sections -Wall -Wdouble-promotion -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.o: E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr.c stm32lib/STM32F7xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DUSE_STM32F769I_DISCO -c -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/LAB-01-Template/inc" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Include" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Device/ST/STM32F7xx/Include" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Inc" -Og -ffunction-sections -Wall -Wdouble-promotion -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.o: E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_pwr_ex.c stm32lib/STM32F7xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DUSE_STM32F769I_DISCO -c -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/LAB-01-Template/inc" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Include" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Device/ST/STM32F7xx/Include" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Inc" -Og -ffunction-sections -Wall -Wdouble-promotion -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.o: E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_rcc.c stm32lib/STM32F7xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DUSE_STM32F769I_DISCO -c -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/LAB-01-Template/inc" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Include" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Device/ST/STM32F7xx/Include" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Inc" -Og -ffunction-sections -Wall -Wdouble-promotion -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.o: E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_tim.c stm32lib/STM32F7xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DUSE_STM32F769I_DISCO -c -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/LAB-01-Template/inc" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Include" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Device/ST/STM32F7xx/Include" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Inc" -Og -ffunction-sections -Wall -Wdouble-promotion -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.o: E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal_uart.c stm32lib/STM32F7xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F769xx -DUSE_STM32F769I_DISCO -c -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/LAB-01-Template/inc" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Include" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/CMSIS/Device/ST/STM32F7xx/Include" -I"E:/AllNetdiskDownload/IDE_Downloader/STM32CubeIDE_1.7.0/workspace/stm32lib/STM32F7xx_HAL_Driver/Inc" -Og -ffunction-sections -Wall -Wdouble-promotion -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

