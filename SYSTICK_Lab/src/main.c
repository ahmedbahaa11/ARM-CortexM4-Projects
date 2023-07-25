/* Include Files from LIB Layer */
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
/* Include Files from MCAL Layer */
#include "../include/stm32F401CC.h"
#include "MCAL/RCC/RCC_Interface.h"
#include "MCAL/SYSTICK/SYSTICK_Interface.h"
#include "MCAL/GPIO/GPIO_Interface.h"
void Func (void);

void main(void)
{
	/* Init of System Clock */
	RCC_voidInitSystemClock();

	/* Init SYSTICK */
	STK_voidInit();

	/* Enable Clock to GPIOA Peripheral */
	RCC_voidEnablePeripheralClock(AHB1,RCC_GPIOA);

	/* Init of Pin A0 as a OUTPUT */
	GPIO_voidPinInit(GPIOA,PIN0,OUTPUT,PUSH_PULL,LOW_SPEED);

//	STK_voidSetIntervalSingle(1000000,&Func);

//	STK_voidSetIntervalPeriodic(3000000,&Func);

	while(1)
	{

	}
}
void Func (void)
{
	GPIO_voidSetPinValueNonAtomic(GPIOA,PIN0,HIGH);
	STK_voidSetBusyWait(1000000);
	GPIO_voidSetPinValueNonAtomic(GPIOA,PIN0,LOW);
	STK_voidSetBusyWait(1000000);
	GPIO_voidSetPinValueNonAtomic(GPIOA,PIN0,HIGH);
	STK_voidSetBusyWait(1000000);
	GPIO_voidSetPinValueNonAtomic(GPIOA,PIN0,LOW);
	STK_voidSetBusyWait(1000000);

//	static u8 Var = HIGH ;
//	if ( Var == HIGH )
//	{
//		GPIO_voidSetPinValueNonAtomic(GPIOA,PIN0,Var);
//		Var = LOW ;
//	}
//	else
//	{
//		GPIO_voidSetPinValueNonAtomic(GPIOA,PIN0,Var);
//		Var = HIGH ;
//	}

}
