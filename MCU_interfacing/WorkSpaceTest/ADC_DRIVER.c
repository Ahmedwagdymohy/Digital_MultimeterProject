/*
 * ADC_DRIVER.c
 *
 * Created: 2/17/2024 1:41:57 AM
 * Author : Sakka
 */ 


#include <stdlib.h>
#include <avr/io.h>
#include "ADC.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "STD_TYPES.h"
#include "LCD.h"
#include "KEYPAD.h"
#include "ADC_DRIVER.h"
void ADC_INIT(void)
{
	DDRA = 0x00;				// Initialize PORTA as input
	/////////////////////////////////////////////////////////
	ADMUX  |= (1 << REFS0);		// voltage reference from AVCC
	ADCSRA |= (1 << ADEN);		// turn on ADC
	ADCSRA |= (1 << ADSC);
	ADCSRA |= ( (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) );  // 16MHz / 128 = 125 KHz --> ADC reference clock
}

u16 ADC_READ(u8 channel)
{
	ADMUX &= 0xF0;					// Clear older version
	ADMUX |= channel;				// Defines the new ADC channel to be read
	ADCSRA |= (1 << ADSC);			// starts a new conversion (single conversion)
	while(ADCSRA & (1 << ADSC));	// wait until the conversion is done
	
	return (ADC);					// returns the ADC value of the chosen channel
}