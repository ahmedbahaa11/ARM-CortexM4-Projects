/* Include Files from LIB Layer */
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
/* Include Files from MCAL Layer */
#include "../include/stm32F401CC.h"
#include "MCAL/RCC/RCC_Interface.h"
#include "MCAL/NVIC/NVIC_Interface.h"
#include "MCAL/GPIO/GPIO_Interface.h"
#include "MCAL/DMA/DMA_int.h"
#include "MCAL/SYSTICK/SYSTICK_Interface.h"
#define SIZE		4000
void DMA_LED_TEST (void);

/* Source Array for CPU */
u32 Global_u32Src_arr[SIZE] ;  // Init value = 0

void main(void)
{
	/* Init of System Clock */
	RCC_voidInitSystemClock();

	/* Enable Clock to GPIOA Peripheral */
	RCC_voidEnablePeripheralClock(AHB1,RCC_GPIOA);

	/* Enable Clock to DMA2 Peripheral */
	RCC_voidEnablePeripheralClock(AHB1,RCC_DMA2);

	/* Init GPIO Pins */
	GPIO_voidPinInit(GPIOA,PIN0,OUTPUT,PUSH_PULL,LOW_SPEED);

	/* Enable DMA2 from NVIC */
	NVIC_voidEnablePeripheralINT(DMA2_Stream0);

	/* DMA Function Call Back */
	MDMA_vSetStreamCallback(0,DMA_LED_TEST);

	/* destination array for CPU */
	u32 Local_u32Distenation[SIZE] ;	//garbage

	/* destination array for DMA */
	u32 Local_u32Dis_Array[SIZE] ;	//garbage

	/* Source array for DMA */
	u32 Local_u32Src_Array[SIZE] ;	//garbage

	/* Initialization of Source array for DMA */
	for (u32 iter=0 ; iter < SIZE ; iter++ )
	{
		/* init Source array from 0 --> 499 {0,1,2,......,SIZE-1} */
		Local_u32Src_Array[iter] = iter ;
	}

	/* Init DMA --> Stream0 */
	MDMA_vInit();

	/* Set Source Address and Destination Address for DMA */
	MDMA_vSetStream(0,Local_u32Src_Array,Local_u32Dis_Array,SIZE,0b10);

	/* Enable DMA Stream0 */
	MDMA_vEnableStream(0);

	/* Transferring by CPU */
	for (u32 i=0 ; i < SIZE ; i++ )
	{
		Local_u32Distenation[i] = Global_u32Src_arr[i] ;
	}

	GPIO_voidSetPinValueNonAtomic(GPIOA,PIN0,LOW);

	while(1)
	{

	}
}
void DMA_LED_TEST (void)
{
	GPIO_voidSetPinValueAtomic(GPIOA,PIN0,SET);
}
