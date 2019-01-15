copy /b /y obj\W7500x_Application_App.bin bin\
copy /b /y obj\W7500x_Application_App.hex bin\
copy /b /y ..\Boot\bin\W7500x_Application_Boot.hex + bin\W7500x_Application_App.hex ..\W7500x_Application_All.hex
..\hex2bin.exe ..\W7500x_Application_All.hex

