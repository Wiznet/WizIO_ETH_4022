################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/RemoteIO/subdir.mk
-include src/PlatformHandler/subdir.mk
-include src/Modbus/subdir.mk
-include src/Configuration/subdir.mk
-include src/Callback/subdir.mk
-include src/subdir.mk
-include Libraries/startup/subdir.mk
-include Libraries/ioLibrary/Internet/TFTP/subdir.mk
-include Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/subdir.mk
-include Libraries/ioLibrary/Internet/MQTT/subdir.mk
-include Libraries/ioLibrary/Internet/DNS/subdir.mk
-include Libraries/ioLibrary/Internet/DHCP/subdir.mk
-include Libraries/ioLibrary/Ethernet/subdir.mk
-include Libraries/ioLibrary/Application/loopback/subdir.mk
-include Libraries/W7500x_StdPeriph_Driver/src/subdir.mk
-include Libraries/CMSIS/Device/WIZnet/W7500/Source/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
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
SECONDARY_FLASH += \
WizIO_App.bin \

SECONDARY_SIZE += \
WizIO_App.siz \


# All Target
all: WizIO_App.elf secondary-outputs

# Tool invocations
WizIO_App.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM GNU C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -T "C:\Users\boomw\Downloads\WizIO\WizIO_App\Projects\WizIO_App\GCC\ldscripts\libs.ld" -T "C:\Users\boomw\Downloads\WizIO\WizIO_App\Projects\WizIO_App\GCC\ldscripts\mem.ld" -T "C:\Users\boomw\Downloads\WizIO\WizIO_App\Projects\WizIO_App\GCC\ldscripts\sections.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"WizIO_App.map" --specs=nano.specs -o "WizIO_App.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

WizIO_App.bin: WizIO_App.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary "WizIO_App.elf"  "WizIO_App.bin"
	@echo 'Finished building: $@'
	@echo ' '

WizIO_App.siz: WizIO_App.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "WizIO_App.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) WizIO_App.elf
	-@echo ' '

post-build:
	-arm-none-eabi-objcopy -O ihex "WizIO_App.elf" "WizIO_App.hex";arm-none-eabi-objcopy -O srec "WizIO_App.elf" "WizIO_App.srec"
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents post-build

-include ../makefile.targets
