################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MBEDTLS/Target/hardware_rng.c 

OBJS += \
./MBEDTLS/Target/hardware_rng.o 

C_DEPS += \
./MBEDTLS/Target/hardware_rng.d 


# Each subdirectory must supply rules for building sources it contributes
MBEDTLS/Target/%.o: ../MBEDTLS/Target/%.c MBEDTLS/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F769xx '-DMBEDTLS_CONFIG_FILE="mbedtls_config.h"' -c -I../Core/Inc -I"C:/Users/bryce/Documents/STM32Workspace/CryptographyLab/cryptography_mcu_shared/Inc" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../MBEDTLS/App -I../Middlewares/Third_Party/mbedTLS/include/mbedtls -I../Middlewares/Third_Party/mbedTLS/include -I../Middlewares/Third_Party/mbedTLS/library -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MBEDTLS-2f-Target

clean-MBEDTLS-2f-Target:
	-$(RM) ./MBEDTLS/Target/hardware_rng.d ./MBEDTLS/Target/hardware_rng.o

.PHONY: clean-MBEDTLS-2f-Target

