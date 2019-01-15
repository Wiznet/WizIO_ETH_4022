################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.c \
C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.c \
C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.c \
C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTFormat.c \
C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTPacket.c \
C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.c \
C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.c \
C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.c \
C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.c \
C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.c 

OBJS += \
./Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.o \
./Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.o \
./Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.o \
./Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTFormat.o \
./Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTPacket.o \
./Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.o \
./Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.o \
./Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.o \
./Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.o \
./Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.o 

C_DEPS += \
./Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.d \
./Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.d \
./Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.d \
./Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTFormat.d \
./Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTPacket.d \
./Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.d \
./Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.d \
./Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.d \
./Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.d \
./Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTFormat.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTFormat.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTPacket.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTPacket.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


