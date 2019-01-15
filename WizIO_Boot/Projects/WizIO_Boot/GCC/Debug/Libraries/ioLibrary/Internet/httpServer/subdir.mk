################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/boomw/Downloads/W7500x_Platform_Firmware-master/W7500x_Platform_Firmware-master/Libraries/ioLibrary/Internet/httpServer/httpParser.c \
C:/Users/boomw/Downloads/W7500x_Platform_Firmware-master/W7500x_Platform_Firmware-master/Libraries/ioLibrary/Internet/httpServer/httpServer.c \
C:/Users/boomw/Downloads/W7500x_Platform_Firmware-master/W7500x_Platform_Firmware-master/Libraries/ioLibrary/Internet/httpServer/httpUtil.c 

OBJS += \
./Libraries/ioLibrary/Internet/httpServer/httpParser.o \
./Libraries/ioLibrary/Internet/httpServer/httpServer.o \
./Libraries/ioLibrary/Internet/httpServer/httpUtil.o 

C_DEPS += \
./Libraries/ioLibrary/Internet/httpServer/httpParser.d \
./Libraries/ioLibrary/Internet/httpServer/httpServer.d \
./Libraries/ioLibrary/Internet/httpServer/httpUtil.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/ioLibrary/Internet/httpServer/httpParser.o: C:/Users/boomw/Downloads/W7500x_Platform_Firmware-master/W7500x_Platform_Firmware-master/Libraries/ioLibrary/Internet/httpServer/httpParser.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\ioLibrary\Internet\httpServer" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\startup" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\src" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/ioLibrary/Internet/httpServer/httpServer.o: C:/Users/boomw/Downloads/W7500x_Platform_Firmware-master/W7500x_Platform_Firmware-master/Libraries/ioLibrary/Internet/httpServer/httpServer.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\ioLibrary\Internet\httpServer" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\startup" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\src" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Libraries/ioLibrary/Internet/httpServer/httpUtil.o: C:/Users/boomw/Downloads/W7500x_Platform_Firmware-master/W7500x_Platform_Firmware-master/Libraries/ioLibrary/Internet/httpServer/httpUtil.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\CMSIS\Include" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\CMSIS\Device\WIZnet\W7500\Include" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\ioLibrary\Application\loopback" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\ioLibrary\Ethernet" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\ioLibrary\Internet\DHCP" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\ioLibrary\Internet\DNS" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\ioLibrary\Internet\httpServer" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\startup" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\Libraries\W7500x_StdPeriph_Driver\inc" -I"C:\Users\boomw\Downloads\W7500x_Platform_Firmware-master\W7500x_Platform_Firmware-master\src" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


