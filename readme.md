# Digital Multimeter Device
Creating DMM used to measure electrical quantities using AVR Microcontroller (Atmega32) 
# Description
DMM, measures and verifies multiple electrical quantities, including voltage, current and resistance
# Usage
Include all the header file needed for every device of example

```c
#include "ohmmeter.h"
#include "volttmeter.h"
#include "ammeter.h"
#include "LCD.h"
#include "ADC.h"
#include "KEYBAD.h"
```
Every Device has a Core function should be called in the main.c to start measuring and showing on LDC
```c
//for Ohmmeter
ohm_display();


//for voltmeter
Volt_display(VOLT_CH,&value,range);
//

```
