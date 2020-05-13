################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SOURCE/PWM.c \
../SOURCE/main.c 

OBJS += \
./SOURCE/PWM.o \
./SOURCE/main.o 

C_DEPS += \
./SOURCE/PWM.d \
./SOURCE/main.d 


# Each subdirectory must supply rules for building sources it contributes
SOURCE/%.o: ../SOURCE/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=1600000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


