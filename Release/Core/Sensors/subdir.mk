################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Sensors/BAR30.c \
../Core/Sensors/BAR30_CommPorter.c 

OBJS += \
./Core/Sensors/BAR30.o \
./Core/Sensors/BAR30_CommPorter.o 

C_DEPS += \
./Core/Sensors/BAR30.d \
./Core/Sensors/BAR30_CommPorter.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Sensors/%.o Core/Sensors/%.su Core/Sensors/%.cyclo: ../Core/Sensors/%.c Core/Sensors/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Core/PeripheralPorts -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Sensors

clean-Core-2f-Sensors:
	-$(RM) ./Core/Sensors/BAR30.cyclo ./Core/Sensors/BAR30.d ./Core/Sensors/BAR30.o ./Core/Sensors/BAR30.su ./Core/Sensors/BAR30_CommPorter.cyclo ./Core/Sensors/BAR30_CommPorter.d ./Core/Sensors/BAR30_CommPorter.o ./Core/Sensors/BAR30_CommPorter.su

.PHONY: clean-Core-2f-Sensors

