/**
 * @file LCD.h
 * @author AhmedWagdyMohy
 * @brief 
 * @version 0.1
 * @date 2024-02-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#ifndef LCD_H_
#define LCD_H_

/**
 * @brief defining the main ports used in the LCD
 * 
 */
#define LCD_Data_Dir                DDRB		            /*  LCD data port direction */
#define LCD_Command_Dir             DDRC		            /*  LCD command port direction register */
#define LCD_Data_Port               PORTB		            /*  LCD data port */
#define LCD_Command_Port            PORTC		            /*  LCD data port */
#define RS                          PC0			            /*  Register Select (data/command reg.)pin */
#define RW                          PC1				        /*  Read/Write signal pin */
#define EN                          PC2	                    /*  Enable signal pin */
/** < We use portB & PortC   oneFor Data and one for controlSignals */





/***********************************************************************************************************************************************/
/*****************************************************< ListOfCommands for LCD >**************************************************************/
/**********************************************************************************************************************************************/

/*    Code(HEX)	Command to LCD	Execution Time
        0x01	Clear the display screen	1.64ms
        0x06	Shift the cursor right (e.g. data gets written in an incrementing order, left to right)	40 us
        0x0C	Display on, cursor off	40 us
        0x0E	Display on, cursor blinking	40 us
        0x80	Force the cursor to the beginning of the 1st line	40 us
        0xC0	Force the cursor to the beginning of the 2nd line	40 us
        0x10	Shift cursor position to the left	40 us
        0x14	Shift cursor position to the right	40 us
        0x18	Shift entire display to the left	40 us
        0x1C	Shift entire display to the right	40 us
        0x38	2 lines, 5x8 matrix, 8-bit mode	40 us
        0x28	2 lines, 5x8 matrix,4-bit mode	40 us
        0x30	1 line, 8-bit mode	40us
        0x20	1 line, 4-bit mode	40us                                                       */



/**
 * @brief using the upove ↑↑↑↑↑↑↑↑↑↑↑↑ commands to make the LCD do what we want 
 * 
 * @param cmnd 
 */
void LCD_Command(unsigned char cmnd);







/**
 * @brief intializing the LCD 
 * 
 */
void LCD_Init (void);








/**
 * @brief       sending a Char to the LCD ( as we know the LCD receives Charachters only not WORDS)
 * 
 * @param       char_data 
 */
void LCD_Char (unsigned char char_data);







/**
 * @brief     Making the LCD Display a string ( using LOOP to send the string char by char)
 * 
 * @param str 
 */
void LCD_String (char *str)	;
















#endif /*< LCH_H_*/