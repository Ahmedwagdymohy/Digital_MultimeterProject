/*
 * LCD_DRIVER.h
 *
 * Created: 2/17/2024 1:41:57 AM
 * Author : Sakka
 */ 

#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

#include <avr/io.h>
#include <avr/delay.h>


#define delay_low _delay_ms(1)
#define delay_high _delay_ms(10)

// PORTS are depending on the circuit

#define LCD_DATA_PORT PORTB // port B is LCD data port

#define en PD7				// enable signal is connected to port D pin 7
#define rw PD6				// read/write signal is connected to port D pin 6
#define rs PD5				// register select signal is connected to port D pin 5


void LCD_CMD(unsigned char cmd);

void LCD_INIT(void);

void LCD_WRITE_DATA(unsigned char data);

void LCD_CURSOR_POSITION(uint8_t row, uint8_t col);

void LCD_PRINT_INT(unsigned int data,const uint8_t numOfDigits);

void LCD_PRINT_FLOAT(float data,const uint8_t numOfDigits);

void LCD_PRINT_STRING(char st[], uint8_t _size);

void LCD_CLEAR();


#endif
