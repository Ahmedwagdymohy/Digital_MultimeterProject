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
#include "KEYBAD.h"
#include "ohmmeter.h"





/***************************************************/
#define F_CPU 8000000UL			    /* Define CPU Frequency e.g. here 8MHz */
#include <avr/io.h>			        /* Include AVR std. library file */
#include <util/delay.h>		       	/* Include inbuilt defined Delay header file */
#include "Ohmmeter.h"
#define LCD_Data_Dir DDRB		    /* Define LCD data port direction */
#define LCD_Command_Dir DDRC		/* Define LCD command port direction register */
#define LCD_Data_Port PORTB		    /* Define LCD data port */
#define LCD_Command_Port PORTC		/* Define LCD data port */
#define RS PC0			        	/* Define Register Select (data/command reg.)pin */
#define RW PC1				        /* Define Read/Write signal pin */
#define EN PC2				        /* Define Enable signal pin */

/***************************************************/





// Function prototypes : we will put ours in implementations below!
char get_user_choice();
void ohmmeter_mode();
void voltmeter_mode();
void ammeter_mode();





int main() {
    /***************************************/
    //this is related to my ohmConfigurtaions

    PORTC |=(1<< 6);
	PORTC |=(1<< 7);
	ADC_Init();
	LCD_Init();

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

    LCD_String("1.Ohm");
    LCD_String("  2.Volt");
	LCD_CURSOR_POSITION(1,0);
    LCD_String("  3.Ammeter");
    //printf("4. Exit program\n");
    /* ana canceled the exit choice to keep the main list on the screen , no exiting from it , it's a DMM :))*/
    choice = keyfind();
    return choice;
}







// Function to handle Ohmmeter mode
void ohmmeter_mode() {

    char key;
    LCD_Clear();
    ohm_display();
    LCD_String("  ");
	PORTD = 0xFF;

    //printf("Ohmmeter mode activated. Press 9 to return to the main menu.\n");
    do {
        key = keyfind();
		if(key == '9'){
			LCD_Clear();
		}
    } while (key != '9');
}








// Function to handle Voltmeter mode
void voltmeter_mode() {
    char key;
    // Call your Voltmeter function here
	/******* choosing the Mode AC or DC ->>>**************/
	LCD_Clear();
	
	LCD_String("Choose Mode : ");
	LCD_CURSOR_POSITION(1,0);
	LCD_String("1.AC");
	LCD_String("   2.DC");
	/*   storing the value in mode   */
	char mode = keyfind();
	
	/****** choosing the range  ->>>***/
	/*// range 0: 0-5 volt		0	
	// range 1: 0-20 volt		1
	// range 2: 0-200 volt		2
	// range 3: 0-2000 volt		3
	
	*/
	LCD_Clear();
	//LCD_String("range:");
	LCD_String("0:0-5v ");
	
	LCD_String("1:0-20v ");
	LCD_CURSOR_POSITION(1,0);
	LCD_String("2:0-200v");
	LCD_String("3:0-2000v");
	/*   storing the value in range   */
	char range = keyfind();
	/* NOW the mode and range values carry the user selections */
	LCD_Clear();
	
	
	
	
    //printf("Voltmeter mode activated. Press 9 to return to the main menu.\n");
    do {
        key = keyfind();
		if(key == '9'){
			LCD_Clear();
		}
    } while (key != '9');
}















// Function to handle Ammeter mode
void ammeter_mode() {
    char key;
    // Call your Ammeter function here
    //printf("Ammeter mode activated. Press 9 to return to the main menu.\n");
    do {
        key = keyfind();
		if(key == '9'){
			LCD_Clear();
		}
    } while (key != '9');
}
