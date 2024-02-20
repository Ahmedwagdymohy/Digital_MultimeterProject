/**
 * @file LCD.c
 * @author AhmedWagdyMohy
 * @brief 
 * @version 0.1
 * @date 2024-02-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "LCD.h"



#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>			/* Include inbuilt defined Delay header file */



 

/**
 * @brief using the upove commands <"inTheHeaderFile"> to make the LCD do what we want
 * 
 * @param cmnd 
 */

void LCD_Command(unsigned char cmnd)
{
	LCD_Data_Port= cmnd;
	LCD_Command_Port &= ~(1<<RS);	/* RS=0 command reg. */
	LCD_Command_Port &= ~(1<<RW);	/* RW=0 Write operation */
	LCD_Command_Port |= (1<<EN);	/* Enable pulse */
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(3);
}
















/**
 * @brief   sending a Char to the LCD ( as we know the LCD receives Charachters only not WORDS)
 * 
 * @param char_data 
 */

void LCD_Char (unsigned char char_data)	/* LCD data write function */
{
	LCD_Data_Port= char_data;
	LCD_Command_Port |= (1<<RS);	/* RS=1 Data reg. */
	LCD_Command_Port &= ~(1<<RW);	/* RW=0 write operation */
	LCD_Command_Port |= (1<<EN);	/* Enable Pulse */
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(1);
}
















/**
 * @brief intializing the LCD
 * 
 */

void LCD_Init (void)			/* LCD Initialize function */
{
	LCD_Command_Dir = 0xFF;		/* Make LCD command port direction as o/p */
	LCD_Data_Dir = 0xFF;		/* Make LCD data port direction as o/p */
	_delay_ms(20);			/* LCD Power ON delay always >15ms */
	
	LCD_Command (0x38);		/* Initialization of 16X2 LCD in 8bit mode */
	LCD_Command (0x0C);		/* Display ON Cursor OFF */
	LCD_Command (0x06);		/* Auto Increment cursor */
	LCD_Command (0x01);		/* Clear display */
	LCD_Command (0x80);		/* Cursor at home position */
}



/**
 * @brief Making the LCD Display a string ( using LOOP to send the string char by char)
 * 
 * @param str 
 */
void LCD_String (char *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);
	}
}














/**
 * @brief  Clearing the LCD
 * 
 */
void LCD_Clear()
{
	LCD_Command (0x01);		/* clear display */
	LCD_Command (0x80);		/* cursor at home position */
}
 


/**
 * @brief 	prints float numbers
 * 
 * @param data      
 * @param numOfDigits    
 */

void LCD_PRINT_FLOAT(float data,const uint8_t numOfDigits)
{
	unsigned char ch[10] = {' '};
	
	for(int j = 0 ; j < numOfDigits ; j++)
	{
		ch[j] = ' ';
	}
	
	sprintf(ch, "%4.3f", data);  // this values are changeable
	
	for(int j = 0 ; j < numOfDigits ; ++j)
	{
		if((ch[j] != '.') && (ch[j] < '0' || ch[j] > '9'))
		LCD_WRITE_DATA(' ');
		else
		LCD_WRITE_DATA(ch[j]);
	}
}
