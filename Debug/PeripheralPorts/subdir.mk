################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../PeripheralPorts/I2C.c 

OBJS += \
./PeripheralPorts/I2C.o 

C_DEPS += \
./PeripheralPorts/I2C.d 


# Each subdirectory must supply rules for building sources it contributes
PeripheralPorts/%.o PeripheralPorts/%.su PeripheralPorts/%.cyclo: ../PeripheralPorts/%.c PeripheralPorts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-PeripheralPorts

clean-PeripheralPorts:
	-$(RM) ./PeripheralPorts/I2C.cyclo ./PeripheralPorts/I2C.d ./PeripheralPorts/I2C.o ./PeripheralPorts/I2C.su

.PHONY: clean-PeripheralPorts

