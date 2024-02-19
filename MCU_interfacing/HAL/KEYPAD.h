/**
 * @file KEYPAD.h
 * @author AhmedWagdy
 * @brief 
 * @version 0.1
 * @date 2024-02-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#ifndef KEYPAD_H_
#define KEYPAD_H_



#define KEY_PRT 	PORTA
#define KEY_DDR		DDRA
#define KEY_PIN		PINA




unsigned char keypad[4][4] = {	{'7','8','9','/'},
				                {'4','5','6','*'},
			                	{'1','2','3','-'},
			                	{' ','0','=','+'}};

unsigned char colloc, rowloc;





char keyfind();







#endif
