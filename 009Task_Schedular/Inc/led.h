/*
 * led.h
 *
 *  Created on: Dec 21, 2023
 *      Author: pubudu
 */

#ifndef LED_H_
#define LED_H_

#include <stdint.h>

#define GRN_LED			1
#define RED_LED			2

void init_leds(void);
void led_on(uint8_t led);
void led_off(uint8_t led);

#endif /* LED_H_ */
