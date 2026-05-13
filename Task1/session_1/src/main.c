#include "main.h"
// #include "stm32f4xx.h"


// Синяя кнопка: PC13 → GPIOC->IDR (0x40020810), бит 13
// alias = 0x42000000 + 0x20810*32 + 13*4 = 0x42410234
#define BLUE_BTN BITBAND_PERIPH(GPIOC_BASE + 0x10UL, 13)

// Красная кнопка: PD2 → GPIOD->IDR (0x40020C10), бит 2
// alias = 0x42000000 + 0x20C10*32 + 2*4 = 0x42418208
#define RED_BTN BITBAND_PERIPH(GPIOD_BASE + 0x10UL, 2)

static void delay(volatile uint32_t n) { while (n--); } // Задержка для антидребезка

uint8_t  ledReg   = 0;
uint32_t prevBlue = 1;
uint32_t prevRed  = 1;



int main(void)
{

	RCC->AHB1ENR |= (1U << 0); //Тактирование порта A
	RCC->AHB1ENR |= (1U << 2); //Тактирование порта С
	RCC->AHB1ENR |= (1U << 3); //Тактирование порта D

	//Входы
	GPIOC->MODER &= ~(3U << 13 * 2); //Сброс 13го пина порта С
	GPIOC->PUPDR &= ~(3U << 13 * 2);

	GPIOD->MODER &= ~(3U << 2 * 2); //Сброс 2го пина порта D
	GPIOD->PUPDR &= ~(3U << 2 * 2); //Без подтяжки

	//Выходы
	GPIOA->MODER &= ~(3U << 15 * 2);
	GPIOA->MODER |=  (1U << 15 * 2);
	GPIOA->OTYPER &= ~(1U << 15);
    GPIOA->OSPEEDR |= (2U << (15 * 2));

	GPIOC->MODER &= ~(3U << 12 * 2);
	GPIOC->MODER |=  (1U << 12 * 2);
	GPIOC->OTYPER &= ~(1U << 12);
    GPIOC->OSPEEDR |= (2U << (12 * 2));

	GPIOC->MODER &= ~(3U << 4 * 2);
	GPIOC->MODER |=  (1U << 4 * 2);
	GPIOC->OTYPER &= ~(1U << 4);
    GPIOC->OSPEEDR |= (2U << (4 * 2));

	GPIOC->MODER &= ~(3U << 5 * 2);
	GPIOC->MODER |=  (1U << 5 * 2);
	GPIOC->OTYPER &= ~(1U << 5);
    GPIOC->OSPEEDR |= (2U << (5 * 2));

	GPIOC->MODER &= ~(3U << 6 * 2);
	GPIOC->MODER |=  (1U << 6 * 2);
	GPIOC->OTYPER &= ~(1U << 6);
    GPIOC->OSPEEDR |= (2U << (6 * 2));

	GPIOC->MODER &= ~(3U << 7 * 2);
	GPIOC->MODER |=  (1U << 7 * 2);
	GPIOC->OTYPER &= ~(1U << 7);
    GPIOC->OSPEEDR |= (2U << (7 * 2));
	
	GPIOC->MODER &= ~(3U << 8 * 2);
	GPIOC->MODER |=  (1U << 8 * 2);
	GPIOC->OTYPER &= ~(1U << 8);
    GPIOC->OSPEEDR |= (2U << (8 * 2));

	GPIOC->MODER &= ~(3U << 9 * 2);
	GPIOC->MODER |=  (1U << 9 * 2);
	GPIOC->OTYPER &= ~(1U << 9);
    GPIOC->OSPEEDR |= (2U << (9 * 2));

	GPIOC->MODER &= ~(3U << 10 * 2);
	GPIOC->MODER |=  (1U << 10 * 2);
	GPIOC->OTYPER &= ~(1U << 10);
    GPIOC->OSPEEDR |= (2U << (10 * 2));

	GPIOC->MODER &= ~(3U << 11 * 2);
	GPIOC->MODER |=  (1U << 11 * 2);
	GPIOC->OTYPER &= ~(1U << 11);
    GPIOC->OSPEEDR |= (2U << (11 * 2));

	// Все светодиоды выключены
	GPIOC->ODR &= ~(0xFF << 4);

	for(;;)
	{
		uint32_t blueNow = BLUE_BTN; // 0 когда нажата (active-low)
		uint32_t redNow  = RED_BTN;

		// Синяя кнопка сдвиг влево и вставить 1
		if (prevBlue && !blueNow) {
			delay(50000);
			if (!BLUE_BTN)
				ledReg = (uint8_t)((ledReg << 1) | 1U);
		}

		// Красная кнопка сдвиг влево и вставить 0
		if (prevRed && !redNow) {
			delay(50000);
			if (!RED_BTN)
				ledReg = (uint8_t)(ledReg << 1);
		}

		prevBlue = blueNow;
		prevRed  = redNow;

		// Вывод PC4 - PC11 через регистр ODR
		GPIOC->ODR = (GPIOC->ODR & ~(0xFF << 4)) | ((uint32_t)ledReg << 4);
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
