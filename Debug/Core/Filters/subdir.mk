################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Filters/AvarageFilter.c 

OBJS += \
./Core/Filters/AvarageFilter.o 

C_DEPS += \
./Core/Filters/AvarageFilter.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Filters/%.o Core/Filters/%.su Core/Filters/%.cyclo: ../Core/Filters/%.c Core/Filters/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Core/Filters -I../Core/Sensors -I../Core/PeripheralPorts -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Filters

clean-Core-2f-Filters:
	-$(RM) ./Core/Filters/AvarageFilter.cyclo ./Core/Filters/AvarageFilter.d ./Core/Filters/AvarageFilter.o ./Core/Filters/AvarageFilter.su

.PHONY: clean-Core-2f-Filters

