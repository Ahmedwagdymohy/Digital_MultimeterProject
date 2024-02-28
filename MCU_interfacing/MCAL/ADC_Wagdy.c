/*
 * ADC_Wagdy.c
 *
 * Created: 2/27/2024 3:06:32 AM
 *  Author: study
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
#define F_CPU 8000000UL
#include <util/delay.h>


double vin;
double vout;
unsigned int value;
char output[6];

void ADC_INIT()
{
	DDRA=0x0;			/* Make ADC port as input */
	ADCSRA = 0x87;			/* Enable ADC, fr/128  */
	ADMUX = 0x40;			/* Vref: Avcc, ADC channel: 0 */
	
}

float ADC_READ(char channel)
{
	float Ain,AinLow;
	
	ADMUX=ADMUX|(channel & 0x0f);	/* Set input channel to read */

	ADCSRA |= (1<<ADSC);		/* Start conversion */
	while((ADCSRA&(1<<ADIF))==0);	/* Monitor end of conversion interrupt */
	
	_delay_us(10);
	AinLow = (float)ADCL;		/* Read lower byte*/
	Ain = (float)ADCH*256;		/* Read higher 2 bits and 
					Multiply with weight */
	Ain = Ain + AinLow;				
	return(Ain);			/* Return digital value*/
}



char current(void)
{
	ADMUX|=(1<<0);
	ADCSRA|=(1<<6);
	while(ADIF==0);
	value=ADCL|ADCH<<8;
	vout=value*0.00488;            //To determine output voltage from sensor
	vin=(vout-2.5)/0.185;          //To determine real current
	
	itoa(vin,output,10);           //Float to char conversion for itoa
	return output;
}