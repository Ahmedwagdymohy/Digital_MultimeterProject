/**
 * @file GPIO_program.c
 *  @author Ahmed_Wagdy
 * @brief   The main application
 * @version 0.1
 * @date 2024-02-11
 * 
 * @copyright WAGDY(c) 2024
 * 
 */

/*********************************************************< LIB **************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/********************************************************< Mcal_GPIO*************************************************************************/
#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"





/****************************************************************************************************************************/
/******************************************************< SetPinDirection ******************************************************/
/****************************************************************************************************************************/

/**
 * @brief SetThe pinDirection based on user choice
 * 
 * @param Copy_portId                       A or B or C ...
 * @param Copy_PinId                        pin number {in the low register we have (0->7) and high we have (8->15)}
 * @param Copy_PinDirection                 The user enters the 4bits of the ConfigOutput (00 | 11) and we can define them to be more readable and user friendly
 * @return Std_ReturnType 
 */
Std_ReturnType GPIO_SetPinDirection (u8 Copy_portId, u8 Copy_PinId, u8 Copy_PinDirection){
    Std_ReturnType LocalFunctionReturn = E_NOT_OK;
    switch (Copy_portId)
    {
    /*******************************************<PortACase***********************************************************/    
    case GPIO_PORTA:
        if(Copy_PinId < 8){ //if() to know wether the pin in theHigh register or theLow register
        /*We have the port name and te pin number all we want is to set the direction*/

             GPIO_GPIOA_CRL &= ~((0b1111) << (Copy_PinId *4) )   ;      /*this line intialize the pinBits with zero*/
             GPIO_GPIOA_CRL |= ((Copy_PinDirection)<<(Copy_PinId *4));  /*this shifts the configBits to it's correct place without affecting the other bits*/



        }else if (Copy_PinId < 16)
        {
            GPIO_GPIOA_CRH &= ~((0b1111) << (Copy_PinId *4) )   ;
            GPIO_GPIOA_CRH |= ((Copy_PinDirection)<<(Copy_PinId *4));
            
        }
        else{
            LocalFunctionReturn =E_NOT_OK;
        }
        
        
    break;
    /*******************************************<PortBCase***********************************************************/
    case GPIO_PORTB:
        if(Copy_PinId < 8){ //if to know wether the pin in theHigh register or theLow register
        /*We have the port name and te pin number all we want is to set the direction*/

             GPIO_GPIOB_CRL &= ~((0b1111) << (Copy_PinId *4) )   ;      /*this line intialize the pinBits with zero*/
             GPIO_GPIOB_CRL |= ((Copy_PinDirection)<<(Copy_PinId *4));  /*this shifts the configBits to it's correct place without affecting the other bits*/



        }else if (Copy_PinId < 16)
        {
            GPIO_GPIOB_CRH &= ~((0b1111) << (Copy_PinId *4) )   ;
            GPIO_GPIOB_CRH |= ((Copy_PinDirection)<<(Copy_PinId *4));
            
        }
        else{
            LocalFunctionReturn =E_NOT_OK;
        }
    
    break;

    /*******************************************<PortCCase***********************************************************/
    case GPIO_PORTC:
       if(Copy_PinId < 8){ //if to know wether the pin in theHigh register or theLow register
        /*We have the port name and te pin number all we want is to set the direction*/

             GPIO_GPIOC_CRL &= ~((0b1111) << (Copy_PinId *4) )   ;      /*this line intialize the pinBits with zero*/
             GPIO_GPIOC_CRL |= ((Copy_PinDirection)<<(Copy_PinId *4));  /*this shifts the configBits to it's correct place without affecting the other bits*/



        }else if (Copy_PinId < 16)
        {
            GPIO_GPIOC_CRH &= ~((0b1111) << (Copy_PinId *4) )   ;
            GPIO_GPIOC_CRH |= ((Copy_PinDirection)<<(Copy_PinId *4));
            
        }
        else{
            LocalFunctionReturn =E_NOT_OK;
        }
    
    break;
    default: LocalFunctionReturn =E_NOT_OK;
        break;
    }






    return LocalFunctionReturn;
}


/****************************************************************************************************************************/
/******************************************************< SET PinValue******************************************************/
/****************************************************************************************************************************/
/**
 * @brief                                                   this function SetThe PinValue                                                
*/
Std_ReturnType GPIO_SetPinValue(u8 Copy_portId, u8 Copy_PinId, u8 Copy_PinValue){
    Std_ReturnType LocalFunctionReturn = E_NOT_OK;
    switch (Copy_portId)
    {
    case GPIO_PORTA:
       SET_BIT(GPIO_GPIOA_IDR , Copy_PinValue );  // continue here
        LocalFunctionReturn =E_OK;
        break;
    case GPIO_PORTB:
        
        LocalFunctionReturn = E_OK;
    break;
    
    

    default:
        LocalFunctionReturn = E_NOT_OK;
        break;
    }


    return LocalFunctionReturn;
}














/****************************************************************************************************************************/
/******************************************************< Get PinValue******************************************************/
/****************************************************************************************************************************/

/*****************************************************<  important*****************************************************************/
/**< NOTE (GPIOx_IDR) captures the data present on the I/O pin*/ //that's why we use to get the pin info , it's read only
/***********************************************************************************************************************/

/**
 * @brief                                                the function gets the pin value with the register GPIOx_IDR that's used to read only
 * 
 * @param Copy_portId                                    portname {A, B , C}
 * @param Copy_PinId                                     Pin_number
 * @param Copy_PinValue                                  the pin value we read { HIGH , LOW }
 * @return Std_ReturnType 
 */

Std_ReturnType GPIO_GetPinValue(u8 Copy_portId , u8 Copy_PinId , u8 *Copy_PinValue ){
    Std_ReturnType LocalFunctionReturn = E_NOT_OK;
    if(Copy_PinValue != NULL){

        switch (Copy_portId){ //cases on which port fisrt!

            case GPIO_PORTA :
                Copy_PinValue = GET_BIT(GPIO_GPIOA_IDR, Copy_PinId); 
                LocalFunctionReturn = E_OK;   
            break;

            case GPIO_PORTB :
                Copy_PinValue = GET_BIT(GPIO_GPIOB_IDR, Copy_PinId);   
                LocalFunctionReturn = E_OK;  
            break;

            case GPIO_PORTC :
                Copy_PinValue = GET_BIT(GPIO_GPIOC_IDR, Copy_PinId);  
                LocalFunctionReturn = E_OK;   
            break;
            default: LocalFunctionReturn = E_NOT_OK;
            break;

        }
    }
    return LocalFunctionReturn;

}






  