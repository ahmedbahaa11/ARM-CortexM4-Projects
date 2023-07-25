#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "MCAL/RCC/RCC_Interface.h"
#include "MCAL/GPIO/GPIO_Interface.h"
#include "MCAL/NVIC/NVIC_Interface.h"
#include "MCAL/SYSTICK/SYSTICK_Interface.h"
#include "MCAL/UART/UART_Interface.h"
#include "HAL/ESP8266/ESP8266_Interface.h"

int main()
{
	// Configuration as HSI/2 --> 8 MHz
	RCC_voidInitSystemClock();
	// Init SYSTICK
	STK_voidInit();
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
							.BaudRate = B_115200,
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
	u8 Data[100] = {0} ;
	ESP8266_voidInit();

	ESP8266_vConnectToRouter("NTI_Student","lookup00");
	ESP8266_vOpenServerTCPConnection("23.179.32.37", "80");

  while (1)
  {

	  ESP8266_vSendHTTPRequest("GET http://imt2023.freevar.com/status.txt" , "43" , Data );

	  u8 iter = 0 ;
	  while ( Data[iter] != ":")
	  {
		  iter++ ;
	  }
	  if( Data[iter+1] == '1')
	  {
		  GPIO_voidSetPinValueNonAtomic(GPIOA,PIN0,HIGH);
	  }
	  else if ( Data[iter+1] == '0' )
	  {
		  GPIO_voidSetPinValueNonAtomic(GPIOA,PIN0,LOW);
	  }
	  STK_voidSetBusyWait(1000);
  }
}
