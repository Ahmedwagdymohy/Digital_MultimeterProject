/*
 * ohmmeter_test_NOTVIP.c
 *
 * Created: 2/28/2024 2:35:01 AM
 * Author : AhmedWagdy
 */ 


/*
***************************************************************************
****___****__***********************__** _ ******__****************__******
   /   |  / /_**____*___**___**____/ /**| |     / ____*_____*_____/ __**__
  / /| | / __ \/ __ `__ \/ _ \/ __  /***| | /| / / __ `/ __ `/ __  / / / /
 / ___ |/ / / / / / / / /  __/ /_/ /****| |/ |/ / /_/ / /_/ / /_/ / /_/ /*
/_/  |_/_/ /_/_/ /_/ /_/\___/\__,_/*****|__/|__/\__,_/\__, /\__,_/\__, /**
**************************************************** /____/*******____/***
**************************************************************************
*/






/*******<LIB************/
#define F_CPU 8000000UL			/* Define CPU Frequency e.g. here 8MHz */
#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>			/* Include inbuilt defined Delay header file */
#include "Ohmmeter.h"




/********<defines**************/
#define LCD_Data_Dir 					DDRB		/* Define LCD data port direction */
#define LCD_Command_Dir 				DDRC		/* Define LCD command port direction register */
#define LCD_Data_Port 					PORTB		/* Define LCD data port */
#define LCD_Command_Port				PORTC		/* Define LCD data port */
#define RS							    PC0				/* Define Register Select (data/command reg.)pin */
#define RW							    PC1				/* Define Read/Write signal pin */
#define EN							    PC2				/* Define Enable signal pin */
 




 


 /**
  * @brief Main function goes here!
  * 
  * @return int 
  */


int main()
{	/**Makin D as OUTPUT & HIGH the 6th and 7th pin in portC*/
	DDRD = 0xFF;
	PORTC |=(1<< 6);
	PORTC |=(1<< 7);
	ADC_Init();
	LCD_Init();
	
	while(1)
	{
		
		ohm_display();
			
		  
		  
		
		LCD_String("  ");
		PORTD = 0xFF;
	}
	return 0;
}
