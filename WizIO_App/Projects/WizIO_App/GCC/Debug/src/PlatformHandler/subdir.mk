################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/boomw/Downloads/WizIO/WizIO_App/src/PlatformHandler/analog_handler.c \
C:/Users/boomw/Downloads/WizIO/WizIO_App/src/PlatformHandler/digital_handler.c \
C:/Users/boomw/Downloads/WizIO/WizIO_App/src/PlatformHandler/flash_handler.c \
C:/Users/boomw/Downloads/WizIO/WizIO_App/src/PlatformHandler/gpio_handler.c \
C:/Users/boomw/Downloads/WizIO/WizIO_App/src/PlatformHandler/storage_handler.c \
C:/Users/boomw/Downloads/WizIO/WizIO_App/src/PlatformHandler/timer_handler.c \
C:/Users/boomw/Downloads/WizIO/WizIO_App/src/PlatformHandler/uart_handler.c 

OBJS += \
./src/PlatformHandler/analog_handler.o \
./src/PlatformHandler/digital_handler.o \
./src/PlatformHandler/flash_handler.o \
./src/PlatformHandler/gpio_handler.o \
./src/PlatformHandler/storage_handler.o \
./src/PlatformHandler/timer_handler.o \
./src/PlatformHandler/uart_handler.o 

C_DEPS += \
./src/PlatformHandler/analog_handler.d \
./src/PlatformHandler/digital_handler.d \
./src/PlatformHandler/flash_handler.d \
./src/PlatformHandler/gpio_handler.d \
./src/PlatformHandler/storage_handler.d \
./src/PlatformHandler/timer_handler.d \
./src/PlatformHandler/uart_handler.d 


# Each subdirectory must supply rules for building sources it contributes
src/PlatformHandler/analog_handler.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/src/PlatformHandler/analog_handler.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/PlatformHandler/digital_handler.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/src/PlatformHandler/digital_handler.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/PlatformHandler/flash_handler.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/src/PlatformHandler/flash_handler.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/PlatformHandler/gpio_handler.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/src/PlatformHandler/gpio_handler.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/PlatformHandler/storage_handler.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/src/PlatformHandler/storage_handler.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/PlatformHandler/timer_handler.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/src/PlatformHandler/timer_handler.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/PlatformHandler/uart_handler.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/src/PlatformHandler/uart_handler.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


