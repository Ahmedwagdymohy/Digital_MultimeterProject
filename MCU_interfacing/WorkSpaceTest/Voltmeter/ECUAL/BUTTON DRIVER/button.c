/*
 * button.c
 *
 * Created: 2/24/2024 4:12:35 AM
 *  Author: asus
 */ 
#include "button.h"
void BUTTON_init(uint8_t buttonPort,uint8_t buttonPin){
	DIO_init(buttonPort,buttonPin,IN);
}
void BUTTON_read(uint8_t buttonPort,uint8_t buttonPin,uint8_t *value){
	DIO_read(buttonPort,buttonPin,value);
}