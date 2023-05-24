/*=================================================================================*/
/*  File        : EXTI_Interface.c                                                 */
/*  Description : interface file includes EXTI Driver prototypes for stm32f401CC   */
/*  Author      : Ahmed Bahaa Taha Nasr. Embedded SW Engineer                      */
/*  Date        : 20/5/2023                                                        */
/*  Linkedin    : https://www.linkedin.com/in/ahmed-bahaa1/                        */
/*  Git account : https://github.com/ahmedbahaa11                                  */
/*  mail        : abahaa14842@gmil.com                                             */
/*=================================================================================*/

/* File Gaurd*/
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H
/* enum as PinID PINx */
enum
{
    EXTI_PIN0,
    EXTI_PIN1,
    EXTI_PIN2,
    EXTI_PIN3,
    EXTI_PIN4,
    EXTI_PIN5,
    EXTI_PIN6,
    EXTI_PIN7,
    EXTI_PIN8,
    EXTI_PIN9,
    EXTI_PIN10,
    EXTI_PIN11,
    EXTI_PIN12,
    EXTI_PIN13,
    EXTI_PIN14,
    EXTI_PIN15,
};
/*     Macros as PortID GPIOx       */
#define EXTI_GPIOA               0b0000
#define EXTI_GPIOB               0b0001
#define EXTI_GPIOC               0b0010
/* Macros as Trigger Control Levels */
#define EXTI_FALLING_EDGE           0
#define EXTI_RAISING_EDGE           1 
#define EXTI_ON_CHANGE              2

typedef struct 
{
    u8 PortID;
    u8 PinID;
    u8 TriggerLevel;
    void (*PF)(void);
}EXTI_PinConfig_t;

u8 EXTI_u8PinInit (const EXTI_PinConfig_t * Copy_pstrPinInit);

u8 EXTI_u8EnableINT (u8 Copy_u8EXTINum);

u8 EXTI_u8DisableINT (u8 Copy_u8EXTINum);

u8 EXTI_u8ClearPendingFlag (u8 Copy_u8EXTINum);






























// /*********************************************************************************************/
// /* Function Name : EXTI_voidEnable                                                           */
// /* Description   : Enable (PIE) Peripheral Interrupt Enable and Put Sesnse Control           */ 
// /* Fun. Argument1: Copy_u8EXTILine -> { EXTI0 : EXTI15 }                                     */
// /* Fun. Argument1: Copy_u8SenseControl { FALLING_EDGE, RAISING_EDGE, ON_CHANGE }             */
// /* Fun. Return   : void                                                                      */
// /*********************************************************************************************/
// void EXTI_voidEnable ( u8 Copy_u8EXTILine , u8 Copy_u8SenseControl );

// /*********************************************************************************************/
// /* Function Name : EXTI_voidDisable                                                          */
// /* Description   : Disable (PIE) Peripheral Interrupt                                        */ 
// /* Fun. Argument1: Copy_u8EXTILine -> { EXTI0 : EXTI15 }                                     */
// /* Fun. Return   : void                                                                      */
// /*********************************************************************************************/
// void EXTI_voidDisable ( u8 Copy_u8EXTILine );

// /*===========================================================================================*/
// void EXTI_voidEnableRisingTrigger (u8 Copy_u8EXTILine); 
// void EXTI_voidDisableRisingTrigger (u8 Copy_u8EXTILine); 
// void EXTI_voidEnableFallingTrigger (u8 Copy_u8EXTILine); 
// void EXTI_voidDisableFallingTrigger (u8 Copy_u8EXTILine); 

// void EXTI_voidSetSoftwareINT (u8 Copy_u8EXTILine);
// /*===========================================================================================*/
// /* Macros as Sense Control options */
// #define FALLING_EDGE                0
// #define RAISING_EDGE                1 
// #define ON_CHANGE                   2
// /*===========================================================================================*/

#endif