#ifndef main_header
#define main_header

#include <stdint.h>


// Периферийный bit - banding 0x40000000 - 0x400FFFFF
// alias = PERIPH_BB_BASE + (byte_offset * 32) + (bit * 4)

#define PERIPH_BB_BASE 0x42000000UL
#define PERIPH_BASE 0x40000000UL

#define BITBAND_PERIPH(addr, bit) \
    (*(volatile uint32_t *)(PERIPH_BB_BASE + \
     ((uint32_t)(addr) - PERIPH_BASE) * 32UL + \
     (uint32_t)(bit) * 4UL))

#define GPIOA_BASE 0x40020000UL
#define GPIOC_BASE 0x40020800UL
#define GPIOD_BASE 0x40020C00UL
#define RCC_BASE 0x40023800UL

typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} GPIO_TypeDef;

typedef struct {
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
    volatile uint32_t RESERVED0;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t RESERVED1[2];
    volatile uint32_t AHB1ENR;
} RCC_TypeDef;

#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOC ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD ((GPIO_TypeDef *) GPIOD_BASE)
#define RCC ((RCC_TypeDef  *) RCC_BASE)

#endif
