################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/PeripheralPorts/I2C.c 

OBJS += \
./Core/PeripheralPorts/I2C.o 

C_DEPS += \
./Core/PeripheralPorts/I2C.d 


# Each subdirectory must supply rules for building sources it contributes
Core/PeripheralPorts/%.o Core/PeripheralPorts/%.su Core/PeripheralPorts/%.cyclo: ../Core/PeripheralPorts/%.c Core/PeripheralPorts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Core/PeripheralPorts -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-PeripheralPorts

clean-Core-2f-PeripheralPorts:
	-$(RM) ./Core/PeripheralPorts/I2C.cyclo ./Core/PeripheralPorts/I2C.d ./Core/PeripheralPorts/I2C.o ./Core/PeripheralPorts/I2C.su

.PHONY: clean-Core-2f-PeripheralPorts

