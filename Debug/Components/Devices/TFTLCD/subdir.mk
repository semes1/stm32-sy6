################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Components/Devices/TFTLCD/lcd.c \
../Components/Devices/TFTLCD/lcd_init.c 

OBJS += \
./Components/Devices/TFTLCD/lcd.o \
./Components/Devices/TFTLCD/lcd_init.o 

C_DEPS += \
./Components/Devices/TFTLCD/lcd.d \
./Components/Devices/TFTLCD/lcd_init.d 


# Each subdirectory must supply rules for building sources it contributes
Components/Devices/TFTLCD/%.o Components/Devices/TFTLCD/%.su Components/Devices/TFTLCD/%.cyclo: ../Components/Devices/TFTLCD/%.c Components/Devices/TFTLCD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/llyy/STM32CubeIDE/workspace_1.11.2/F407VET6_test/Components/Devices/TFTLCD" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Components-2f-Devices-2f-TFTLCD

clean-Components-2f-Devices-2f-TFTLCD:
	-$(RM) ./Components/Devices/TFTLCD/lcd.cyclo ./Components/Devices/TFTLCD/lcd.d ./Components/Devices/TFTLCD/lcd.o ./Components/Devices/TFTLCD/lcd.su ./Components/Devices/TFTLCD/lcd_init.cyclo ./Components/Devices/TFTLCD/lcd_init.d ./Components/Devices/TFTLCD/lcd_init.o ./Components/Devices/TFTLCD/lcd_init.su

.PHONY: clean-Components-2f-Devices-2f-TFTLCD

