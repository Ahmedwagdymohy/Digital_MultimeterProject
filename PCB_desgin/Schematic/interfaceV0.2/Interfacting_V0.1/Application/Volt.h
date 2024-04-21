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

#define DATA_PORT 'D'



#define RELAY_VRANGE 0
#define MUX_VOL_SELH 1
#define MUX_VOL_SELL 2
#define RELAY_MUX_SEL 3
#define RELAY_VSEL 4


void Volt_relay(uint8_t mode, uint8_t range,uint8_t volt_ch);




#endif /* VOLT_H_ */