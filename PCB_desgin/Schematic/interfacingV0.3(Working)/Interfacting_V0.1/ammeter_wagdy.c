/*
 * ammeter_wagdy.c
 *
 * Created: 4/22/2024 11:22:15 AM
 *  Author: study
 */ 


#define LCD_Data_Dir       DDRB			/* Define LCD data port direction */
#define LCD_Command_Dir    DDRD			/* Define LCD command port direction register */
#define LCD_Data_Port      PORTB		/* Define LCD data port */
#define LCD_Command_Port   PORTD		/* Define LCD data port */
#define RS PD5							/* Define Register Select (data/command reg.)pin */
#define RW PD6							/* Define Read/Write signal pin */
#define EN PD7




void LCD_Commandd(unsigned char cmnd)
{
	LCD_Data_Port= cmnd;
	LCD_Command_Port &= ~(1<<RS);	/* RS=0 command reg. */
	LCD_Command_Port &= ~(1<<RW);	/* RW=0 Write operation */
	LCD_Command_Port |= (1<<EN);	/* Enable pulse */
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(3);
}

void LCD_Charr (unsigned char char_data)	/* LCD data write function */
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
void LCD_WRITE_DATAA(unsigned char data)
{
	LCD_Data_Port = data;

	PORTD |= (1 << RS);  // set RS to 1
	PORTD &= ~(1 << RW); // set RW to 0
	PORTD |= (1 << EN);  // make enable high
	_delay_us(5);
	PORTD &= ~(1 << EN); // make enable low
}



//*************************************************************************************************
void LCD_Initt (void)			/* LCD Initialize function */
{
	LCD_Command_Dir = 0xFF;		/* Make LCD command port direction as o/p */
	LCD_Data_Dir = 0xFF;		/* Make LCD data port direction as o/p */
	_delay_ms(20);			/* LCD Power ON delay always >15ms */

	LCD_Commandd (0x38);		/* Initialization of 16X2 LCD in 8bit mode */
	LCD_Commandd (0x0C);		/* Display ON Cursor OFF */
	LCD_Commandd (0x06);		/* Auto Increment cursor */
	LCD_Commandd (0x01);		/* Clear display */
	LCD_Commandd (0x80);		/* Cursor at home position */
}

void LCD_Stringg (char *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		LCD_Charr(str[i]);
	}
}

void LCD_String_xy (char row, char pos, char *str)/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	LCD_Commandd((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	LCD_Commandd((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	LCD_Stringg(str);					/* Call LCD string function */
}

void LCD_Clearr()
{
	LCD_Commandd (0x01);		/* clear display */
	LCD_Commandd (0x80);		/* cursor at home position */
}

void LCD_CURSOR_POSITIONN(uint8_t row, uint8_t col)
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
	
	LCD_Commandd(address);
}





/************************************************************************************************************/


void ADC_Initt() {
	// Configure the first 3 pins of port A as ADC inputs
	DDRA &= ~(0b00000111);  // Set PA0, PA1, and PA2 as input

	// Set the other pins of port A (PA3 to PA7) as output
	DDRA |= 0b11111000;  // Set PA3 to PA7 as output

	// Set all output pins of port A to high
	PORTA |= 0b10000000; // Set PA3 to PA7 high

	// Enable ADC, set ADC clock division factor to 128
	ADCSRA = 0x87;

	// Set ADC reference voltage to AVCC and ADC channel to 0
	ADMUX = 0x40;
}



int ADC_Readd(char channel)
{
	int Ain,AinLow;

	ADMUX=ADMUX|(channel & 0x0f);	/* Set input channel to read */

	ADCSRA |= (1<<ADSC);		    /* Start conversion */
	while((ADCSRA&(1<<ADIF))==0);	/* Monitor end of conversion interrupt */

	_delay_us(10);
	AinLow = (int)ADCL;		    /* Read lower byte*/
	Ain = (int)ADCH*256;		/* Read higher 2 bits and
					               Multiply with weight */
	Ain = Ain + AinLow;
	return(Ain);			    /* Return digital value*/
}
//*********************************************************************************
void LCD_PRINT_INTT( int data, const unsigned int numOfDigits)
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
		LCD_WRITE_DATAA(' ');
		else
		LCD_WRITE_DATAA(ch[j]);

	}
}





char String[6];
int value;

double realvolt;
int resisreq;
		/* Initialization of LCD */
/* Write string on 1st line of LCD */

char buffer[25];

void ammeter_display(char mode, char range){
	/* LCD16x2 cursor position */
	value=ADC_Readd(1);	/* Read ADC channel 0 */ // this function returns integer of the binary
	//after getting the value of the ADCREAD it retruns integer with ration   5v --> 1023 & 2.5v --> 512     and so on
	//creating a function to make this equation
	if (range == '1'){ 
		
		
		

	}else if(range == '2'){
		//range 2 goes here
		
		
	}else if (range == '3'){
		//range 3 goes here
		
		
	}
	

	}

