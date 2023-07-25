/*=================================================================================*/
/*  File        : RCC_Interface.c                                                  */
/*  Description : interface file includes RCC Driver prototypes for stm32f401CC    */
/*  Author      : Ahmed Bahaa Taha Nasr. Embedded SW Engineer                      */
/*  Date        : 10/5/2023                                                        */
/*  Linkedin    : https://www.linkedin.com/in/ahmed-bahaa1/                        */
/*  Git account : https://github.com/ahmedbahaa11                                  */
/*  mail        : abahaa14842@gmil.com                                             */
/*=================================================================================*/

/* File Gaurd*/
#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

/*=======================================*/
/*============     Bus ID     ===========*/
/*=======================================*/
#define	   AHB1			0
#define    AHB2			1
#define    APB1			2
#define    APB2			3
/*=======================================*/

/*======================================================================================================================*/
/*====================================     A.BAHAA RCC Functions Implementation      ===================================*/
/*======================================================================================================================*/
/********************************************    RCC_voidInitSystemClock            *************************************/
/********************************************    RCC_voidEnablePeripheralClock      *************************************/ 
/********************************************    RCC_voidDisablePeripheralClock     *************************************/ 
/*======================================================================================================================*/

/************************************************************************************************/
/* Function Name : RCC_voidInitSystemClock                                                      */
/* Description : Initilization of RCC to initialize System clock                                */
/* Fun. Return : void                                                                           */
/************************************************************************************************/
void RCC_voidInitSystemClock (void);

/************************************************************************************************/
/* Function Name : RCC_voidEnablePeripheralClock                                                */
/* Description : Enable clock source to specific Bus and spesific Peripheral                    */
/* Fun. Argument1: Copy_u8BusID { AHB1,AHB2,APB1,APB2 }                                         */
/* Fun. Argument2: Copy_u8PeripheralID { from 0 -> 32 according to Pheripheral }                */
/* Fun. Return : void                                                                           */
/************************************************************************************************/
void RCC_voidEnablePeripheralClock ( u8 Copy_u8BusID , u8 Copy_u8PeripheralClock);

/************************************************************************************************/
/* Function Name : RCC_voidDisablePeripheralClock                                               */
/* Description : Disable clock source to specific Bus and spesific Peripheral                   */
/* Fun. Argument1: Copy_u8BusID { AHB1,AHB2,APB1,APB2 }                                         */
/* Fun. Argument2: Copy_u8PeripheralID { from 0 -> 32 according to Pheripheral }                */
/* Fun. Return : void                                                                           */
/************************************************************************************************/
void RCC_voidDisablePeripheralClock ( u8 Copy_u8BusID , u8 Copy_u8PeripheralClock);

#endif