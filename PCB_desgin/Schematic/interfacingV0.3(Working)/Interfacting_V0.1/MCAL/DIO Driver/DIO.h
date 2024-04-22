/*
 * DIO.h
 *
 * Created: 2/24/2024 2:53:04 AM
 *  Author: asus
 */ 


#ifndef DIO_H_
#define DIO_H_
#include "../../Utilities/registers.h"
#include "../../Utilities/bit_ops.h"
#include "../../Utilities/types.h"
// internal driver typedefs
/************************************************************************/
/*                         Driver Macros                                */
/************************************************************************/ 
#define PORT_A 'A'
#define PORT_B 'B'
#define PORT_C 'C'
#define PORT_D 'D'

#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7
// Direction defines
#define IN 0
#define OUT 1

// Value defines
#define LOW 0
#define HIGH 1


/************************************************************************/
/*                    Driver Function Prototypes                        */
/************************************************************************/

void DIO_init(uint8_t portNumber,uint8_t pinNumber,uint8_t direction); //set dio direction
void DIO_write(uint8_t portNumber,uint8_t pinNumber,uint8_t value); //write to dio
void DIO_toggle(uint8_t portNumber,uint8_t pinNumber);// toggled dio
void DIO_read(uint8_t portNumber,uint8_t pinNumber,uint8_t *value);//read_dio



#endif /* DIO_H_ */