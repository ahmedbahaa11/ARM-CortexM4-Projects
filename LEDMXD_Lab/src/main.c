/* Include Files from LIB Layer */
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
/* Include Files from MCAL Layer */
#include "../include/stm32F401CC.h"
#include "MCAL/RCC/RCC_Interface.h"
#include "MCAL/SYSTICK/SYSTICK_Interface.h"
#include "MCAL/GPIO/GPIO_Interface.h"
#include "HAL/LEDMXD/LEDMXD_Interface.h"

u8 LEDMXD_ARRAY1[8]={12, 18, 36, 72, 36, 18, 12, 0};
u8 LEDMXD_ARRAY2[8]={252, 32, 253, 1, 255, 1, 245, 0};

void main(void)
{
	/* Init of System Clock */
	RCC_voidInitSystemClock();

	/* Enable Clock to GPIOA Peripheral */
	RCC_voidEnablePeripheralClock(AHB1,RCC_GPIOA);
	RCC_voidEnablePeripheralClock(AHB1,RCC_GPIOB);

	/* (STK) Init SYSTICK */
	STK_voidInit();

	/* (LEDMXD) Init LED Matrix */
	LEDMXD_voidInit();


	while(1)
	{
		LEDMXD_u8Display(LEDMXD_ARRAY1);
		LEDMXD_u8Display(LEDMXD_ARRAY2);
	}
}

