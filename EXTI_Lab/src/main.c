/* Include Files from LIB Layer */
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "../include/stm32F401CC.h"
/* Include Files from MCAL Layer */
#include "MCAL/RCC/RCC_Interface.h"
#include "MCAL/GPIO/GPIO_Interface.h"
#include "MCAL/NVIC/NVIC_Interface.h"
#include "MCAL/EXTI/EXTI_Interface.h"
void EXTI5Func(void);
void EXTI4Func(void);
void APP_voidDelayMs(u32 Copy_u32Delay)
{
	for(u32 i=0 ; i < (Copy_u32Delay * 300) ; i++ ) {asm("NOP") ;}
}

void main(void)
{

	RCC_voidInitSystemClock();									// Init of System Clock
	RCC_voidEnablePeripheralClock(AHB1,RCC_GPIOA);				// Enable Clock to GPIOA Peripheral
	GPIO_voidPinInit(GPIOA,PIN0,OUTPUT,PUSH_PULL,LOW_SPEED);	// Init of Pin A0 as a OUTPUT
	GPIO_voidPinInit(GPIOA,PIN1,OUTPUT,PUSH_PULL,LOW_SPEED);	// Init of Pin A1 as a OUTPUT

	/* Configration of Software Priority Grouping */
	NVIC_voidSetPriorityConfig (GR4BITS_SubGR0BITS); //16 GR (Nesting Enable)

	/* Set Software Priority  */
	NVIC_voidSetINTPriority (EXTI9_5,10,0);
	NVIC_voidSetINTPriority (EXTI4,15,0);

	/*==============  Steps to Active EXTI  ===============*/
	/* 1- Init of Pin A5 as a INPUT */
	GPIO_voidPinInit(GPIOA,PIN5,INPUT,PULL_UP,LOW_SPEED);
	/* 2- Define Object from struct contain {PORT,EXTI Line,Sense Control,CallBack Function}  */
	EXTI_PinConfig_t LOL = {EXTI_GPIOA,EXTI_PIN5,EXTI_FALLING_EDGE,&EXTI5Func};
	/* 3- Call Function EXTI_u8PinInit with Previous struct Object */
	EXTI_u8PinInit (&LOL);
	/* 4- Enable Peripheral INT (EXTI5_9) from NVIC */
	NVIC_voidEnablePeripheralINT (EXTI9_5);
	/*=====================================================*/
	/* 1- Init of Pin A4 as a INPUT */
	GPIO_voidPinInit(GPIOA,PIN4,INPUT,PULL_UP,LOW_SPEED);
	/* 2- Define Object from struct contain {PORT,EXTI Line,Sense Control,CallBack Function}  */
	EXTI_PinConfig_t LOL2 = {EXTI_GPIOA,EXTI_PIN4,EXTI_FALLING_EDGE,&EXTI4Func};
	/* 3- Call Function EXTI_u8PinInit with Previous struct Object */
	EXTI_u8PinInit (&LOL2);
	/* 4- Enable Peripheral INT (EXTI4) from NVIC */
	NVIC_voidEnablePeripheralINT (EXTI4);
	/*=====================================================*/

	while(1)
	{

	}
}

void EXTI5Func(void)
{
	GPIO_voidSetPinValueAtomic(GPIOA,PIN0,SET);
	APP_voidDelayMs(10000);
	GPIO_voidSetPinValueAtomic(GPIOA,PIN0,RST);
}
void EXTI4Func(void)
{
	GPIO_voidSetPinValueAtomic(GPIOA,PIN1,SET);
	APP_voidDelayMs(10000);
	GPIO_voidSetPinValueAtomic(GPIOA,PIN1,RST);
}

