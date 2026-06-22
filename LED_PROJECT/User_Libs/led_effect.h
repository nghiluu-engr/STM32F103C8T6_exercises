#ifndef LED_EFFECT_H
#define LED_EFFECT_H
#include "stm32f1xx_hal.h"
#include "led_rgb.h"

typedef enum
{
	STATE_OFF,
	STATE_FADE_IN_OUT,
	STATE_RAINBOW_BLINK,
	STATE_RAINBOW_FOLLOW,
} LED_EFFECTS;

typedef struct
{
	RGB *led_1;
	RGB *led_2;
	RGB *led_3;
	RGB *led_4;
	
	LED_EFFECTS led_effects;
	COLOR color;
	
	uint8_t state;
	uint8_t state_rainbow;
	uint32_t start;
	uint16_t display_time;
} LED_CONTROL;

void led_effects_init(LED_CONTROL *led_control, RGB *led_1, RGB *led_2, RGB *led_3, RGB *led_4);
void state_off(LED_CONTROL *led_control);
void state_fade_in_out(LED_CONTROL *led_control);
void state_rainbow_blink(LED_CONTROL *led_control);
void state_rainbow_follow(LED_CONTROL *led_control);
#endif