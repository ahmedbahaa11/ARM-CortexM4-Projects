/*=================================================================================*/
/*  File        : SSD_Program.c                                                    */
/*  Description : This file includes SSD Driver implementations for stm32f401CC    */
/*  Author      : Ahmed Bahaa Taha Nasr. Embedded SW Engineer                      */
/*  Date        : 12/5/2023                                                        */
/*  Linkedin    : https://www.linkedin.com/in/ahmed-bahaa1/                        */
/*  Git account : https://github.com/ahmedbahaa11                                  */
/*  mail        : abahaa14842@gmil.com                                             */
/*=================================================================================*/


/*==========================================*/
/* Include Header Files From include Folder */
#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"
/*==========================================*/
/* Include Header Files From MCAL Layer */
#include "../include/GPIO_Interface.h"
/*==========================================*/
#include "../include/SSD_Interface.h"
#include "../include/SSD_Private.h"
#include "../include/SSD_Config.h"
/*==========================================*/

u8 Common_Anode_Arr[10]= {ZERO,ONE,TWO,THREE,FOUR,FIVE,SEX,SEVEN,EIGHT,NINE} ;

/*======================================================================================================================*/
/***********************************     A.BAHAA 7_SEGMENT Functions Implementation     *********************************/
/*======================================================================================================================*/
/********************************************    SEGMENT_voidInitSegmentPort       **************************************/
/********************************************    SEGMENT_voidPrintNumber           **************************************/
/*======================================================================================================================*/


/*****************************************************************************************************/
/* Function Name : SEGMENT_voidInitSegmentPort                                                       */
/* Description : Initialize one 7-Segment on specific Port ant make it direction as OUTPUT           */
/* Fun. Argument1: Copy_u8PortNumber { PORTA,PORTB,PORTC,PORTD }                                     */
/* Fun. Return : void                                                                                */
/*****************************************************************************************************/
void SSD_voidInitSegmentPort ( u8 Copy_u8PortNumber )
{
    #if( SSD_PINS == LSB_FROM_PIN0_TO_PIN6 )
        for ( u8 x=0 ; x <= 6 ; x++ )
        {
            GPIO_voidPinInit(Copy_u8PortNumber,x,OUTPUT,PUSH_PULL,LOW_SPEED);
        }
    #elif( SSD_PINS == LSB_FROM_PIN9_TO_PIN15 )
        for ( u8 x=9 ; x <= 15 ; x++ )
        {
            GPIO_voidPinInit(Copy_u8PortNumber,x,OUTPUT,PUSH_PULL,LOW_SPEED);
        }
    #endif  
}
/*****************************************************************************************************/
/* Function Name : SEGMENT_voidPrintNumber                                                           */
/* Description : Print Number from 0 to 9 at the 7-Segment                                           */
/* Fun. Argument1: Copy_u8PortNumber { PORTA,PORTB,PORTC,PORTD }                                     */
/* Fun. Argument2: Copy_SegmentPolarity { COMMON_ANODE , COMMON_CATHODE }                            */
/* Fun. Argument3: Copy_u8Number { 0,1,2,3,4,5,6,7,8,9 }                                             */
/* Fun. Return : void                                                                                */
/*****************************************************************************************************/
void SSD_voidPrintNumber ( u8 Copy_u8PortNumber , u8 Copy_SegmentPolarity , u8 Copy_u8Number )
{
    #if( SSD_PINS == LSB_FROM_PIN0_TO_PIN6 )
        switch ( Copy_SegmentPolarity )
        {
            case COMMON_ANODE   :   switch(Copy_u8PortNumber)
                                    {
                                        case GPIOA :   GPIOA_ODR = ( ((u8)GPIOA_ODR) & 0x80 ) | Common_Anode_Arr[Copy_u8Number] ;    break;
                                        case GPIOB :   GPIOB_ODR = ( ((u8)GPIOB_ODR) & 0x80 ) | Common_Anode_Arr[Copy_u8Number] ;    break;
                                        default    :                                                                break;
                                    }
                                    break;
            case COMMON_CATHODE :   switch(Copy_u8PortNumber)
                                    {
                                        case GPIOA :   GPIOA_ODR = ( ((u8)GPIOA_ODR) & 0x80 ) | (~Common_Anode_Arr[Copy_u8Number]) ;    break;
                                        case GPIOB :   GPIOB_ODR = ( ((u8)GPIOB_ODR) & 0x80 ) | (~Common_Anode_Arr[Copy_u8Number]) ;    break;
                                        default    :                                                                    break;
                                    }   
                                    break;
            default             :   break;
        }
    #elif( SSD_PINS == LSB_FROM_PIN9_TO_PIN15 )
        switch ( Copy_SegmentPolarity )
        {
            case COMMON_ANODE   :   switch(Copy_u8PortNumber)
                                    {
                                        case GPIOA :   GPIOA_ODR = ( (GPIOA_ODR) & 0x01FF ) | ( Common_Anode_Arr[Copy_u8Number] << 9 ) ;    break;
                                        case GPIOB :   GPIOB_ODR = ( (GPIOB_ODR) & 0x01FF ) | ( Common_Anode_Arr[Copy_u8Number] << 9 ) ;    break;
                                        default    :                                                                break;
                                    }
                                    break;
            case COMMON_CATHODE :   switch(Copy_u8PortNumber)
                                    {
                                        case GPIOA :   GPIOA_ODR = ( ((u16)GPIOA_ODR) & 0x01FF ) | ( Common_Anode_Arr[Copy_u8Number] << 9 ) ;    break;
                                        case GPIOB :   GPIOB_ODR = ( ((u16)GPIOB_ODR) & 0x01FF ) | ( Common_Anode_Arr[Copy_u8Number] << 9 ) ;                break;
                                        default    :                                                                    break;
                                    }   
                                    break;
            default             :   break;
        }
    #endif
    
}





