### Communicating from MacOS

In OS X 10.9 and up, and in some installations of windows, the operating systems have installed a virtual com port driver for the FTDI chip used by the kilobots. The KiloGUI can use this virtual serial port, by choosing the serial port. However, for best results we recommend disabling the virtual com port entirely, and allow KiloGUI to connect to the FTDI chip directly.
How to do this:

In OS X, the FTDI driver can be temporally disabled by the following command
```
sudo kextunload -b com.apple.driver.AppleUSBFTDI.
```

Enter this command into a terminal window. Note that every time you shut down your computer and start back up, you will need to redo this.
In Windows, you must use the device manager to uninstall the virtual serial driver, and then install the libusb driver (link).

## Maximum speed

It is important that in a 2 second interval no motor is at 100% duty-cycle (255) for more than 50ms at a time, since this might cause the motors to fail permanently. It is recommended that during regular operation the motors are never run to more than a 35% duty-cycle (90).


# Sequence

- bootload  (approach to the robot and wait)
- upload (approach to the bot and wait until dim flickering)
- run


# Charging
- Blue and green: to sleep
- yellow and red: turn off manually
- leave approx 2 hours a day for charging (~50 bots)



# Experiment workflow

- pick only blue and green
- max 2hours run
- checck voltage wih Kilobot Toolkit
- move to charge yellow and red
- flashing and idle:
  - check physicially the battery voltage
  - if volage>2.5, reset
