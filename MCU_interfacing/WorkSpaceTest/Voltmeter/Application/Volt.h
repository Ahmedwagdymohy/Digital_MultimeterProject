/*
 * Volt.h
 *
 * Created: 2/28/2024 5:12:50 AM
 *  Author: asus
 */ 




#ifndef VOLT_H_
#define VOLT_H_

#include "../ECUAL/LCD DRIVER/LCD.h"
#include "../MCAL/ADC Driver/ADC.h"


#define VOLT_CH ADC_CH_0

#define SELECTOR_DIR DDRD
#define SELECTOR_DATA PORTD

/* range definitions
// mode 0: ac
// mode 1: dc
// range 0: 0-5 volt 00
// range 1: 0-20 volt 01
// range 2: 0-200 volt 10
// range 3: 0-2000 volt 11
*/


#define RANGE_SWITCH0 0
#define RANGE_SWITCH1 1
#define AC_DC_SWITCH 2

void Volt_init(uint8_t volt_ch,uint8_t mode,uint8_t range);
void Volt_display(uint8_t volt_ch,int *value,uint8_t range);



#endif /* VOLT_H_ */