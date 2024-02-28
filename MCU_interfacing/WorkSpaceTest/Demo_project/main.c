/*
 * ohmmeter.c
 *
 * Created: 2/26/2024 2:29:31 AM
 * Author : study
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


int main(void)
{
    DDRC = 0xFF; //make all port C as output
	
	ADC_INIT();
	LCD_Init();
	char string [10];
	int value;
	int valueOfResis;
    while (1) 
    {
		PORTC = PORTC | (1<<3);
		PORTC = PORTC | (1<<1);
		PORTC = PORTC | (1<<2);
		PORTC = PORTC | (1<<0);	 //High the Pin 3
		value = ADC_READ(0);
		valueOfResis = value /(0.2);
		itoa(value,string,15 );
		LCD_String(string);
    }
}

