/* Include Files from LIB Layer */
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "../include/stm32F401CC.h"
/* Include Files from MCAL Layer */
#include "MCAL/RCC/RCC_Interface.h"
#include "MCAL/GPIO/GPIO_Interface.h"
#include "MCAL/NVIC/NVIC_Interface.h"


void main(void)
{
	/* Init of System Clock */
	RCC_voidInitSystemClock();

	/* Enable Clock to GPIOA Peripheral */
	RCC_voidEnablePeripheralClock(AHB1,RCC_GPIOA);

	/* Init of Pin A0 as a OUTPUT */
	GPIO_voidPinInit(GPIOA,PIN0,OUTPUT,PUSH_PULL,LOW_SPEED);

	/* Enable Peripheral INT (INT-0,INT-35) */
	NVIC_voidEnablePeripheralINT(EXTI0);
	NVIC_voidEnablePeripheralINT(SPI1);

	/* Configration of Software Priority Grouping */
	NVIC_voidSetPriorityConfig (GR4BITS_SubGR0BITS); //16 GR (Nesting Enable)

	/* Set Software Priority  */
	NVIC_voidSetINTPriority (EXTI0,1,0);	// EXTI0 -> GR0
	NVIC_voidSetINTPriority (SPI1,1,0);		// SPI1  -> GR1

	/* Set Pending Flag to Fire Interrupt */
	NVIC_voidSetPendingFlag(SPI1);

	while(1)
	{

	}
}

EXTI0_IRQHandler()
{
	GPIO_voidSetPinValueNonAtomic(GPIOA,PIN0,HIGH);
	while(1);
}

SPI1_IRQHandler()
{
	/* Set Pending Flag to Fire Interrupt */
	NVIC_voidSetPendingFlag(EXTI0);
	while(1);
}
