################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Ethernet/socket.c \
C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Ethernet/wizchip_conf.c 

OBJS += \
./Libraries/ioLibrary/Ethernet/socket.o \
./Libraries/ioLibrary/Ethernet/wizchip_conf.o 

C_DEPS += \
./Libraries/ioLibrary/Ethernet/socket.d \
./Libraries/ioLibrary/Ethernet/wizchip_conf.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/ioLibrary/Ethernet/socket.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Ethernet/socket.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/ioLibrary/Ethernet/wizchip_conf.o: C:/Users/boomw/Downloads/WizIO/WizIO_App/Libraries/ioLibrary/Ethernet/wizchip_conf.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\MQTT\MQTTPacket\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Internet\TFTP" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\startup" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Callback" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Configuration" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\Modbus" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\PlatformHandler" -I"C:\Users\boomw\Downloads\WizIO\WizIO_App\src\RemoteIO" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


