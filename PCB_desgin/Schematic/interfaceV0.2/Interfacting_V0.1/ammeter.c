/*
 * GccApplication1.c
 *
 * Created: 2/17/2024 1:41:57 AM
 * Author : Sakka
 */ 


#define F_CPU 16000000UL // CPU 16 MHZ

#define pinWriteHIGH(pin) PORTA |= (1 << pin)
#define pinWriteLow(pin) PORTA &= ~(1 << pin)

#include <avr/io.h>
#include <avr/delay.h>


#define delay_low _delay_ms(1)
#define delay_high _delay_ms(10)

////// ADC

#define LCD_DATA_PORT PORTB // port B is LCD data port

#define en PD7				// enable signal is connected to port D pin 7
#define rw PD6				// read/write signal is connected to port D pin 6
#define rs PD5				// register select signal is connected to port D pin 5

void ADC_INIT_saka(void)
{
	DDRA = 0x00;				// Initialize PORTA as input
	/////////////////////////////////////////////////////////
	ADMUX  |= (1 << REFS0);		// voltage reference from AVCC
	ADCSRA |= (1 << ADEN);		// turn on ADC
	ADCSRA |= (1 << ADSC);
	ADCSRA |= ( (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) );  // 16MHz / 128 = 125 KHz --> ADC reference clock
}

uint16_t ADC_READ_saka(uint8_t channel)
{
	ADMUX &= 0xF0;					// Clear older version
	ADMUX |= channel;				// Defines the new ADC channel to be read
	ADCSRA |= (1 << ADSC);			// starts a new conversion (single conversion)
	while(ADCSRA & (1 << ADSC));	// wait until the conversion is done
	
	return (ADC);					// returns the ADC value of the chosen channel
}

/////// LCD

void LCD_CMD_saka(unsigned char cmd)
{
	LCD_DATA_PORT = cmd;
	
	PORTD &= ~(1 << rs); // set RS to 0
	PORTD &= ~(1 << rw); // set RW to 0
	PORTD |= (1 << en);  // make enable high
	delay_low;
	PORTD &= ~(1 << en); // make enable low
}

void LCD_INIT_saka(void)
{
	
	// initialize before while loop
	// Assumed PORTB is for data & PORT
	DDRB = 0xFF;
	DDRD = 0xFF;
	//////////////////////////////////////////////
	LCD_CMD_saka(0x38); // initialize LCD in 8-bit mode
	delay_low;
	LCD_CMD_saka(0x01); // Clear display
	delay_low;
	LCD_CMD_saka(0x02); // return home
	delay_low;
	LCD_CMD_saka(0x06); // make increment in cursor
	delay_low;
	LCD_CMD_saka(0x80); // Go to first line and 0th position
	delay_low;
	delay_high;
	LCD_CMD_saka(0x0C); // display on, cursor off
	delay_high;
}

void LCD_WRITE_DATA_saka(unsigned char data)
{
	LCD_DATA_PORT = data;
	
	PORTD |= (1 << rs);  // set RS to 1
	PORTD &= ~(1 << rw); // set RW to 0
	PORTD |= (1 << en);  // make enable high
	delay_low;
	PORTD &= ~(1 << en); // make enable low
}

void LCD_CURSOR_POSITION_saka(uint8_t row, uint8_t col)
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
	
	LCD_CMD_saka(address);
}

void LCD_PRINT_INT_saka(unsigned int data,const uint8_t numOfDigits)
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
		LCD_WRITE_DATA_saka(' ');
		else
		LCD_WRITE_DATA_saka(ch[j]);
	}
}

void LCD_PRINT_FLOAT_saka(float data,const uint8_t numOfDigits)
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
		LCD_WRITE_DATA_saka(' ');
		else
		LCD_WRITE_DATA_saka(ch[j]);
	}
}

void LCD_PRINT_STRING_saka(char st[], uint8_t _size)
{
	
	for(int i = 0 ; i < _size ; ++i)
	{
		LCD_WRITE_DATA_saka(st[i]);
		delay_low;
	}
}

void LCD_CLEAR_saka()
{
	LCD_CMD_saka(0x01); // Clear display
	delay_low;
	LCD_CMD_saka(0x02); // return home
	delay_low;
	LCD_CMD_saka(0x80); // Go to first line and 0th position
	delay_low;
}

////////// AMMETER

void Ammeter_Init(char mode)
{
	LCD_INIT_saka();
	ADC_INIT_saka();
	
	//LCD_CURSOR_POSITION_saka(0,0);
	//LCD_PRINT_STRING_saka("Current value : ",16);
	
	//LCD_CURSOR_POSITION_saka(1,13);
	//LCD_PRINT_STRING_saka("9->",3);
	
	DDRA = 0xFF;
	PORTA = 0xFF;
	DDRA &= ~(1 << DDA0); // To make PA0 input
	
	/*
		if mode == 1	--> DC
		if mode == 2	--> AC
	*/
	
	if(mode == '1')
	{
		pinWriteLow(PORTA5);
	}
	else if(mode == '2')
	{
		pinWriteHIGH(PORTA5);
	}
}

char Ammeter(char range, char mode)
{
	/**
	*
	*	1K		0 --> 5 mA
	*	100		0 --> 50mA
	*	1		0 --> 4A
	*
	*	PA5 selection of DC/AC (RelayISel)
	*	PA4 selection of 100/1 Ohm
	*	PA3 selection of 1K/ ...	
	*
	****///
	
	double value;
	double factor;
	uint8_t keypadValue;
	
	Ammeter_Init(mode);
	
	if(range == '1')
	{
		// range of 1K Ohm
		// 0 --> 5 (mA)
		
		//factor = 207067.92;
		factor = 0.005 / 1024.0;
		
		// TODO : switch Relays.
		pinWriteLow(PORTA3);
		pinWriteLow(PORTA4);

	}
	else if(range == '2')
	{
		// range of 100 Ohm
		// 0 --> 50 (mA)
		
		//factor = 20740.66918;
		factor = 0.05 / 1024.0;
		
		// TODO : switch Relays.
		pinWriteHIGH(PORTA3);
		pinWriteLow(PORTA4);
		
	}
	else if(range == '3')
	{
		// range of 1 Ohm
		// 0 --> 4 (A)
		
		//factor = 248.947;
		factor = 4.0 / 1024.0;
		//factor = 1;
		
		// TODO : switch Relays.
		pinWriteHIGH(PORTA3);
		pinWriteHIGH(PORTA4);
	}
	else
	{
		return 0;
	}
	
	while(1)
	{
		LCD_CURSOR_POSITION_saka(1,0);
		value = ADC_READ_saka(1) * factor;
		LCD_PRINT_FLOAT_saka(value, 6);
		
		// keypadValue;
		if(keypadValue == '9')
		{
			break;
		}
		
	}
	
	return 1;
}


