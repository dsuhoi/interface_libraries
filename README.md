# Interface Libraries
![GitHub repo size](https://img.shields.io/github/repo-size/dsuhoi/interface_libraries)
[![GitHub](https://img.shields.io/github/license/dsuhoi/interface_libraries)](https://github.com/dsuhoi/interface_libraries/blob/master/LICENSE)
>Libraries for working with different interfaces.

### [I2C](i2c/i2c.h)
`I2C` (Inter-Integrated Circuit) is a synchronous, multi-master, multi-slave, packet switched, single-ended,
serial communication bus invented by Philips Semiconductor. It is widely used for attaching lower-speed peripheral
ICs to processors and microcontrollers in short-distance, intra-board communication.

### [TWI](twi/twi.h) (hardware I2C)
This is a hardware version of the `I2C` interface for AVR microcontrollers (ATmega8/328p).

### [SPI](spi/spi.h)
The Serial Peripheral Interface is a synchronous serial communication interface specification used for short-distance communication,
primarily in embedded systems. The interface was developed by Motorola. Typical applications include Secure Digital cards and liquid crystal displays.

### [UART](uart/uart.h)
A universal asynchronous receiver-transmitter is a computer hardware device for asynchronous serial communication in which
the data format and transmission speeds are configurable. The electric signaling levels and methods are handled by a driver circuit external to the `UART`.
One or more `UART` peripherals are commonly integrated in microcontroller chips.

### [1-WIRE](onewire/onewire.h)
`1-wire` is a device communications bus system designed by Dallas Semiconductor Corp. that provides low-speed data, signaling, and power over a single conductor.
`1-wire` is similar in concept to `I2C`, but with lower data rates and longer range. It is typically used to communicate with small
inexpensive devices such as digital thermometers and weather instruments.

### [EEPROM](eeprom/24cxx.h)
`EEPROM` stands for electrically erasable programmable read-only memory and is a type of non-volatile memory used in computers,
integrated in microcontrollers for smart cards and remote keyless systems, and other electronic devices to store relatively small
amounts of data but allowing individual bytes to be erased and reprogrammed.

### [RDA5807FP](rda5807fp/rda5807fp.h)
This is an FM tuner that has an `I2C` interface, stereo audio output, digital audio volume settings, radio frequency,
and is supported by RDS. In addition to the `rda5807fp` library itself, the [AVRadio](rda5807fp/AVRadio) project is attached
(a radio receiver based on an AVR microcontroller, `rda5807fp` and LCD display).

## License
Copyright © 2019 [dsuhoi](https://github.com/dsuhoi).

This project is [GPL-3.0](https://github.com/dsuhoi/interface_libraries/blob/master/LICENSE) licensed.
