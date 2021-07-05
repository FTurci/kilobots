### Communicating from MacOS

In OS X 10.9 and up, and in some installations of windows, the operating systems have installed a virtual com port driver for the FTDI chip used by the kilobots. The KiloGUI can use this virtual serial port, by choosing the serial port. However, for best results we recommend disabling the virtual com port entirely, and allow KiloGUI to connect to the FTDI chip directly. 
How to do this: 

In OS X, the FTDI driver can be temporally disabled by the following command 
```
sudo kextunload -b com.apple.driver.AppleUSBFTDI. 
```

Enter this command into a terminal window. Note that every time you shut down your computer and start back up, you will need to redo this. 
In Windows, you must use the device manager to uninstall the virtual serial driver, and then install the libusb driver (link).

## Further
