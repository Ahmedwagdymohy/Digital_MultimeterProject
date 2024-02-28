/*
 * LCD_DRIVER.c
 *
 * Created: 2/17/2024 1:41:57 AM
 * Author : Sakka
 */ 

#include "LCD.h"

void LCD_CMD(unsigned char cmd)
{
	LCD_DATA_PORT = cmd;
	
	PORTD &= ~(1 << rs); // set RS to 0
	PORTD &= ~(1 << rw); // set RW to 0
	PORTD |= (1 << en);  // make enable high
	delay_low;
	PORTD &= ~(1 << en); // make enable low
}

void LCD_INIT(void)
{
	
	// initialize before while loop
	// Assumed PORTB is for data & PORT
	DDRB = 0xFF;
	DDRD = 0xFF;
	//////////////////////////////////////////////
	LCD_CMD(0x38); // initialize LCD in 8-bit mode
	delay_low;
	LCD_CMD(0x01); // Clear display
	delay_low;
	LCD_CMD(0x02); // return home
	delay_low;
	LCD_CMD(0x06); // make increment in cursor
	delay_low;
	LCD_CMD(0x80); // Go to first line and 0th position
	delay_low;
	delay_high;
	LCD_CMD(0x0C); // display on, cursor off
	delay_high;
}

void LCD_WRITE_DATA(unsigned char data)
{
	LCD_DATA_PORT = data;
	
	PORTD |= (1 << rs);  // set RS to 1
	PORTD &= ~(1 << rw); // set RW to 0
	PORTD |= (1 << en);  // make enable high
	delay_low;
	PORTD &= ~(1 << en); // make enable low
}

void LCD_CURSOR_POSITION(uint8_t row, uint8_t col)
{
	uint8_t address = 0;
	
	if(row == 0)
	{
		address = 0x80;
	}
	else if(row == 1)
	{
		address = 0xC0;
	}
	
	if(col < 16)
	{
		address += col;
	}
	
	LCD_CMD(address);
}

void LCD_PRINT_INT(unsigned int data,const uint8_t numOfDigits)
{
	unsigned char ch[10] = {' '};
	
	for(int j = 0 ; j < numOfDigits ; j++)
	{
		ch[j] = ' ';
	}
	
	itoa(data, ch, 10);
	
	for(int j = 0 ; j < numOfDigits ; ++j)
	{
		if(ch[j] < '0' || ch[j] > '9')
		LCD_WRITE_DATA(' ');
		else
		LCD_WRITE_DATA(ch[j]);
		
	}
}

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

void LCD_PRINT_STRING(char st[], uint8_t _size)
{
	
	for(int i = 0 ; i < _size ; ++i)
	{
		LCD_WRITE_DATA(st[i]);
		delay_low;
	}
}

void LCD_CLEAR()
{
	LCD_CMD(0x01); // Clear display
	delay_low;
	LCD_CMD(0x02); // return home
	delay_low;
	LCD_CMD(0x80); // Go to first line and 0th position
	delay_low;
}

void LCD_print_float(float num,uint8_t row,uint8_t column){
	int c =  get_digit_count((int) num);
	LCD_CURSOR_POSITION(row,column);
	LCD_PRINT_INT((int) num,c);
	LCD_CURSOR_POSITION(row,column+c);
	LCD_WRITE_DATA('.');
	LCD_CURSOR_POSITION(row,column+c+1);
	float dec = (num - (int)num)*100 ;
	LCD_PRINT_INT(round(dec),2);
}
