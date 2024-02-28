/*
 * Volt.c
 *
 * Created: 2/28/2024 5:12:59 AM
 *  Author: asus
 */ 
#include "Volt.h"

void Volt_init(uint8_t volt_ch,uint8_t mode,uint8_t range){
	uint8_t range1 = bitcheck(range,1);
	uint8_t range0 = bitcheck(range,0);
	
	ADC_init(volt_ch);
	LCD_INIT();
	LCD_CURSOR_POSITION(0,0);
	bitset(SELECTOR_DIR,AC_DC_SWITCH);
	bitset(SELECTOR_DIR,RANGE_SWITCH0);
	bitset(SELECTOR_DIR,RANGE_SWITCH1);
	
	if (mode == 0){
		bitclear(SELECTOR_DATA,AC_DC_SWITCH);
		LCD_PRINT_STRING("Voltmeter AC",12);
	}
	else if (mode == 1)
	{
		bitset(SELECTOR_DATA,AC_DC_SWITCH);
		LCD_PRINT_STRING("Voltmeter DC",12);
	}
	if (range0 == 0){
		bitclear(SELECTOR_DATA,RANGE_SWITCH0);
	}
	else if (range0 == 1)
	{
		bitset(SELECTOR_DATA,RANGE_SWITCH0);
	}
	if (range1 == 0){
		bitclear(SELECTOR_DATA,RANGE_SWITCH1);
	}
	else if (range1 == 1)
	{
		bitset(SELECTOR_DATA,RANGE_SWITCH1);
	}
	
}

void Volt_display(uint8_t volt_ch,int *value,uint8_t range){
	
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