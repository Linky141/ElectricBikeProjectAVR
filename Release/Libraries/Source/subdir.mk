################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/Source/delay.c \
../Libraries/Source/gpio.c \
../Libraries/Source/lcd.c 

OBJS += \
./Libraries/Source/delay.o \
./Libraries/Source/gpio.o \
./Libraries/Source/lcd.o 

C_DEPS += \
./Libraries/Source/delay.d \
./Libraries/Source/gpio.d \
./Libraries/Source/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Source/%.o: ../Libraries/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=1600000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


