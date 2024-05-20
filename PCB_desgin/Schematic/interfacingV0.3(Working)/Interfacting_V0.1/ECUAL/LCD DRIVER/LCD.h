/*
 * LCD_DRIVER.h
 *
 * Created: 2/17/2024 1:41:57 AM
 * Author : Sakka
 */ 

#ifndef LCD_H_
#define LCD_H_

#define F_CPU 1000000U


#include <util/delay.h>
#include <stdio.h>
#include <math.h>


#include "../../MCAL/DIO Driver/DIO.h"
#include "../../Utilities/Helpers.h"
#include "../../Utilities/bit_ops.h"




/************************************************************************/
/*                         Driver Macros                                */
/************************************************************************/
#define delay_low _delay_ms(1)
#define delay_high _delay_ms(10)

#define LCD_DATA_PORT PORTB // port B is LCD data port
#define en 7				// enable signal is connected to port D pin 7
#define rw 5				// read/write signal is connected to port D pin 6
#define rs 6				// register select signal is connected to port D pin 5


/************************************************************************/
/*                    Driver Function Prototypes                        */
/************************************************************************/
void LCD_CMD(unsigned char cmd);
void LCD_INIT(void);
void LCD_WRITE_DATA(unsigned char data);
void LCD_CURSOR_POSITION(uint8_t row, uint8_t col);
void LCD_PRINT_INT(unsigned int data,const uint8_t numOfDigits);
void LCD_PRINT_FLOAT(float data,const uint8_t numOfDigits);
void LCD_PRINT_STRING(char st[], uint8_t _size);
void LCD_CLEAR();
void LCD_print_float(float num,uint8_t row,uint8_t column);
unsigned char reverseBits(unsigned char num);



#endif
