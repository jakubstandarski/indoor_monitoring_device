# Indoor monitoring device

- [Overview](#overview)
    - [Goal](#goal)
    - [Hardware specification](#hardware-specification)
    - [Software specification](#software-specification)



## Overview


### Goal

Goal of this project is to implement simple indoor monitoring device, which
measures basic environmental parameters like temperature, humidity, CO2 gas
concentration, air particles and pressure.

Project is based on the idea of "prototyping", which means that architecture,
code, documentation and even hardware will evolve during its lifetime.


### Hardware specification

Hardware parts needed for this project:

* **Development board**: STM32F407G-DISC1

* **Temperature sensor**: `TODO`

* **Humidity sensor**: `TODO`

* **CO2 sensor**: `TODO`

* **Air particles sensor**: `TODO`

* **Pressure sensor**: `TODO`


### Software specification

Software needed for this project:

* **Operating system**: Ubuntu 20.04 or MacOS

* **Toolchain**: GNU Arm Embedded Toolchain 9-2020-q2-update 9.3.1

* **Build system**: Makefile

* **Embedded programming type**: bare metal

* **Peripherals drivers type**: low layer API provided by ST (STM32CubeF4)

