/*
 * GccApplication1.c
 *
 * Created: 20/4/2024 1:41:57 AM
 * Author : Sakka
 */ 

#include "ammeter.h"

void Ammeter_Init(uint8_t mode)
{
	LCD_INIT();
	ADC_INIT();
	
	LCD_CURSOR_POSITION(0,0);
	LCD_PRINT_STRING("Current value : ",16);
	
	LCD_CURSOR_POSITION(1,13);
	LCD_PRINT_STRING("9->",3);
	
	DDRA = 0xFF;
	PORTA = 0xFF;
	DDRA &= ~(1 << DDA0); // To make PA0 input
	
	/*
		if mode == 1	--> DC
		if mode == 2	--> AC
	*/
	
	if(mode == 1)
	{
		pinWriteHIGH(PORTA5);
	}
	else if(mode == 2)
	{
		pinWriteLow(PORTA5);
	}
}

char Ammeter(uint8_t range, uint8_t mode)
{
	/**
	*
	*	1K		0 --> 5 mA
	*	100		0 --> 50mA
	*	1		0 --> 4A
	*
	*	PA5 selection of DC/AC (RelayISel)
	*	PA4 selection of 100/1 Ohm
	*	PA3 selection of 1K/ ...	
	*
	****///
	
	double value;
	double factor;
	uint8_t keypadValue;
	
	Ammeter_Init(mode);
	
	if(range == 1)
	{
		// range of 1K Ohm
		// 0 --> 5 (mA)
		
		//factor = 207067.92;
		factor = 0.005 / 1024.0;
		
		// TODO : switch Relays.
		pinWriteLow(PORTA3);
		pinWriteLow(PORTA4);

	}
	else if(range == 2)
	{
		// range of 100 Ohm
		// 0 --> 50 (mA)
		
		//factor = 20740.66918;
		factor = 0.05 / 1024.0;
		
		// TODO : switch Relays.
		pinWriteHIGH(PORTA3);
		pinWriteLow(PORTA4);
		
	}
	else if(range == 3)
	{
		// range of 1 Ohm
		// 0 --> 4 (A)
		
		//factor = 248.947;
		factor = 4.0 / 1024.0;
		//factor = 1;
		
		// TODO : switch Relays.
		pinWriteHIGH(PORTA3);
		pinWriteHIGH(PORTA4);
	}
	else
	{
		return 0;
	}
	
	while(1)
	{
		LCD_CURSOR_POSITION(1,0);
		value = ADC_READ(0) * factor;
		LCD_PRINT_FLOAT(value, 6);
		



		// get keypadValue;



		if(keypadValue == '9')
		{
			break;
		}
		
	}
	
	return 1;
}


