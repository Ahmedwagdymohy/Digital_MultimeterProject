/*
 * ADC.h
 *
 * Created: 2/24/2024 6:54:53 AM
 *  Author: asus
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "../../Utilities/registers.h"
#include "../../Utilities/bit_ops.h"
#include "../../Utilities/types.h"
/************************************************************************/
/*                         Driver Macros                                */
/************************************************************************/
#define ADC_CH_0 0
#define ADC_CH_1 1
#define ADC_CH_2 2
#define ADC_CH_3 3
#define ADC_CH_4 4
#define ADC_CH_5 5
#define ADC_CH_6 6
#define ADC_CH_7 7



/************************************************************************/
/*                    Driver Function Prototypes                        */
/************************************************************************/
void ADC_init(uint8_t adc_ch);
//void ADC_read(uint8_t adc_ch,uint16_t *value);
void ADC_read(uint8_t adc_ch,int *value);
//void ADC_DAC(uint8_t valuel,uint8_t valueh,int *value);




#endif /* ADC_H_ */