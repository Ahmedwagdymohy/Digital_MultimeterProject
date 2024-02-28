/*
 * led.h
 *
 * Created: 2/24/2024 3:44:30 AM
 *  Author: asus
 */ 


#ifndef LED_H_
#define LED_H_

#include "../../MCAL/DIO Driver/DIO.h"

#define LED_1_PORT PORT_A
#define LED_1_PIN PIN_0

void LED_init(uint8_t ledPort,uint8_t ledPin);
void LED_on(uint8_t ledPort,uint8_t ledPin);
void LED_off(uint8_t ledPort,uint8_t ledPin);
void LED_toggle(uint8_t ledPort,uint8_t ledPin);


#endif /* LED_H_ */