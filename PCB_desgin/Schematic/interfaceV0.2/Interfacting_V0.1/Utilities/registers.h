/*
 * registers.h
 *
 * Created: 2/24/2024 2:32:14 AM
 *  Author: asus
 */ 
/************************************************************************/
/*                  ALL MICROCONTROLLERS REGISTERS                     */
/************************************************************************/

#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "types.h"

/************************************************************************/
/* DIO REGISTERS                                                          */
/************************************************************************/

// PORT A Registers
#define PORTA *((volatile uint8_t* ) 0x3B)
#define DDRA *((volatile uint8_t* ) 0x3A)
#define PINA *((volatile uint8_t* ) 0x39)

// PORT B Registers
#define PORTB *((volatile uint8_t* ) 0x38)
#define DDRB *((volatile uint8_t* ) 0x37)
#define PINB *((volatile uint8_t* ) 0x36)

// PORT C Registers
#define PORTC *((volatile uint8_t* ) 0x35)
#define DDRC *((volatile uint8_t* ) 0x34)
#define PINC *((volatile uint8_t* ) 0x33)

// PORT D Registers
#define PORTD *((volatile uint8_t* ) 0x32)
#define DDRD *((volatile uint8_t* ) 0x31)
#define PIND *((volatile uint8_t* ) 0x30)

/************************************************************************/
/*                               ADC REGISTERS                          */
/************************************************************************/
#define ADMUX *((volatile uint8_t* ) 0x27)
#define ADCSRA *((volatile uint8_t* ) 0x26)
#define ADCH *((volatile uint8_t* ) 0x25)
#define ADCL *((volatile uint8_t* ) 0x24)

#endif /* REGISTERS_H_ */