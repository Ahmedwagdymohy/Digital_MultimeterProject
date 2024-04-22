/*
 * Volt.c
 *
 * Created: 2/28/2024 5:12:59 AM
 *  Author: asus
 */ 
#include "Volt.h"



void Volt_relay(uint8_t mode, uint8_t range,uint8_t volt_ch){
	ADC_init(volt_ch);
	//LCD_INIT();
	//LCD_CURSOR_POSITION(0,0);
	
	bitset(SELECTOR_DIR,RELAY_VSEL);
	bitset(SELECTOR_DIR,MUX_VOL_SELH);
	bitset(SELECTOR_DIR,RELAY_VRANGE);
	bitset(SELECTOR_DIR,MUX_VOL_SELL);
	bitset(SELECTOR_DIR,RELAY_MUX_SEL);

	if (mode == 1){
		bitset(SELECTOR_DIR,RELAY_VSEL);
		bitclear(SELECTOR_DATA,RELAY_VSEL);
		//LCD_PRINT_STRING("Voltmeter DC",12);
	}
	else if (mode == 0)
	{
		bitset(SELECTOR_DIR,RELAY_VSEL);
		bitset(SELECTOR_DATA,RELAY_VSEL);
		//LCD_PRINT_STRING("Voltmeter AC",12);
	}
	switch (range)
	{
		case 0:
		bitclear(SELECTOR_DATA,MUX_VOL_SELL);
		bitclear(SELECTOR_DATA,MUX_VOL_SELH);
		bitset(SELECTOR_DATA,RELAY_MUX_SEL);
		break;
		case 1:
		bitset(SELECTOR_DATA,RELAY_MUX_SEL);
		bitset(SELECTOR_DATA,MUX_VOL_SELL);
		bitclear(SELECTOR_DATA,MUX_VOL_SELH);
		break;
		case 2:
		bitset(SELECTOR_DATA,RELAY_MUX_SEL);
		bitclear(SELECTOR_DATA,MUX_VOL_SELL);
		bitset(SELECTOR_DATA,MUX_VOL_SELH);
		break;
		case 3:
		bitclear(SELECTOR_DIR,MUX_VOL_SELH);
		bitclear(SELECTOR_DIR,MUX_VOL_SELL);
		bitclear(SELECTOR_DATA,RELAY_MUX_SEL);
		bitclear(SELECTOR_DATA,RELAY_VRANGE);
		break;
	}
	int *value;
	ADC_read(volt_ch,value);
	float A_value = ((float) *value)* (5.0/1024.0);
	switch(range){
		case 0:
		A_value = A_value * 1;
		break;
		case 1:
		A_value = A_value * (20/4.5);
		break;
		case 2:
		A_value = A_value * (200/4.5);
		break;
		case 3:
		A_value = A_value * (2000/4.5);
		break;
	}
	LCD_print_float(A_value,1,0);
	
}


