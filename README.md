# USBKeyboard
## Introduction
USBKeyboard is a library for the Arduino IDE. It adds HID USB keyboard functionality to your projects, allowing Arduinos and other AVRs to act as a HID USB Devices.  
Due to its HID protocol no drivers have to be installed, the USB keyboard connection will work with every PC and OS.

## Getting Started
Connect your Arduino to the USB connector following the given schematic below and add a pushbutton betwen D7 and GND. Copy this repository into your `libraries` folder and (re)start the Arduino IDE.  
Open `File > Examples > USBKeyboard > USBKeyboard_GettingStarted` and upload it to your Arduino.  
Unplug your Arduino from your PC and plug in the USB connector. The keyboard should be recognized automatically by your PC, open a text editor of your choice and push the button afterwards, a message will be typed in.

## Schematic
[![Schematic](https://petrockblog.files.wordpress.com/2012/05/wpid-photo-19-05-2012-22201.jpg "Schematic for the Arduino UNO")](https://petrockblog.files.wordpress.com/2012/05/wpid-photo-19-05-2012-22201.jpg)

You just need the zener diodes if your Arduino/AVR is running above 3.6V  
(following the USB specification 3.6V is the maximum for D+ and D-).

## Reference
This library is based on the [V-USB code](https://www.obdev.at/products/vusb/) by Objective Developement.

## License
As the V-USB code, this library is licensed under GNU GPLv3, see [`LICENSE.txt`](LICENSE.txt) for further information.
