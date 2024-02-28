/**
 * @file main_ohmmeter.c
 * @author AhmedWagdy 
 * @brief 
 * @version 0.1
 * @date 2024-02-28
 * 
 * @copyright Copyright (c) 2024
 * 
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



int main(){
    
    char String[5];
	int value;

	ADC_INIT();
	LCD_Init();			/* Initialization of LCD */
	LCD_String("ADC value");	/* Write string on 1st line of LCD */
    /**Making portD and portC as output*/
    DDRD = 0xFF;
    DDRC = 0xFF; 
    


    while(1){

        
        PORTD= 0xFF;
        PORTC= 0xFF;
        LCD_Command(0xc4);	/* LCD16x2 cursor position */
		value=ADC_READ(0);	/* Read ADC channel 0 */
		itoa(value,String,10);	/* Integer to string conversion */ 
		LCD_String(String);						
		LCD_String("  ");	



    }





    return 0 ;
}






















