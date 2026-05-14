#include "main.h"

#include "stm32f4xx.h"


volatile uint32_t int_val;

volatile uint32_t usart_data;


int main()
{
	// Write your code here!

	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;   
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN;

    
    GPIOC->MODER  &= ~(3U << (10 * 2));
    GPIOC->MODER  |=  (2U << (10 * 2));
    GPIOC->AFR[1] &= ~(0xFU << ((10-8)*4));
    GPIOC->AFR[1] |=  (7U   << ((10-8)*4));    

    GPIOD->MODER  &= ~(3U << (9 * 2));
    GPIOD->MODER  |=  (2U << (9 * 2));
    GPIOD->AFR[1] &= ~(0xFU << ((9-8)*4));
    GPIOD->AFR[1] |=  (7U   << ((9-8)*4)); 

    USART3->BRR = 16000000U / 115200U;

    USART3->CR1 |= USART_CR1_PCE | USART_CR1_PS;  
    USART3->CR2 &= ~USART_CR2_STOP;               
    USART3->CR1 |= USART_CR1_TE | USART_CR1_RE;
    USART3->CR1 |= USART_CR1_IDLEIE;
            
    NVIC_SetPriority(USART3_IRQn, 9);
    NVIC_EnableIRQ(USART3_IRQn);

    USART3->CR1 |= USART_CR1_UE;

    
    int_val = USART3->SR & USART_SR_IDLE;

    usart_data = (uint32_t)USART3->DR;

    while (!(USART3->SR & USART_SR_TXE));
    USART3->DR = '/';
	for(;;)
	{
		// infinite loop
	}
}

void USART3_IRQHandler(void)
{
    if (USART3->SR & USART_SR_IDLE) {
        (void)USART3->SR;
        (void)USART3->DR;
    }
}

 void NMI_Handler(void)
{
	while(1){};
}

 void HardFault_Handler(void)
{
	while(1){};
}

 void MemManage_Handler(void)
{
	while(1){};
}

 void BusFault_Handler(void)
{
	while(1){};
}

 void UsageFault_Handler(void)
{
	while(1){};
}