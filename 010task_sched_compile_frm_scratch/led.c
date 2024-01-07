/*
 * led.c
 *
 *  Created on: Dec 21, 2023
 *      Author: pubudu
 */

#include "led.h"

#define GPIOG_REG_BASE	0x40021800
#define RCC_REG_BASE	0x40023800

#define GRN_LED_OFFSET	13
#define RED_LED_OFFSET	14

const uint32_t test1 = 100;
const uint32_t test2 = 455;
const uint8_t test3 = 45;

void init_leds(void)
{
	uint32_t *pRCC_AHB1ENR = (uint32_t *)(RCC_REG_BASE + 0x30);

	uint32_t *pGPIO_G_MODER = (uint32_t *)(GPIOG_REG_BASE + 0x00);
	uint32_t *pGPIO_G_OTYPER = (uint32_t *)(GPIOG_REG_BASE + 0x04);
	uint32_t *pGPIO_G_AFRHR = (uint32_t *)(GPIOG_REG_BASE + 0x24);

	// enable GPIO G clock
	*pRCC_AHB1ENR |= (1 << 6);

	//set alternative function to GPIO - GPIOx_AFR (Though on reset AF0)
	*pGPIO_G_AFRHR &= ~(0x0FF00000); // Set AF0 for bit 13&14 (PG13/PG14) - 0 AF0

	//set mode to gpio output - GPIOx_MODER
	*pGPIO_G_MODER &= ~(1 << (GRN_LED_OFFSET * 2 + 1));
	*pGPIO_G_MODER |= (01 << GRN_LED_OFFSET * 2);

	*pGPIO_G_MODER &= ~(1 << (RED_LED_OFFSET * 2 + 1));
	*pGPIO_G_MODER |= (1 << (RED_LED_OFFSET * 2));

	//set output type to push-pull
	*pGPIO_G_OTYPER &= ~(1 << GRN_LED_OFFSET); // 0 - push-pull
	*pGPIO_G_OTYPER &= ~(1 << RED_LED_OFFSET); // 0 - push-pull
}

void led_on(uint8_t led)
{
	uint32_t *pGPIO_G_BSRR = (uint32_t *)(GPIOG_REG_BASE + 0x18);

	switch(led)
	{
	case GRN_LED:
		*pGPIO_G_BSRR |= (1 << GRN_LED_OFFSET);
		break;
	case RED_LED:
		*pGPIO_G_BSRR |= (1 << RED_LED_OFFSET);
			break;
	default:
		break;
	}
}

void led_off(uint8_t led)
{
	uint32_t *pGPIO_G_BSRR = (uint32_t *)(GPIOG_REG_BASE + 0x18);

	switch(led)
	{
	case GRN_LED:
		*pGPIO_G_BSRR |= (1 << (16 + GRN_LED_OFFSET));
		break;
	case RED_LED:
		*pGPIO_G_BSRR |= (1 << (16 + RED_LED_OFFSET));
			break;
	default:
		break;
	}
}
