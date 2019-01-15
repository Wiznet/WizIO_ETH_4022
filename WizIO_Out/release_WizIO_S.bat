copy ..\WizIO_Boot\Projects\WizIO_Boot\GCC\Debug\WizIO_Boot.hex .\\WizIO_Boot.hex
copy ..\WizIO_App\Projects\WizIO_App\GCC\Debug\WizIO_App.hex .\\WizIO_App.hex
srec_cat WizIO_Boot.hex -intel WizIO_App.hex -intel -o WizIO.hex -intel
HEX2BIN.exe .\\WizIO.hex
