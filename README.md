# uvc
UV-C Disinfection Controller and Enclosure
(C) Dave White, PE - 2020

# License
MIT License. See license file for more info

# Description
The UV-C Disinfection Controller and Enclosure is a device
that dispenses measured amounts of UV-C irradiance for the
purpose of disinfection small items. It does this by combining
UVC-band ballast/lamps, a Silicon-carbide UV-C sensor (blind to visible, 
UVA/UVB light), and electronics that form a "total dose accumulator" and
controller. It is a prototype, and **not a listed or certified medical device.** 
For detailed information on its construction consult the photos, assembly 
drawings, and bill of materials (BOM). For detailed info 
on its safe operation, see the manual folder.

# Firmware
The firmware relies on the use of Mbed OS, a C++ based 
embedded operating system and hardware abstraction layer (HAL),
atop an ST Micro STM32F746ZG ARM Cortex M7 microcontroller. 
Note that the hardware is 100% overkill for this application,
the MCU is just what happened to be lying around. See "firmware"
folder for usable binaries, as well as the source code. The
main program lives here:
    *\uvc\firmware\uvc_controller\main.cpp*

# Contact
For questions, please contact me through github **@davewhiiite**, or my
Twitter handle: **@daveswarez**

