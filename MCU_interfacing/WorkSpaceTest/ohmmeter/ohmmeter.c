/*
 * Ohmmeter.c
 *
 * Created: 2/28/2024 8:57:41 PM
 *  Author: study
 */ 
#include "Ohmmeter.h"
#define F_CPU 8000000UL			/* Define CPU Frequency e.g. here 8MHz */
#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>			/* Include inbuilt defined Delay header file */

#define LCD_Data_Dir DDRB		/* Define LCD data port direction */
#define LCD_Command_Dir DDRC		/* Define LCD command port direction register */
#define LCD_Data_Port PORTB		/* Define LCD data port */
#define LCD_Command_Port PORTC		/* Define LCD data port */
#define RS PC0				/* Define Register Select (data/command reg.)pin */
#define RW PC1				/* Define Read/Write signal pin */
#define EN PC2




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

void LCD_Char (unsigned char char_data)	/* LCD data write function */
{
	LCD_Data_Port= char_data;
	LCD_Command_Port |= (1<<RS);	/* RS=1 Data reg. */
	LCD_Command_Port &= ~(1<<RW);	/* RW=0 write operation */
	LCD_Command_Port |= (1<<EN);	/* Enable Pulse */
	_delay_us(5);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(5);
}



//*************************************************************************************************
void LCD_WRITE_DATA(unsigned char data)
{
	LCD_Data_Port = data;
	
	PORTC |= (1 << RS);  // set RS to 1
	PORTC &= ~(1 << RW); // set RW to 0
	PORTC |= (1 << EN);  // make enable high
	_delay_us(5);
	PORTC &= ~(1 << EN); // make enable low
}



//*************************************************************************************************
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

void LCD_String (char *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		LCD_Char(str[i]);
	}
}

void LCD_String_xy (char row, char pos, char *str)/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	LCD_Command((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	LCD_Command((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	LCD_String(str);		/* Call LCD string function */
}

void LCD_Clear()
{
	LCD_Command (0x01);		/* clear display */
	LCD_Command (0x80);		/* cursor at home position */
}


void ADC_Init()
{
	DDRA=0x0;			/* Make ADC port as input */
	ADCSRA = 0x87;			/* Enable ADC, fr/128  */
	ADMUX = 0x40;			/* Vref: Avcc, ADC channel: 0 */
	
}

int ADC_Read(char channel)
{
	int Ain,AinLow;
	
	ADMUX=ADMUX|(channel & 0x0f);	/* Set input channel to read */

	ADCSRA |= (1<<ADSC);		/* Start conversion */
	while((ADCSRA&(1<<ADIF))==0);	/* Monitor end of conversion interrupt */
	
	_delay_us(10);
	AinLow = (int)ADCL;		/* Read lower byte*/
	Ain = (int)ADCH*256;		/* Read higher 2 bits and 
					Multiply with weight */
	Ain = Ain + AinLow;				
	return(Ain);			/* Return digital value*/
}
//*********************************************************************************
void LCD_PRINT_INT( int data, const unsigned int numOfDigits)
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





char String[6];
int value;

double realvolt;
int resisreq;
		/* Initialization of LCD */
/* Write string on 1st line of LCD */

char buffer[25];

void ohm_display(){
	/* LCD16x2 cursor position */
	value=ADC_Read(0);	/* Read ADC channel 0 */ // this function returns integer of the binary
	//after getting the value of the ADCREAD it retruns integer with ration   5v --> 1023 & 2.5v --> 512     and so on
	//creating a function to make this equation
	if (value < 26){ //above 25k ohm
		realvolt = ((value * 5.0) / 1023);
		resisreq = (5/(realvolt))-(1+10);
		LCD_Command(0x80);
		LCD_String("in Kohms is: ");
		LCD_Command(0xC0);
		LCD_PRINT_INT(resisreq , 6);
		
	}
	else{
		realvolt = ((value * 5.0) / 1023);
		/*************** NOTE that the LCD has a max value of integer to print which is 16360*********/
		resisreq = (5/(realvolt/1000.0))-(1000+10000);
		if(resisreq< 10000 && resisreq> 0){
			//0x80	Force the cursor to the beginning of the 1st line
			//0xC0	Force the cursor to the beginning of the 2nd line
			LCD_Command(0x80);
			LCD_String("in ohms is: ");
			LCD_Command(0xC0);
			LCD_PRINT_INT(resisreq , 6);
		}
		else if( resisreq > 10000 ) {
			LCD_Command(0x80);
			LCD_String("in Kohms is: ");
			LCD_Command(0xC0);
			LCD_PRINT_INT(resisreq/1000 , 6);
			
			}else if (resisreq < 50){
			LCD_Command(0x80);
			LCD_String("the value is ");
			LCD_Command(0xC0);
			LCD_String(" below 50ohm ");
			}else{
			LCD_Command(0x80);
			LCD_String("Error !");
		}
		
	}
}