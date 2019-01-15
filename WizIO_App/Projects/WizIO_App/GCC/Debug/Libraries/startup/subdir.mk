################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/startup/_exit.c \
C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/startup/_initialize_hardware.c \
C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/startup/_reset_hardware.c \
C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/startup/_sbrk.c \
C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/startup/_startup.c \
C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/startup/_syscalls.c \
C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/startup/exception_handlers.c \
C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/startup/vectors_W7500x.c 

OBJS += \
./Libraries/startup/_exit.o \
./Libraries/startup/_initialize_hardware.o \
./Libraries/startup/_reset_hardware.o \
./Libraries/startup/_sbrk.o \
./Libraries/startup/_startup.o \
./Libraries/startup/_syscalls.o \
./Libraries/startup/exception_handlers.o \
./Libraries/startup/vectors_W7500x.o 

C_DEPS += \
./Libraries/startup/_exit.d \
./Libraries/startup/_initialize_hardware.d \
./Libraries/startup/_reset_hardware.d \
./Libraries/startup/_sbrk.d \
./Libraries/startup/_startup.d \
./Libraries/startup/_syscalls.d \
./Libraries/startup/exception_handlers.d \
./Libraries/startup/vectors_W7500x.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/startup/_exit.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/startup/_exit.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/startup/_initialize_hardware.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/startup/_initialize_hardware.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/startup/_reset_hardware.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/startup/_reset_hardware.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/startup/_sbrk.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/startup/_sbrk.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/startup/_startup.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/startup/_startup.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/startup/_syscalls.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/startup/_syscalls.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/startup/exception_handlers.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/startup/exception_handlers.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/startup/vectors_W7500x.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/startup/vectors_W7500x.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


