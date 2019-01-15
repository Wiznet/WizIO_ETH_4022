copy /b /y obj\W7500x_Application_Boot.bin bin\
copy /b /y obj\W7500x_Application_Boot.hex bin\
copy /b /y bin\W7500x_Application_Boot.hex + ..\App\bin\W7500x_Application_App.hex ..\W7500x_Application_All.hex
..\hex2bin.exe ..\W7500x_Application_All.hex

