/*
 * ammeter_wagdy.h
 *
 * Created: 4/22/2024 11:23:15 AM
 *  Author: study
 */ 


#ifndef AMMETER_WAGDY_H_
#define AMMETER_WAGDY_H_


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
/*void LCD_PRINT_INT( int data,const unsigned int numOfDigits);*/





/*
* @brief ADC functions
*/
void ADC_Init();
int  ADC_Read(char channel);





/*
* @brief ohm functions used in main
*/
void ammeter_display(char mode, char range);






#endif /* AMMETER_WAGDY_H_ */