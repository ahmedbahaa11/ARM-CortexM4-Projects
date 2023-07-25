/* Include Files from LIB Layer */
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
/* Include Files from MCAL Layer */
#include "MCAL/RCC/RCC_Interface.h"
#include "MCAL/GPIO/GPIO_Interface.h"

void APP_voidDelayMs(u32 Copy_u32Delay)
{
	for(u32 i=0 ; i < (Copy_u32Delay * 300) ; i++ ) {asm("NOP") ;}
}

void main(void)
{
	/* Init of System Clock */
	RCC_voidInitSystemClock();

	/* Enable Clock to GPIOA Peripheral */
	RCC_voidEnablePeripheralClock(AHB1,0);
	RCC_voidEnablePeripheralClock(AHB1,1);

	/* Init of Pin A0 as a OUTPUT */
	GPIO_voidPinInit(GPIOA,PIN0,OUTPUT,PUSH_PULL,LOW_SPEED);

	/* Init of Pin B5 as a OUTPUT */
	GPIO_voidPinInit(GPIOB,PIN5,OUTPUT,PUSH_PULL,LOW_SPEED);
	GPIO_voidSetPinValueAtomic(GPIOB,PIN5,SET);

	while(1)
	{
		GPIO_voidSetPinValueNonAtomic(GPIOA,PIN0,HIGH);
		APP_voidDelayMs(2000);
		GPIO_voidSetPinValueNonAtomic(GPIOA,PIN0,LOW);
		APP_voidDelayMs(2000);
	}
}
