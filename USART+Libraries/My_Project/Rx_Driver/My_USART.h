/* ======================================== START__H ========================================*/
		#ifndef USART_1__H
		#define USART_1__H
/* ======================================== MACROS ========================================*/
		#include <stdint.h>
		#define STATE uint8_t
		#define DATA_RECEIVED uint8_t
/* ======================================== DECLARATIONS ========================================*/

		void begin(uint32_t baudRate);
		
		STATE available(void);
		
		DATA_RECEIVED read(void);
		
		void readBytes(uint8_t* BUFFER, uint32_t LENGTH);
		
		void write(uint8_t byte);
		
		void writeBytes(uint8_t *BUFFER, uint32_t LENGTH);
		
		void print(const char *str);
		
		void println(const char *str);
		
		void delay_ms(unsigned int delay);		
		
/* ======================================== MACROS_BASE ========================================*/

		#define System_Core_Clock   16000000 			// system clock 

		#define RCC_BASE            0x40023800U		// Define register addresses for RCC

		#define GPIOA_BASE          0x40020000U		// Define register addresses for GPIOA

		#define GPIOB_BASE          0x40020400U		// Define register addresses for GPIOB

		#define USART2_BASE         0x40004400U		// Define register addresses for USART2

		#define TIM2_BASE           0x40000000U		//Define register addresses for TIM2
		
/* ======================================== RCC ========================================*/

		#define RCC_AHB1ENR_OFFSET  0x30U
		#define RCC_APB1ENR_OFFSET  0x40U
		#define RCC_APB2ENR_OFFSET  0x44U
		#define RCC_CR_OFFSET   0x00U

		#define RCC_AHB1ENR (*((volatile uint32_t *)(RCC_BASE + RCC_AHB1ENR_OFFSET)))
		#define RCC_APB1ENR (*((volatile uint32_t *)(RCC_BASE + RCC_APB1ENR_OFFSET)))
		#define RCC_APB2ENR (*((volatile uint32_t *)(RCC_BASE + RCC_APB2ENR_OFFSET)))
		#define RCC_CR (*((volatile uint32_t *)(RCC_BASE + RCC_CR_OFFSET)))
			
/* ======================================== GPIO ========================================*/
		
		#define GPIOx_MODER_OFFSET  0x00U
		#define GPIOx_AFRL_OFFSET   0x20U
		#define GPIOB_BSRR_OFFSET   0x18U
		
		#define GPIOA_MODER (*((volatile uint32_t *)(GPIOA_BASE + GPIOx_MODER_OFFSET)))
		#define GPIOA_AFRL  (*((volatile uint32_t *)(GPIOA_BASE + GPIOx_AFRL_OFFSET)))
			
		#define GPIOB_MODER (*((volatile uint32_t *)(GPIOB_BASE + GPIOx_MODER_OFFSET)))
		#define GPIOB_AFRL  (*((volatile uint32_t *)(GPIOB_BASE + GPIOx_AFRL_OFFSET)))
		#define GPIOB_BSRR  (*((volatile uint32_t *)(GPIOB_BASE + GPIOB_BSRR_OFFSET)))
			
/* ======================================== USART ========================================*/
		
		#define USART_SR_OFFSET     0x00U
		#define USART_DR_OFFSET     0x04U
		#define USART_BRR_OFFSET    0x08U
		#define USART_CR1_OFFSET    0x0CU
		#define USART_CR2_OFFSET    0x10U
		#define USART_CR3_OFFSET    0x14U
		#define USART_SR_OFFSET     0x00U
		#define USART_DR_OFFSET     0x04U
		
		#define USART2_SR   (*((volatile uint32_t *)(USART2_BASE + USART_SR_OFFSET)))
		#define USART2_DR   (*((volatile uint32_t *)(USART2_BASE + USART_DR_OFFSET)))
		#define USART2_BRR  (*((volatile uint32_t *)(USART2_BASE + USART_BRR_OFFSET)))
		#define USART2_CR1  (*((volatile uint32_t *)(USART2_BASE + USART_CR1_OFFSET)))
		#define USART2_CR2  (*((volatile uint32_t *)(USART2_BASE + USART_CR2_OFFSET)))
		#define USART2_CR3  (*((volatile uint32_t *)(USART2_BASE + USART_CR3_OFFSET)))
		#define USART2_SR   (*((volatile uint32_t *)(USART2_BASE + USART_SR_OFFSET)))
		#define USART2_DR   (*((volatile uint32_t *)(USART2_BASE + USART_DR_OFFSET)))
			
/* ======================================== USART ========================================*/
		
		#define TIM2_CR1_OFFSET  0x00U
		#define TIM2_SR_OFFSET   0x10U
		#define TIM2_CNT_OFFSET  0x24U
		#define TIM2_PSC_OFFSET  0x28U
		#define TIM2_ARR_OFFSET  0x2CU
		#define TIM2_EGR_OFFSET  0x14U
		
		#define TIM2_CR1 (*((volatile uint32_t *)(TIM2_BASE + TIM2_CR1_OFFSET)))
		#define TIM2_SR  (*((volatile uint32_t *)(TIM2_BASE + TIM2_SR_OFFSET)))
		#define TIM2_CNT (*((volatile uint32_t *)(TIM2_BASE + TIM2_CNT_OFFSET)))
		#define TIM2_PSC (*((volatile uint32_t *)(TIM2_BASE + TIM2_PSC_OFFSET)))
		#define TIM2_ARR (*((volatile uint32_t *)(TIM2_BASE + TIM2_ARR_OFFSET)))
		#define TIM2_EGR (*((volatile uint32_t *)(TIM2_BASE + TIM2_EGR_OFFSET)))
			
/* ======================================== END__H ========================================*/

		#endif /*USART_1__H*/
