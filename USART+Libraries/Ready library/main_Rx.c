# include "stm32f4xx.h"
void USART2_INIT (void);
char USART2_READ (void);
/**************************************************/
int main (void)
{
	char R_D; 
	RCC->AHB1ENR |=(1<<1);		// ENABLE PORT B CLOCK 
	GPIOB->MODER |= (1<<4);		// CONFIGURE PB2 AS OUTPUT
	
	USART2_INIT ();
	
	
	while (1)
	{
		R_D = USART2_READ ();
		
		if (R_D == 'O')
			GPIOB->BSRR = (1<<2);		// WHEN RECIEVING 'N' LED ON PB2 IT'S STATE IS ON 
		if (R_D == 'F')
			GPIOB->BSRR = (1<<18);		// WHEN RECIEVING 'F' LED ON PB2 IT'S STATE IS OFF 
		
	}

}
/**************************************************/
void USART2_INIT (void)
{
	RCC->APB1ENR |= (1<<17);		// USART2 clock enable
	RCC->AHB1ENR |=(1<<0); 			// ENABLE PORT A CLOCK 
	GPIOA->AFR[0] = (7<<12);     // ENABLE ALTERNATE FUNCTION TO USE USART2 (ON PA3)
	GPIOA->MODER |= (1<<7);			// CONFIGURE PA3 IN ALTERNATE FUNCTION MODE (Rx)
	
	USART2->BRR = 0X0683; 			// SET THE BUAD RATE 9600 AT 16MHz
	USART2->CR1 |= (1<<13);			// USART ENABLE
	USART2->CR1 |= (1<<2);			// RECIEVER ENABLE
	

}
/**************************************************/
char USART2_READ (void)
{
	while (!(USART2->SR & (1<<5))){}		// WAIT UNTILL THE RECIEVING DATA REGISTER IS EMPTY
	return USART2->DR ;						// RETURN THE CHARACTER IN THE DATA REGISTER
	
}
/**************************************************/
