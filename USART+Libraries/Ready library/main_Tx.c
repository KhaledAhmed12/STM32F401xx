# include "stm32f4xx.h"
#define System_Core_Clock 16000000
uint32_t Counter;

void SysTick_Handler(void);
void delay_ms(uint32_t delay);
void USART2_INIT (void);
void USART2_WRITE (int CH);
/**************************************************/
int main (void)
{
	USART2_INIT ();
	while (1)
	{
		USART2_WRITE ('O');
		USART2_WRITE (' ');
		delay_ms(1000);
		USART2_WRITE ('F');
		USART2_WRITE (' ');
		delay_ms(1000);
	}

}
/**************************************************/
void USART2_INIT (void)
{
	RCC->APB1ENR |= (1<<17);		// USART2 clock enable
	RCC->AHB1ENR |=(1<<0); 			// ENABLE PORT A CLOCK 
	GPIOA->AFR[0] = (7<<8);     // ENABLE ALTERNATE FUNCTION TO USE USART2
	GPIOA->MODER |= (1<<5);			// CONFIGURE PA2 IN ALTERNATE FUNCTION MODE
	
	USART2->BRR = 0X0683; 			// SET THE BUAD RATE 9600 AT 16MHz
	USART2->CR1 |= (1<<13);			// USART ENABLE
	USART2->CR1 |= (1<<3);			// TRANSMITTER ENABLE
	

}
/**************************************************/
void USART2_WRITE (int CH)
{
	while (!(USART2->SR & (1<<7)));		// WAIT UNTILL THE TRANSMIT DATA REGISTER IS EMPTY
	USART2->DR = CH & 0xFF;						// WRITE THE CHARACTER TO THE DATA REGISTER
	
}
/**************************************************/
void SysTick_Handler(void)
{
    if (Counter != 0x00)
    {
        Counter--;
    }
}

void delay_ms(uint32_t delay)
{
    SysTick_Config(System_Core_Clock / 1000);
    Counter = delay;
    while (Counter != 0)
    {
    }
}
