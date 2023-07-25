#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "MCAL/RCC/RCC_Interface.h"
#include "MCAL/GPIO/GPIO_Interface.h"
#include "MCAL/NVIC/NVIC_Interface.h"
#include "MCAL/SYSTICK/SYSTICK_Interface.h"
#include "MCAL/UART/UART_Interface.h"

int main()
{
	// Configuration as HSI/2 --> 8 MHz
	RCC_voidInitSystemClock();
	// Enable GPIOA from RCC
	RCC_voidEnablePeripheralClock(AHB1,RCC_GPIOA);
	// Enable USART1 from RCC
	RCC_voidEnablePeripheralClock(APB2,RCC_USART1);

	GPIO_voidPinInit(GPIOA,PIN0,OUTPUT,PUSH_PULL,LOW_SPEED,AF0);
	// Configure USART1 Pins as Alternative Function Push Pull with AF7 USART1
	GPIO_voidPinInit(GPIOA,PIN9,ALTERNATE,PUSH_PULL,LOW_SPEED,AF7);
	GPIO_voidPinInit(GPIOA,PIN10,ALTERNATE,PUSH_PULL,LOW_SPEED,AF7);
	// Configuration of UART
	USART_InitType uart={
							.BaudRate = B_9600,
							.DataWidth = MODE_8BIT,
							.StopBits = STOP_BIT_1,
							.Oversampling = OVER_SAMPLING_16,
							.TransferDirection = TX_RX,
						};

	USART_ClockInitTypeDef uartclock ={DISABLE,0,0,0};
	// Initialization of USART1
	USART_voidInit(&uart, &uartclock, UART1);
	// Enable USART1
	USART_Enable(UART1);
	// Transmit String
	USART_voidTransmitString(UART1, "ATE0\r\n");
	// Infinite loop
  while (1)
  {
	  USART_voidTransmitString(UART1, "AT\r\n");
	  u8* x ;
	  x = USART_ptrReceiveStringSynchNonBlocking(UART1);
	  if( ( *x == 'O') && ( *(x+1) =='K') )
	  {
		  GPIO_voidSetPinValueAtomic(GPIOA,PIN0,SET);
	  }
	  else
	  {
		  GPIO_voidSetPinValueAtomic(GPIOA,PIN0,RST);
	  }
	  GPIO_voidSetPinValueAtomic(GPIOA,PIN0,SET);
  }
}
