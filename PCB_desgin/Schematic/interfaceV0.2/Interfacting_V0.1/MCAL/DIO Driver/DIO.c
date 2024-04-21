/*
 * DIO.c
 *
 * Created: 2/24/2024 2:52:52 AM
 *  Author: asus
 */ 
// include .h
#include "DIO.h"

// global variables
// function definitions
void DIO_init(uint8_t portNumber,uint8_t pinNumber,uint8_t direction){
	switch(portNumber){
		case PORT_A:
		if (direction == IN)
		{
			bitclear(DDRA,pinNumber);
		}
		else if(direction == OUT){
			bitset(DDRA,pinNumber);
		}
		else{
			//error handling
		}
		
		break;
		case PORT_B:
		if (direction == IN)
		{
			bitclear(DDRB,pinNumber);
		}
		else if(direction == OUT){
			bitset(DDRB,pinNumber);
		}
		else{
			//error handling
		}
		break;
		case PORT_C:
		if (direction == IN)
		{
			bitclear(DDRC,pinNumber);
		}
		else if(direction == OUT){
			bitset(DDRC,pinNumber);
		}
		else{
			//error handling
		}
		break;
		case PORT_D:
		if (direction == IN)
		{
			bitclear(DDRD,pinNumber);
		}
		else if(direction == OUT){
			bitset(DDRD,pinNumber);
		}
		else{
			//error handling
		}
		break;
	}
}
void DIO_write(uint8_t portNumber,uint8_t pinNumber,uint8_t value){
	switch(portNumber){
		case PORT_A:
		if (value == LOW)
		{
			bitclear(PORTA,pinNumber);
		}
		else if(value == HIGH){
			bitset(PORTA,pinNumber);
		}
		else{
			//error handling
		}
		break;
		case PORT_B:
		if (value == LOW)
		{
			bitclear(PORTB,pinNumber);
		}
		else if(value == HIGH){
			bitset(PORTB,pinNumber);
		}
		else{
			//error handling
		}
		break;
		case PORT_C:
		if (value == LOW)
		{
			bitclear(PORTC,pinNumber);
		}
		else if(value == HIGH){
			bitset(PORTC,pinNumber);
		}
		else{
			//error handling
		}
		break;
		case PORT_D:
		if (value == LOW)
		{
			bitclear(PORTD,pinNumber);
		}
		else if(value == HIGH){
			bitset(PORTD,pinNumber);
		}
		else{
			//error handling
		}
		break;
	}
}
void DIO_toggle(uint8_t portNumber,uint8_t pinNumber){
	switch(portNumber){
		case PORT_A:
		bitflip(PORTA,pinNumber);
		break;
		case PORT_B:
		bitflip(PORTB,pinNumber);
		break;
		case PORT_C:
		bitflip(PORTC,pinNumber);
		break;
		case PORT_D:
		bitflip(PORTD,pinNumber);
		break;
	}
}
void DIO_read(uint8_t portNumber,uint8_t pinNumber,uint8_t *value){
	switch (portNumber)
	{
	case PORT_A:
	*value = bitcheck(PINA,pinNumber);
	break;
	case PORT_B:
	*value = bitcheck(PINB,pinNumber);
	break;
	case PORT_C:
	*value = bitcheck(PINC,pinNumber);
	//*value = (PINC & (1<<pinNumber))>>pinNumber;
	break;
	case PORT_D:
	*value = bitcheck(PIND,pinNumber);
	break;
	default:
	break;
	}
}