/*
 * ADC.c
 *
 * Created: 2/24/2024 6:55:03 AM
 *  Author: asus
 */ 
#include "ADC.h"

void ADC_init(uint8_t adc_ch){
	bitclear(DDRA,adc_ch);// set ADC channel to be input
	bitset(ADMUX,6); // Set VREF to be VCC
	bitset(ADCSRA,7); // Enable ADC
	bitset(ADCSRA,2);
	bitset(ADCSRA,1);
	bitset(ADCSRA,0);
	
}
void ADC_read(uint8_t adc_ch,int *value){
	ADMUX |= (adc_ch & 0x0F);
	bitset(ADCSRA,6);
	while((ADCSRA&(1<<4))==0);
	//*value = (ADCH<<8) | ADCL;
	// 	*valuel = ADCL;
	// 	*valueh = ADCH;
	uint8_t valuel = ADCL;
	uint8_t valueh = ADCH;
	uint16_t v  = (valueh << 8) | valuel;
	*value = (int) v;
	
}
