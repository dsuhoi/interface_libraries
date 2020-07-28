# Interface Libraries
-----------------------
### The contents of the repository
Libraries for working with different interfaces.
#### I2C interface
I2C (Inter-Integrated Circuit), is a synchronous, multi-master, multi-slave, packet switched, single-ended, serial communication bus invented by Philips Semiconductor. It is widely used for attaching lower-speed peripheral ICs to processors and microcontrollers in short-distance, intra-board communication. ([about I2C](https://en.wikipedia.org/wiki/I%C2%B2C))
#### TWI interface (hardware I2C)
This is a hardware version of the I2C interface for AVR microcontrollers (ATmega8/328p).
#### SPI interface
The Serial Peripheral Interface (SPI) is a synchronous serial communication interface specification used for short-distance communication, primarily in embedded systems. The interface was developed by Motorola. Typical applications include Secure Digital cards and liquid crystal displays. ([about SPI](https://en.wikipedia.org/wiki/Serial_Peripheral_Interface))
#### UART
A universal asynchronous receiver-transmitter (UART) is a computer hardware device for asynchronous serial communication in which the data format and transmission speeds are configurable. The electric signaling levels and methods are handled by a driver circuit external to the UART. One or more UART peripherals are commonly integrated in microcontroller chips. A related device, the universal synchronous and asynchronous receiver-transmitter (USART) also supports synchronous operation. ([about UART](https://en.wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter))
#### 1-WIRE interface
1-Wire is a device communications bus system designed by Dallas Semiconductor Corp. that provides low-speed (16.3 kbit/s[1]) data, signaling, and power over a single conductor. 1-Wire is similar in concept to I²C, but with lower data rates and longer range. It is typically used to communicate with small inexpensive devices such as digital thermometers and weather instruments. ([about 1-WIRE](https://en.wikipedia.org/wiki/1-Wire))
#### EEPROM
EEPROM (also E2PROM) stands for electrically erasable programmable read-only memory and is a type of non-volatile memory used in computers, integrated in microcontrollers for smart cards and remote keyless systems, and other electronic devices to store relatively small amounts of data but allowing individual bytes to be erased and reprogrammed. ([about EEPROM](https://en.wikipedia.org/wiki/EEPROM))
#### RDA5807FP
This is an FM tuner that has an I2C interface, stereo audio output, digital audio volume settings, radio frequency, and is supported by RDS. In addition to the rda5807fp library itself, the AVRadio project is attached (a radio receiver based on an AVR microcontroller, RDA5807FP and LCD display).
