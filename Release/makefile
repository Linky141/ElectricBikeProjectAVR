################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include SOURCE/subdir.mk
-include Libraries/Source/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
ElectricBike.lss \

FLASH_IMAGE += \
ElectricBike.hex \

EEPROM_IMAGE += \
ElectricBike.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: ElectricBike.elf secondary-outputs

# Tool invocations
ElectricBike.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ElectricBike.map -mmcu=atmega328p -o "ElectricBike.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ElectricBike.lss: ElectricBike.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ElectricBike.elf  >"ElectricBike.lss"
	@echo 'Finished building: $@'
	@echo ' '

ElectricBike.hex: ElectricBike.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ElectricBike.elf  "ElectricBike.hex"
	@echo 'Finished building: $@'
	@echo ' '

ElectricBike.eep: ElectricBike.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex ElectricBike.elf  "ElectricBike.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ElectricBike.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p ElectricBike.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ElectricBike.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
