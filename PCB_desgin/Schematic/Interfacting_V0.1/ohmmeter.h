/*
 * Ohmmeter.h
 *
 * Created: 2/28/2024 8:57:58 PM
 *  Author: study
 */


#ifndef OHMMETER_H_
#define OHMMETER_H_

/*
* @brief LCD functions
*/

void LCD_Command(unsigned char cmnd);
void LCD_Command(unsigned char cmnd);
void LCD_Char (unsigned char char_data);
void LCD_WRITE_DATA(unsigned char data);
void LCD_Init (void);
void LCD_String (char *str);
void LCD_String_xy (char row, char pos, char *str);
void LCD_Clear();
void LCD_PRINT_INT( int data,const unsigned int numOfDigits);





/*
* @brief ADC functions
*/
void ADC_Init();
int  ADC_Read(char channel);





/*
* @brief ohm functions used in main
*/
void ohm_display();



#endif /* OHMMETER_H_ */
