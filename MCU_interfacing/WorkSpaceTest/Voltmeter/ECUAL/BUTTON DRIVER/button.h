/*
 * button.h
 *
 * Created: 2/24/2024 4:12:45 AM
 *  Author: asus
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "../../MCAL/DIO Driver/DIO.h"
#define BUTTON_1_PORT PORT_C
#define BUTTON_1_PIN PIN_4

#define BUTTON_2_PORT PORT_D
#define BUTTON_2_PIN PIN_7

void BUTTON_init(uint8_t buttonPort,uint8_t buttonPin);
void BUTTON_read(uint8_t buttonPort,uint8_t buttonPin,uint8_t *value);





#endif /* BUTTON_H_ */