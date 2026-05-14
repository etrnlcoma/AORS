
#include <stdint.h>

typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
    volatile uint32_t AFRH;
} GPIO_TypeDef;

#define PERIPH_BASE         0x40000000UL
#define PERIPH_BITBAND_BASE 0x42000000UL
#define GPIOC_BASE          0x40020800UL
#define GPIOD_BASE          0x40020C00UL
#define RCC_AHB1ENR         (*(volatile uint32_t *)0x40023830UL)
#define GPIOC               ((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOCEN             (1U << 2)
#define GPIODEN             (1U << 3)

#define BITBAND_PERIPH(addr, bit) \
    (*(volatile uint32_t *)(PERIPH_BITBAND_BASE + \
    (((uint32_t)(addr) - PERIPH_BASE) * 32U) + ((uint32_t)(bit) * 4U)))

/* ── Таблица состояний варианта 4 ── */
static const uint8_t seq[] = {
    0b00000001,  // синий
    0b00000010,  // красный
    0b00000100,  // красный
    0b00001001,  // синий
    0b00010011,  // синий
    0b00100110   // красный
};
#define SEQ_LEN 6

volatile uint32_t step = 0;

/* Вывести текущее состояние на LED PC4..PC11 через bit-banding */
void update_leds(void)
{
    for (uint32_t i = 0; i < 8U; i++) {
        BITBAND_PERIPH(&GPIOC->ODR, 4U + i) = (seq[step] >> i) & 1U;
    }
}

int main(void)
{
    /* Тактирование */
    RCC_AHB1ENR |= GPIOCEN | GPIODEN;

    /* PC4..PC11 — выходы, push-pull */
    GPIOC->MODER  &= ~(0xFFFFU << 8);
    GPIOC->MODER  |=  (0x5555U << 8);   // 01 = output
    GPIOC->OTYPER &= ~(0xFFU  << 4);    // push-pull
    GPIOC->OSPEEDR&= ~(0xFFFFU << 8);   // low speed
    GPIOC->PUPDR  &= ~(0xFFFFU << 8);   // no pull

    /* PC13 — вход (синяя кнопка), pull-up */
    GPIOC->MODER &= ~(3U << (13 * 2));
    GPIOC->PUPDR &= ~(3U << (13 * 2));
    GPIOC->PUPDR |=  (1U << (13 * 2));  // pull-up

    /* PD2 — вход (красная кнопка), pull-up */
    GPIOD->MODER &= ~(3U << (2 * 2));
    GPIOD->PUPDR &= ~(3U << (2 * 2));
    GPIOD->PUPDR |=  (1U << (2 * 2));   // pull-up

    /* Начальное состояние */
    update_leds();

    for (;;)
    {
        /* Синяя кнопка PC13 нажата (active-low) */
        if (BITBAND_PERIPH(&GPIOC->IDR, 13) == 0U) {
            step = (step + 1U) % SEQ_LEN;
            update_leds();
            /* Ждём отпускания */
            while (BITBAND_PERIPH(&GPIOC->IDR, 13) == 0U) {}
        }

        /* Красная кнопка PD2 нажата (active-low) */
        if (BITBAND_PERIPH(&GPIOD->IDR, 2) == 0U) {
            step = (step + 1U) % SEQ_LEN;
            update_leds();
            /* Ждём отпускания */
            while (BITBAND_PERIPH(&GPIOD->IDR, 2) == 0U) {}
        }
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
