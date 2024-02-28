/*
 * First_Project.c
 *
 * Created: 2/23/2024 11:28:31 PM
 * Author : asus
 */ 

#include "Application/Volt.h"



int main(void)
{
    /* Replace with your application code */
	uint8_t mode = 0;
	uint8_t range = 2;
	Volt_init(VOLT_CH,mode,range);
	int value;
    while (1) 
    {
		Volt_display(VOLT_CH,&value,range);

		
    }
}

