/**
 * @file main.c
 * @author Ahmed Wagdy
 * @brief   main program
 * @version 0.2
 * @date 2023-04-01
 *
 * @copyright Copyright (c) 2024
 *
 */
// we will put out implemented functions #include here!!!!! don't forget
#include <stdio.h>
#include <stdlib.h>
#include "ECUAL/KEYPAD DRIVER/Keypad.h"
#include "ohmmeter.h"
#include "ammeter.h"
//#include "ADC.h"
#include "Application/Volt.h"






/***************************************************/
#define F_CPU 8000000UL			    /* Define CPU Frequency e.g. here 8MHz */
#include <avr/io.h>			        /* Include AVR std. library file */
#include <util/delay.h>		       	/* Include inbuilt defined Delay header file */
#include "Ohmmeter.h"
#define LCD_Data_Dir		 DDRB		    /* Define LCD data port direction */
#define LCD_Command_Dir		 DDRD		    /* Define LCD command port direction register */
#define LCD_Data_Port		 PORTB		    /* Define LCD data port */
#define LCD_Command_Port     PORTD		/* Define LCD data port */
#define RS PD5			        	/* Define Register Select (data/command reg.)pin */
#define RW PD6				        /* Define Read/Write signal pin */
#define EN PD7				        /* Define Enable signal pin */

/***************************************************/





// Function prototypes : we will put ours in implementations below!
char get_user_choice();
void ohmmeter_mode();
void voltmeter_mode();
void ammeter_mode();





int main() {
    /***************************************/
    //this is related to my ohmConfigurtaions

    //PORTC |=(1<< 6);
	DDRA |= (1 << 7);
	PORTA |= (1 << 7);
	
	ADC_Initt();
	
	LCD_Initt();

    /***************************************/
    char choice;

    do {
        choice = get_user_choice();

        switch (choice) {
            case '1':
                ohmmeter_mode();
                break;
            case '2':
                voltmeter_mode();
                break;
            case '3':
                ammeter_mode();
                break;
            case '4':
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
                break;
        }
    } while (choice != '66');

    return 0;
}






// Function to get user choice
char get_user_choice() {
	
    char choice;

    LCD_Stringg("1.Ohm");
    LCD_Stringg("  2.Volt");
	LCD_CURSOR_POSITIONN(1,0);
    LCD_Stringg("  3.Ammeter");
    //printf("4. Exit program\n");
    /* ana canceled the exit choice to keep the main list on the screen , no exiting from it , it's a DMM :))*/
    choice = keyfind();
    return choice;
}







// Function to handle Ohmmeter mode
void ohmmeter_mode() {

    char key;
    LCD_Clearr();
    ohm_display();
    LCD_Stringg("  ");
	//PORTD = 0xFF;

    //printf("Ohmmeter mode activated. Press 9 to return to the main menu.\n");
    do {
        key = keyfind();
		if(key == '9'){
			LCD_Clearr();
		}
    } while (key != '9');
}








// Function to handle Voltmeter mode
void voltmeter_mode() {
    char key;
    // Call your Voltmeter function here
	/******* choosing the Mode AC or DC ->>>**************/
	LCD_Clearr();
	
	LCD_Stringg("Choose Mode : ");
	LCD_CURSOR_POSITIONN(1,0);
	LCD_Stringg("1.AC");
	LCD_Stringg("   2.DC");
	/*   storing the value in mode   */
	char mode = keyfind();
	
	/****** choosing the range  ->>>***/
	/*// range 0: 0-5 volt		0	
	// range 1: 0-20 volt		1
	// range 2: 0-200 volt		2
	// range 3: 0-2000 volt		3
	
	*/
	LCD_Clearr();
	//LCD_String("range:");
	LCD_Stringg("0:0-5v ");
	
	LCD_Stringg("1:0-20v ");
	LCD_CURSOR_POSITIONN(1,0);
	LCD_Stringg("2:0-200v");
	LCD_Stringg("3:0-2000v");
	/*   storing the value in range   */
	char range = keyfind();
	
	/* NOW the mode and range values carry the user selections */
	LCD_Clearr();
	LCD_Stringg("The value is : ");
	//LCD_CURSOR_POSITIONN(1,0);
	
	uint8_t range_uint8_char_converted;    // Variable to store the converted value
	uint8_t mode_uint8_char_converted;
	// Convert char to uint8_t
	range_uint8_char_converted = range;
	mode_uint8_char_converted = mode;
	
	Volt_relay(mode_uint8_char_converted,range_uint8_char_converted,VOLT_CH);
	
	
	
	
    //printf("Voltmeter mode activated. Press 9 to return to the main menu.\n");
    do {
        key = keyfind();
		if(key == '9'){
			LCD_Clearr();
		}
    } while (key != '9');
}















// Function to handle Ammeter mode
void ammeter_mode() {
    char key;
    // Call your Ammeter function here
	LCD_Clearr();
	
	LCD_Stringg("Choose Mode : ");
	LCD_CURSOR_POSITIONN(1,0);
	LCD_Stringg("1.AC");
	LCD_Stringg("   2.DC");
	char mode = keyfind();
	
	
	/****** choosing the range  ->>>***/
	/*// range 1: 0-5 mA		0	
	//   range 5: 0-50 mA	1
	//   range 3: 0-4 mA		2
	//  		*/
	
	LCD_Clearr();
	
	
	LCD_Stringg("1:0-5 mA ");
	LCD_Stringg("2:0-50 mA");
	LCD_CURSOR_POSITIONN(1,0);
	LCD_Stringg("3:0-4 mA");
	
	/*   storing the value in range   */
	char range = keyfind();
	
	
	/* NOW the mode and range values carry the user selections */
	LCD_Clearr();
	LCD_Stringg("The value is : ");
	
	Ammeter( range,  mode);
	
	
    //printf("Ammeter mode activated. Press 9 to return to the main menu.\n");
    do {
        key = keyfind();
		if(key == '9'){
			LCD_Clearr();
		}
    } while (key != '9');
}
