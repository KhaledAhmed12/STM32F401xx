/* ======================================== INCLUDES ========================================*/
# include "My_USART.h"

/* ======================================== MAIN ========================================*/
int main (void){
	
		begin(9600);
		char R_D;
	
		while (1)
		{
			R_D = read();
			
			if (R_D == 'O')

				GPIOB_BSRR = (1<<2);		// WHEN RECIEVING 'N' LED ON PB2 IT'S STATE IS ON 
				
			if (R_D == 'F')
				
				GPIOB_BSRR = (1<<18);		// WHEN RECIEVING 'F' LED ON PB2 IT'S STATE IS OFF
				
			
		}

	
}

/* ======================================== DEFINITIONS ========================================*/
/*----------------------------------------------------------------------------------------------*/
/* ======================================== BEGIN ========================================*/
void begin(uint32_t baudRate)
{ 
/*-------------------------------------------- Initialize the GPIO --------------------------------------------------*/
		RCC_CR |= (1<<0);							//Enable HSI Clock
	
		while(!(RCC_CR & (1<<1))) { } // waits until HSI is ready

    RCC_AHB1ENR |= (1<<0); 			// ENABLE PORT A CLOCK
		RCC_AHB1ENR |= (1<<1);		// ENABLE PORT B CLOCK 
		
		GPIOB_MODER |= (1<<4);		// CONFIGURE PB2 AS OUTPUT
		
		
		GPIOA_MODER |= (1<<7);				// CONFIGURE PA3 IN ALTERNATE FUNCTION MODE
    GPIOA_AFRL = (7<<12);     		// ENABLE ALTERNATE FUNCTION TO USE USART2 (ON PA2)
		
/*-------------------------------------------- Initialize USART --------------------------------------------------*/		
		RCC_APB1ENR |= (1<<17); 			// USART2 clock enable
		
		USART2_CR1 |= (1<<15);		  	//Set the over sampling bit to over sample by 8
    USART2_CR1 |= (1<<13);				// USART ENABLE
		USART2_CR1 &=~(1<<12); 				// 0:To Set word length to 1 start bit and 8 data bits
    USART2_CR1 &=~(1<<10); 				// Set parity enable to zero to disable parity
		USART2_CR1 |= (1<<2);					// RECIEVER  ENABLE
    
		
		USART2_CR2 &=~ (1<<13); 			// Set bit 12 and 13 as zero for 1 stop bit
    USART2_CR2 &=~ (1<<12); 			// Set bit 12 and 13 as zero for 1 stop bit
    USART2_CR2 &=~ (1<<11); 			// Disable clock
		
    USART2_CR3 |= (1<<11);				// One sample per bit
    USART2_CR3 &=~ (1<<3); 				// Half-duplex mode is disabled
    
/*-------------------------------------------- SET THE GIVEN BAUD_RATE --------------------------------------------------*/
		double USART_DIV = (double)System_Core_Clock / (8.0 * baudRate);
    uint32_t DIV_Mantissa = (uint32_t)USART_DIV;
    uint32_t DIV_Fraction = (uint32_t)((USART_DIV - (double)DIV_Mantissa) * 8.0);
    USART2_BRR = (DIV_Mantissa << 4) | (DIV_Fraction & 0x0F);

}

/* ======================================== AVAILABLE ========================================*/
STATE available(void) 
{
	 return (USART2_SR & (1 << 5)) != 0;		// CHECK "RXNE" (Read data register not empty)
	  // If STATE == 1 SO, THERE IS DATA AVAILABLE
}

/* ======================================== READ ONE BYTE ========================================*/
DATA_RECEIVED read(void)
{
    while (!(USART2_SR & (1 << 5))){}		// WAIT UNTILL THE RECIEVING DATA REGISTER IS EMPTY
    return USART2_DR & 0xFF; 						// RETURN THE DATA WHICH IN THE DATA REGISTER
}

/* ======================================== READ_BYTES ========================================*/
void readBytes(uint8_t* BUFFER, uint32_t LENGTH)
{
    for (uint32_t i = 0; i < LENGTH; ++i)
    {
        while (!(USART2_SR & (1 << 5))){}		// WAIT UNTILL THE RECIEVING DATA REGISTER IS EMPTY
        BUFFER[i] = USART2_DR & 0xFF;			  // buffer[i] = USART1->DR; // Read received data
    }
}

/* ======================================== WRITE ONE BYTE ========================================*/
// Overloaded function: Sends a single byte
void write(uint8_t BYTE) 
{
    while (!(USART2_SR & (1 << 7))){}		// WAIT UNTILL THE TRANSMIT DATA REGISTER IS EMPTY
    USART2_DR = BYTE & 0xFF;						// WRITE THE CHARACTER TO THE DATA REGISTER
}
/* ======================================== WRITE_BYTES ========================================*/
void writeBytes(uint8_t *BUFFER, uint32_t LENGTH) {
    for (uint32_t i = 0; i < LENGTH; ++i) {
        while (!(USART2_SR & (1 << 7))){}		// WAIT UNTILL THE TRANSMIT DATA REGISTER IS EMPTY
        USART2_DR = BUFFER[i];							// WRITE THE CHARACTER TO THE DATA REGISTER
    }
}
/* ======================================== PRINT ========================================*/
void print(const char *str)
{
    while (*str != '\0')
     {
        while (!(USART2_SR & (1 << 7))){}		// WAIT UNTILL THE TRANSMIT DATA REGISTER IS EMPTY

        USART2_DR = (uint32_t)(*str++);			// WRITE THE CHARACTER TO THE DATA REGISTER
    }
}
/* ======================================== PRINTLN ========================================*/
void println(const char *str)
{
    while (*str != '\0')
     {
        while (!(USART2_SR & (1 << 7))){}		// WAIT UNTILL THE TRANSMIT DATA REGISTER IS EMPTY

        USART2_DR = (uint32_t)(*str++);			// WRITE THE CHARACTER TO THE DATA REGISTER
     }

    while (!(USART2_SR & (1 << 7)));
    USART2_DR = '\0'; 											// SEND NULL
}
/* ======================================== BEGIN ========================================*/
void delay_ms(unsigned int delay){ 
	 RCC_APB1ENR |= (1<<0); 							// ENABLE TIMER_2
	 TIM2_CR1 |= (1<<7); 									// SET AUTO RELOAD REGISTER 
	 TIM2_CR1 &=~ ((1<<5) | (1<<6) );			// EDGE ALLIGNED MODE (UP OR DOWN ONLY) 
	 TIM2_CR1 &=~ (1<<4);  								// SET THE DIRECTION TO "UP" 

 //COUNTER FREQUENCY = Fclk /PSC (16MHz / (15999+1)) = 1 kHz 
	 TIM2_PSC = 15999;
	 TIM2_ARR = 10000; 										//THE MAX. COUNTER NUMBER (MAX. SECONDS 10s) 
	 TIM2_EGR |= (1<<0); 									// INITIALIZE THE COUNTER TO START FROM ZERO 
	 TIM2_CR1 |= (1<<0); 									// START THE COUNTER 
	 //while (!(TIM2_SR & (1<<0)));  // UIF: Update interrupt flag
	 TIM2_CNT = 0;
	 unsigned int target = TIM2_CNT + delay;
	 while(TIM2_CNT < target); 						// WAIT TO THE COUNTER IN THIS WHILE LOOP  
	 TIM2_CR1 &=~ (1<<0); 								// STOP THE COUNTER

}
