/*
 * GccApplication1.c
 *
 * Created: 4/20/2024 1:41:57 AM
 * Author : Sakka
 */ 

#ifndef AMMETER_H
#define AMMETER_H


#define F_CPU 16000000UL // CPU 16 MHZ

#include "ECUAL/LCD DRIVER/LCD_DRIVER.c"
#include "MCAL/ADC Driver/ADC_DRIVER.c"

#define pinWriteHIGH(pin) PORTA |= (1 << pin)
#define pinWriteLow(pin) PORTA &= ~(1 << pin)

void Ammeter_Init(uint8_t mode);

char Ammeter(uint8_t range, uint8_t mode);


#endif