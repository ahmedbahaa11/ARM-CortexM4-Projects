#include"../include/STD_TYPES.h"
#include"../include/RCC_Interface.h"
#include"../include/GPIO_Interface.h"
#include"../include/SYSTICK_Interface.h"
#include"../include/LEDMXD_Interface.h"
void UpdateArray (u8 *Copy_u8Array, u8 Copy_NewValue);
u8 LEDMXD_ARRAY[8]={0, 0, 0, 0, 0, 0, 0, 0};
u8 NewValues[71]={252,34,33,34,252,0,0,255,16,16,224,0,0,252,8,248,8,240,0,0,60,82,146,12,0,0,96,144,144,255,0,0,0,0,0,255,153,153,118,0,0,48,72,72,240,0,0,255,16,16,224,0,0,48,72,72,240,0,0,48,72,72,240,0,0,0,0,0,0,0,0};
void main(void)
{
	/* (RCC) Init System Clock */
	RCC_voidInitSystemClock();

	/* (RCC) Enable Peripheral ClocK */
	RCC_voidEnablePeripheralClock(AHB1,0);	// GPIOA
	RCC_voidEnablePeripheralClock(AHB1,1);	// GPIOB

	/* (STK) Init SYSTIC */
	STK_voidInit();

	/* (LEDMXD) Init LED Matrix */
	LEDMXD_voidInit();

	while(1)
	{
		for ( u8 i=0 ; i<71 ; i++ )
		{
			LEDMXD_u8Display(LEDMXD_ARRAY);
			UpdateArray(LEDMXD_ARRAY,NewValues[i]);
		}
	}
}

void UpdateArray (u8 *Copy_u8Array, u8 Copy_NewValue)
{
	for(u8 i=0 ; i<8 ; i++)
	{
		Copy_u8Array[i] ^= Copy_u8Array[i+1] ;
		Copy_u8Array[i+1] ^= Copy_u8Array[i] ;
		Copy_u8Array[i] ^= Copy_u8Array[i+1] ;
		if ( i == 7 )
		{ Copy_u8Array[i] = Copy_NewValue ; }
	}
}
