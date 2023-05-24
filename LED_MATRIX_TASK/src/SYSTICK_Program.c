/*==================================================================================*/
/*  File        : SYSTICK_Program.c                                                 */
/*  Description : This file includes SYSTICK Driver implementations for stm32f401CC */
/*  Author      : Ahmed Bahaa Taha Nasr. Embedded SW Engineer                       */
/*  Date        : 13/5/2023                                                         */
/*  Linkedin    : https://www.linkedin.com/in/ahmed-bahaa1/                         */
/*  Git account : https://github.com/ahmedbahaa11                                   */
/*  mail        : abahaa14842@gmil.com                                              */
/*==================================================================================*/
/*==========================================*/
/* Include Header Files From include Folder */
#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"
/*==========================================*/
#include "../include/SYSTICK_Interface.h"
#include "../include/SYSTICK_Config.h"
#include "../include/SYSTICK_Private.h"
/*==========================================*/
/* Global Pointer to Function to Call Back Funtions for ISR */
void (*Global_CallBackptr1)(void) = NULL ;
/* Global Variables */
u8 STK_IntervalMode = 0 ;

/*====================================================================================================*/
/*=========================     A.BAHAA SYSTICK Functions Implementation      ========================*/
/*====================================================================================================*/
/*********************************    STK_voidInit                       ******************************/
/*********************************    STK_voidSetBusyWait                ******************************/ 
/*********************************    STK_voidSetIntervalSingle          ******************************/ 
/*********************************    STK_voidSetIntervalPeriodic        ******************************/ 
/*********************************    STK_voidStopInterval               ******************************/ 
/*********************************    STK_u32GetElapsedTime              ******************************/ 
/*********************************    STK_u32GetRemainingTime            ******************************/ 
/*********************************    SysTick_Handler                    ******************************/ 
/*====================================================================================================*/


/************************************************************************************************/
/* Function Name : STK_voidInit                                                                 */
/* Description : Inilization of SYSTICK Source                                                  */
/* Fun. Return : void                                                                           */
/************************************************************************************************/
void STK_voidInit (void)
{
    STK_voidStopInterval();
    /* Select CLOCK Source */
    #if( STK_CLOCK_SOURCE == AHB_CLOCK )
        SET_BIT(STK_CTRL,2);        // AHB
    #elif( STK_CLOCK_SOURCE == AHB_CLOCK_DividedBy_8 )
        CLEAR_BIT(STK_CTRL,2);      // AHB/8
    #endif
}

/************************************************************************************************/
/* Function Name : STK_voidSetBusyWait                                                          */
/* Description : Delay for Given Time in Msecond                                                */
/* Fun. Argument1: Copy_u32TimeMs                                                               */
/* Fun. Return : void                                                                           */
/************************************************************************************************/
void STK_voidSetBusyWait(u32 Copy_u32TimeMs)
{
    /* Set Time on LOAD */
    STK_LOAD = Copy_u32TimeMs;

    /* Start Timer */
    SET_BIT(STK_CTRL,0);

    /* Polling on Flag */
    while( ((GET_BIT(STK_CTRL,16))) == 0);

    /* Stop Timer */
    STK_voidStopInterval();
}

/************************************************************************************************/
/* Function Name : STK_voidSetIntervalSingle                                                    */
/* Description : Take Action on CallBack Function at specific time for single interval          */
/* Fun. Argument1: Copy_u32TimeMs                                                               */
/* Fun. Argument2: void (*Copy_ptr)(void) ( Address of Call Back Function )                     */
/* Fun. Return : void                                                                           */
/************************************************************************************************/
void STK_voidSetIntervalSingle(u32 Copy_u32TimeMs,void (*Copy_ptr)(void))
{
    /* Disable Timer */
    CLEAR_BIT(STK_CTRL,0);
    STK_VAL = 0 ;

    /* Load Time to LOAD Register */
    STK_LOAD = Copy_u32TimeMs*1000UL ;

    /* Start Timer */
    SET_BIT(STK_CTRL,0);

    /* Save Call Back */
    Global_CallBackptr1 = Copy_ptr ;

    /* Set Mode To Single Interval */
    STK_IntervalMode = STK_SingleInterval ;

    /* Enable SYSTICK Interrupt */
    SET_BIT(STK_CTRL,1);
}

/************************************************************************************************/
/* Function Name : STK_voidSetIntervalPeriodic                                                  */
/* Description : Take Action on CallBack Function at specific time for Periodic interval        */
/* Fun. Argument1: Copy_u32TimeMs                                                               */
/* Fun. Argument2: void (*Copy_ptr)(void) ( Address of Call Back Function )                     */
/* Fun. Return : void                                                                           */
/************************************************************************************************/
void STK_voidSetIntervalPeriodic(u32 Copy_u32TimeMs,void (*Copy_ptr)(void))
{
    /* Disable Timer */
    CLEAR_BIT(STK_CTRL,0);
    STK_VAL = 0 ;

    /* Load Time to LOAD Register */
    STK_LOAD = Copy_u32TimeMs*1000UL ;

    /* Start Timer */
    SET_BIT(STK_CTRL,0);

    /* Save Call Back */
    Global_CallBackptr1 = Copy_ptr ;

    /* Set Mode To Periodic Interval */
    STK_IntervalMode = STK_PeriodicInterval ;

    /* Enable SYSTICK Interrupt */
    SET_BIT(STK_CTRL,1);
}

/************************************************************************************************/
/* Function Name : STK_voidStopInterval                                                         */
/* Description : Stop SYSTICK and Clear LOAD Register and Value Register                        */
/* Fun. Return : void                                                                           */
/************************************************************************************************/
void STK_voidStopInterval (void)
{
    /* Disable Interrupt */
    CLEAR_BIT(STK_CTRL,1);

    /* Disable STK */
    CLEAR_BIT(STK_CTRL,0);
    STK_LOAD = 0 ;
    STK_VAL = 0 ;
}

/************************************************************************************************/
/* Function Name : STK_u32GetElapsedTime                                                        */
/* Description : Return The Elapsed Time                                                        */
/* Fun. Return : u32 Elapsed Time                                                               */
/************************************************************************************************/
u32 STK_u32GetElapsedTime (void)
{
    u32 Local_ElapsedTime ;
    Local_ElapsedTime = STK_LOAD - STK_VAL ;
    return Local_ElapsedTime ;
}

/************************************************************************************************/
/* Function Name : STK_u32GetRemainingTime                                                      */
/* Description : Return The Remaining Time                                                      */
/* Fun. Return : u32 Remaining Time                                                             */
/************************************************************************************************/
u32 STK_u32GetRemainingTime (void)
{
    u32 LocalRemainingTime ;
    LocalRemainingTime = STK_VAL ;
    return LocalRemainingTime ;
}

/*==============   ISR  SYSTICK   ===============*/
void SysTick_Handler (void)
{
    u8 Local_u8Temp = 0 ;

    if ( STK_IntervalMode == STK_SingleInterval )
    {
        STK_voidStopInterval();
    }

    if ( Global_CallBackptr1 != NULL )
    {
        /* Call Back Notification */
    Global_CallBackptr1();
    }
    
    /* Clear Interrupt Flag by Reading */
    Local_u8Temp = GET_BIT(STK_CTRL,16);
}