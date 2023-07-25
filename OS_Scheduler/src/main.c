/* Include Files from LIB Layer */
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
/* Include Files from MCAL Layer */
#include "../include/stm32F401CC.h"
#include "MCAL/RCC/RCC_Interface.h"
#include "MCAL/SYSTICK/SYSTICK_Interface.h"
#include "MCAL/GPIO/GPIO_Interface.h"
#include "SRV/RTOS/RTOS_Interface.h"
void Func1 (void);
void Func2 (void);
void Func3 (void);

void main(void)
{
	/* Init of System Clock */
	RCC_voidInitSystemClock();

	/* Enable Clock to GPIOA Peripheral */
	RCC_voidEnablePeripheralClock(AHB1,RCC_GPIOA);

	/* Init of Pin Ax as a OUTPUT */
	GPIO_voidPinInit(GPIOA,PIN0,OUTPUT,PUSH_PULL,LOW_SPEED);
	GPIO_voidPinInit(GPIOA,PIN1,OUTPUT,PUSH_PULL,LOW_SPEED);
	GPIO_voidPinInit(GPIOA,PIN2,OUTPUT,PUSH_PULL,LOW_SPEED);

	/* Create Tasks */
	RTOS_u8CreateTask(0,1000,1000,&Func1);
	RTOS_u8CreateTask(1,1000,1000,&Func2);
	RTOS_u8CreateTask(2,1000,1000,&Func3);

	/* Init RTOS Scheduler */
	RTOS_voidInit();

	while(1);

}
void Func1 (void)
{
	static u8 Var = HIGH ;
	if ( Var == HIGH )
	{
		GPIO_voidSetPinValueNonAtomic(GPIOA,PIN0,Var);
		Var = LOW ;
	}
	else
	{
		GPIO_voidSetPinValueNonAtomic(GPIOA,PIN0,Var);
		Var = HIGH ;
	}
}
void Func2 (void)
{
	static u8 Var = HIGH ;
	if ( Var == HIGH )
	{
		GPIO_voidSetPinValueNonAtomic(GPIOA,PIN1,Var);
		Var = LOW ;
	}
	else
	{
		GPIO_voidSetPinValueNonAtomic(GPIOA,PIN1,Var);
		Var = HIGH ;
	}
}
void Func3 (void)
{
	static u8 Var = HIGH ;
	if ( Var == HIGH )
	{
		GPIO_voidSetPinValueNonAtomic(GPIOA,PIN2,Var);
		Var = LOW ;
	}
	else
	{
		GPIO_voidSetPinValueNonAtomic(GPIOA,PIN2,Var);
		Var = HIGH ;
	}
}
