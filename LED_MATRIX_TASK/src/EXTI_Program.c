/*=================================================================================*/
/*  File        : EXTI_Program.c                                                   */
/*  Description : This file includes EXTI Driver implementations for stm32f401CC   */
/*  Author      : Ahmed Bahaa Taha Nasr. Embedded SW Engineer                      */
/*  Date        : 20/5/2023                                                        */
/*  Linkedin    : https://www.linkedin.com/in/ahmed-bahaa1/                        */
/*  Git account : https://github.com/ahmedbahaa11                                  */
/*  mail        : abahaa14842@gmil.com                                             */
/*=================================================================================*/
/*==========================================*/
/* Include Header Files From include Folder */
#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"
/*==========================================*/
#include "../include/stm32F401CC.h"
#include "../include/EXTI_Interface.h"
#include "../include/EXTI_Private.h"
#include "../include/EXTI_Config.h"
/*==========================================*/
static void (*EXTI_APF[16])(void) = {NULL};

u8 EXTI_u8PinInit (const EXTI_PinConfig_t * Copy_pstrPinInit)
{
    u8 Local_u8ErrorStatus = STD_TYPES_OK ;
    u8 Local_u8RegIndex , Local_u8ShiftValue ;
    if ( Copy_pstrPinInit != NULL || Copy_pstrPinInit->PinID < 16 || Copy_pstrPinInit->PortID < 3 )
    {
        /* Enable Interrupt */
        EXTI_u8EnableINT(Copy_pstrPinInit->PinID);
        /* Set SYSCFG to select the PORT */
        Local_u8RegIndex = Copy_pstrPinInit->PinID / 4 ;
        Local_u8ShiftValue = (Copy_pstrPinInit->PinID % 4) * 4 ;
        SYSCFG->EXTICR[Local_u8RegIndex] &= ~( 0b1111 << Local_u8ShiftValue ) ;                     // Clear the 4 Bits Before Modified
        SYSCFG->EXTICR[Local_u8RegIndex] |=  ( (Copy_pstrPinInit->PortID) << Local_u8ShiftValue ) ;   // Set the 4 Bits of the Port {0b0000,0b0001,0b0010}
        /* Select Trigger Soiurce (FALLING_EDGE , RAISING_EDGE , ON_CHANGE )*/
        switch (Copy_pstrPinInit->TriggerLevel)
        {
            case EXTI_FALLING_EDGE :
                                    CLEAR_BIT(EXTI->RTSR , Copy_pstrPinInit->PinID);
                                    SET_BIT(EXTI->FTSR , Copy_pstrPinInit->PinID);
                                    break;
            case EXTI_RAISING_EDGE :
                                    CLEAR_BIT(EXTI->FTSR , Copy_pstrPinInit->PinID);
                                    SET_BIT(EXTI->RTSR , Copy_pstrPinInit->PinID);
                                    break;
            case EXTI_ON_CHANGE    :
                                    SET_BIT(EXTI->RTSR , Copy_pstrPinInit->PinID);
                                    SET_BIT(EXTI->FTSR , Copy_pstrPinInit->PinID);
                                    break;
            default                :
                                    break;
        }
        /* Set Global Pointer to Function */
        EXTI_APF[Copy_pstrPinInit->PinID] = Copy_pstrPinInit->PF ;
    }
    else
    {
        Local_u8ErrorStatus = STD_TYPES_NOK ;
    }
    return Local_u8ErrorStatus ;
}
/*================================================*/
u8 EXTI_u8EnableINT (u8 Copy_u8EXTINum)
{
    u8 Local_u8ErrorState = STD_TYPES_OK ;
    if(Copy_u8EXTINum < 16)
    {
        SET_BIT(EXTI->IMR , Copy_u8EXTINum);
    }
    else
    {   Local_u8ErrorState = STD_TYPES_NOK;    }
    return Local_u8ErrorState ;
}
/*================================================*/
u8 EXTI_u8DisableINT (u8 Copy_u8EXTINum)
{
    u8 Local_u8ErrorState = STD_TYPES_OK ;
    if(Copy_u8EXTINum < 16)
    {
        CLEAR_BIT(EXTI->IMR , Copy_u8EXTINum);
    }
    else
    {   Local_u8ErrorState = STD_TYPES_NOK ;   }
    return Local_u8ErrorState ;
}
/*================================================*/
u8 EXTI_u8ClearPendingFlag (u8 Copy_u8EXTINum)
{
    u8 Local_u8ErrorState = STD_TYPES_OK ;
    if(Copy_u8EXTINum < 16)
    {
        SET_BIT(EXTI->PR , Copy_u8EXTINum);
    }
    else
    {
        Local_u8ErrorState = STD_TYPES_NOK ;
    }
    return Local_u8ErrorState ;
}
/*================================================*/
void EXTI0_IRQHandler (void)
{
    if ( EXTI_APF[0] != NULL )
    {
        EXTI_APF[0]();
    }
    /* Clear Pending Flag */
    EXTI_u8ClearPendingFlag(0);
}
/*==========================================*/
void EXTI1_IRQHandler (void)
{
    if ( EXTI_APF[1] != NULL )
    {
        EXTI_APF[1]();
    }
    /* Clear Pending Flag */
    EXTI_u8ClearPendingFlag(1);
}
/*==========================================*/
void EXTI9_5_IRQHandler(void)
{
    if ( EXTI_APF[5] != NULL )
    {
        EXTI_APF[5]();
        /* Clear Pending Flag */
        EXTI_u8ClearPendingFlag(5);
    }
    if ( EXTI_APF[6] != NULL )
    {
        EXTI_APF[6]();
        /* Clear Pending Flag */
        EXTI_u8ClearPendingFlag(6);
    }
    if ( EXTI_APF[7] != NULL )
    {
        EXTI_APF[7]();
        /* Clear Pending Flag */
        EXTI_u8ClearPendingFlag(7);
    }
    if ( EXTI_APF[8] != NULL )
    {
        EXTI_APF[8]();
        /* Clear Pending Flag */
        EXTI_u8ClearPendingFlag(8);
    }
    if ( EXTI_APF[9] != NULL )
    {
        EXTI_APF[9]();
        /* Clear Pending Flag */
        EXTI_u8ClearPendingFlag(9);
    }
    
}
/*==========================================*/



// /*********************************************************************************************/
// /* Function Name : EXTI_voidEnable                                                           */
// /* Description   : Enable (PIE) Peripheral Interrupt Enable and Put Sesnse Control           */ 
// /* Fun. Argument1: Copy_u8EXTILine -> { EXTI0 : EXTI15 }                                     */
// /* Fun. Argument1: Copy_u8SenseControl { FALLING_EDGE, RAISING_EDGE, ON_CHANGE }             */
// /* Fun. Return   : void                                                                      */
// /*********************************************************************************************/
// void EXTI_voidEnable ( u8 Copy_u8EXTILine , u8 Copy_u8SenseControl )
// {
//     switch(Copy_u8SenseControl)
//     {
//         case FALLING_EDGE :
//                             EXTI_voidDisableRisingTrigger(Copy_u8EXTILine);
//                             EXTI_voidEnableFallingTrigger(Copy_u8EXTILine);
//                             break;
//         case RAISING_EDGE :
//                             EXTI_voidDisableFallingTrigger(Copy_u8EXTILine);
//                             EXTI_voidEnableRisingTrigger(Copy_u8EXTILine);
//                             break;
//         case ON_CHANGE    :
//                             EXTI_voidEnableFallingTrigger(Copy_u8EXTILine);
//                             EXTI_voidEnableRisingTrigger(Copy_u8EXTILine);
//                             break;
//         default           : break;
//     }
// }





