GPIO Device Driver Development on Linux
Overview

This project demonstrates the development of custom Linux GPIO device drivers to control and monitor General Purpose Input/Output (GPIO) pins on an embedded Linux system. The drivers were developed as part of a self-learning initiative to understand low-level hardware control, kernel-space to user-space interaction, and GPIO subsystem integration in Linux.

Features

GPIO configuration and control from kernel space

Support for GPIO input and output operations

Character device interface for user-space interaction

Read and write operations mapped to GPIO pin behavior

Safe data transfer between user space and kernel space

Hardware Used

Raspberry Pi 3B+

LEDs (for output testing)

Push buttons / switches (for input testing)

External resistors (as required)

Software & Tools

Embedded C

Linux Kernel Programming

Linux Kernel Modules

GPIO subsystem

Device Tree Overlays

GCC

Make

Raspberry Pi OS (64-bit)

Driver Functionality:

GPIO pins are requested and configured during module initialization

Output GPIOs:

User writes data to the character device

GPIO pin is set HIGH or LOW accordingly

Input GPIOs:

GPIO pin state is read

Value is returned to user space via read operation

GPIOs are released safely during module removal

User-Space Interface

The driver registers a character device node

User-space applications can:

Write 1 or 0 to control GPIO output

Read GPIO pin status

Driver Architecture

gpio_driver.c – Core GPIO driver implementation

Module initialization and cleanup routines

File operations:

open

read

write

release

GPIO request, direction setting, and value control APIs

How to Build
make

How to Load the Driver
sudo insmod gpio_driver.ko

How to Remove the Driver
sudo rmmod gpio_driver

Debugging
dmesg | tail

Learning Outcomes

This project helped me gain hands-on experience in:

Linux GPIO framework

Character device driver development

GPIO direction and value control

User-kernel space communication

Kernel debugging and logging

Hardware interfacing on embedded Linux

Future Enhancements

Add interrupt-based GPIO input handling

Support multiple GPIO pins via ioctl

Dynamic GPIO configuration using Device Tree

Debouncing logic for input GPIOs

Disclaimer

This project is developed for educational and learning purposes and is not intended for production deployment.

Author

Dinesh Loya
Embedded Engineer
