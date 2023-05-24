/*=================================================================================*/
/*  File        : NVIC_Program.c                                                   */
/*  Description : This file includes NVIC Driver implementations for stm32f401CC   */
/*  Author      : Ahmed Bahaa Taha Nasr. Embedded SW Engineer                      */
/*  Date        : 19/5/2023                                                        */
/*  Linkedin    : https://www.linkedin.com/in/ahmed-bahaa1/                        */
/*  Git account : https://github.com/ahmedbahaa11                                  */
/*  mail        : abahaa14842@gmil.com                                             */
/*=================================================================================*/
/*==========================================*/
/* Include Header Files From include Folder */
#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"
/*==========================================*/
#include "../include/NVIC_Interface.h"
#include "../include/NVIC_Private.h"
#include "../include/NVIC_Config.h"
/*==========================================*/
u8 Global_u8PriorityOption = 0;

void NVIC_voidEnablePeripheralINT (u8 Copy_u8INTID)
{
    NVIC->ISER[(Copy_u8INTID / 32)] = ( 1 << (Copy_u8INTID % 32)) ;
}
void NVIC_voidDisablePeripheralINT (u8 Copy_u8INTID)
{
    NVIC->ICER[(Copy_u8INTID / 32)] = ( 1 << (Copy_u8INTID % 32)) ;
}
void NVIC_voidSetPendingFlag (u8 Copy_u8INTID)
{
    NVIC->ISPR[(Copy_u8INTID / 32)] = ( 1 << (Copy_u8INTID % 32)) ;
}
void NVIC_voidClearPendingFlag (u8 Copy_u8INTID)
{
    NVIC->ICPR[(Copy_u8INTID / 32)] = ( 1 << (Copy_u8INTID % 32)) ;
}
// { GR4BITS_SubGR0BITS , GR3BITS_SubGR1BITS , GR2BITS_SubGR2BITS , GR1BITS_SubGR3BITS , GR0BITS_SubGR4BITS }
void NVIC_voidSetPriorityConfig (u8 Copy_u8PriorityOption)
{
    Global_u8PriorityOption = Copy_u8PriorityOption ;
    SCB_AIRCR = VECTOR_KEY | (Copy_u8PriorityOption << 8) ;
}
void NVIC_voidSetINTPriority (u8 Copy_u8INTID , u8 Copy_u8GroupID , u8 Copy_u8SubGroupID)
{
    u8 Local_u8Priority = Copy_u8SubGroupID | (Copy_u8GroupID << (Global_u8PriorityOption - GR4BITS_SubGR0BITS)) ;
    NVIC -> IPR[Copy_u8INTID] = (Local_u8Priority << 4) ;
}
