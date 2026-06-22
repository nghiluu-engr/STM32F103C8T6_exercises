#include "led_effect.h"
#include "led_rgb.h"

void led_effects_init(LED_CONTROL *led_control, RGB *led_1, RGB *led_2, RGB *led_3, RGB *led_4)
{
	led_control->led_1 = led_1;
	led_control->led_2 = led_2;
	led_control->led_3 = led_3;
	led_control->led_4 = led_4;
	
	led_control->state = 0;
	led_control->state_rainbow = 0;
	led_control->start = HAL_GetTick();
	led_control->display_time = 1000;
	
	led_control->led_effects = STATE_OFF;
}

void state_off(LED_CONTROL *led_control)
{
	led_rgb_SetColor(led_control->led_1, OFF);
	led_rgb_SetColor(led_control->led_2, OFF);
	led_rgb_SetColor(led_control->led_3, OFF);
	led_rgb_SetColor(led_control->led_4, OFF);
}

void state_SetColor(LED_CONTROL *led_control)
{
	if (HAL_GetTick() - led_control->start >= led_control->display_time)
	{
		led_rgb_SetColor(led_control->led_1, led_control->led_1->color);
		led_rgb_SetColor(led_control->led_2, led_control->led_2->color);
		led_rgb_SetColor(led_control->led_3, led_control->led_3->color);
		led_rgb_SetColor(led_control->led_4, led_control->led_4->color);
		led_control->start = HAL_GetTick();
		led_control->state++;
	}
}


void state_fade_in_out(LED_CONTROL *led_control)
{
	switch (led_control->state)
	{
		case 0:
			led_control->led_1->color = RED;
			led_control->led_2->color = OFF;
			led_control->led_3->color = OFF;
			led_control->led_4->color = OFF;
			state_SetColor(led_control);
			break;
		case 1:
			led_control->led_1->color = RED;
			led_control->led_2->color = GREEN;
			led_control->led_3->color = OFF;
			led_control->led_4->color = OFF;
			state_SetColor(led_control);
			break;
		case 2:
			led_control->led_1->color = RED;
			led_control->led_2->color = GREEN;
			led_control->led_3->color = BLUE;
			led_control->led_4->color = OFF;
			state_SetColor(led_control);
			break;
		case 3:
			led_control->led_1->color = RED;
			led_control->led_2->color = GREEN;
			led_control->led_3->color = BLUE;
			led_control->led_4->color = WHITE;
			state_SetColor(led_control);
			break;
		case 4:
			led_control->led_1->color = RED;
			led_control->led_2->color = GREEN;
			led_control->led_3->color = BLUE;
			led_control->led_4->color = OFF;
			state_SetColor(led_control);
		case 5:
			led_control->led_1->color = RED;
			led_control->led_2->color = GREEN;
			led_control->led_3->color = OFF;
			led_control->led_4->color = OFF;
			state_SetColor(led_control);
			break;
		case 6:
			led_control->led_1->color = RED;
			led_control->led_2->color = OFF;
			led_control->led_3->color = OFF;
			led_control->led_4->color = OFF;
			state_SetColor(led_control);
			break;
		default:
			state_off(led_control);
			led_control->state = 0;
			break;
	}
}
void state_rainbow_blink(LED_CONTROL *led_control)
{
	switch (led_control->state)
	{
		case 0:
			led_control->led_1->color = RED;
			led_control->led_2->color = RED;
			led_control->led_3->color = RED;
			led_control->led_4->color = RED;
			state_SetColor(led_control);
			break;
		case 1:
			led_control->led_1->color = YELLOW;
			led_control->led_2->color = YELLOW;
			led_control->led_3->color = YELLOW;
			led_control->led_4->color = YELLOW;
			state_SetColor(led_control);
			break;
		case 2:
			led_control->led_1->color = GREEN;
			led_control->led_2->color = GREEN;
			led_control->led_3->color = GREEN;
			led_control->led_4->color = GREEN;
			state_SetColor(led_control);
			break;
		case 3:
			led_control->led_1->color = BLUE;
			led_control->led_2->color = BLUE;
			led_control->led_3->color = BLUE;
			led_control->led_4->color = BLUE;
			state_SetColor(led_control);
			break;
		case 4:
			led_control->led_1->color = CYAN;
			led_control->led_2->color = CYAN;
			led_control->led_3->color = CYAN;
			led_control->led_4->color = CYAN;
			state_SetColor(led_control);
		case 5:
			led_control->led_1->color = PURPLE;
			led_control->led_2->color = PURPLE;
			led_control->led_3->color = PURPLE;
			led_control->led_4->color = PURPLE;
			state_SetColor(led_control);
			break;
		case 6:
			led_control->led_1->color = WHITE;
			led_control->led_2->color = WHITE;
			led_control->led_3->color = WHITE;
			led_control->led_4->color = WHITE;
			state_SetColor(led_control);
			break;
		default:
			led_control->state = 0;
			break;
	}
}

void state_1_rainbow(LED_CONTROL *led_control)
{
	switch (led_control->state)
	{
		case 0:
			led_control->led_1->color = RED;
			led_control->led_2->color = OFF;
			led_control->led_3->color = OFF;
			led_control->led_4->color = OFF;
			state_SetColor(led_control);
			break;
		case 1:
			led_control->led_1->color = YELLOW;
			led_control->led_2->color = OFF;
			led_control->led_3->color = OFF;
			led_control->led_4->color = OFF;
			state_SetColor(led_control);
			break;
		case 2:
			led_control->led_1->color = GREEN;
			led_control->led_2->color = OFF;
			led_control->led_3->color = OFF;
			led_control->led_4->color = OFF;
			state_SetColor(led_control);
			break;
		case 3:
			led_control->led_1->color = BLUE;
			led_control->led_2->color = OFF;
			led_control->led_3->color = OFF;
			led_control->led_4->color = OFF;
			state_SetColor(led_control);
			break;
		case 4:
			led_control->led_1->color = CYAN;
			led_control->led_2->color = OFF;
			led_control->led_3->color = OFF;
			led_control->led_4->color = OFF;
			state_SetColor(led_control);
		case 5:
			led_control->led_1->color = PURPLE;
			led_control->led_2->color = OFF;
			led_control->led_3->color = OFF;
			led_control->led_4->color = OFF;
			state_SetColor(led_control);
			break;
		case 6:
			led_control->led_1->color = WHITE;
			led_control->led_2->color = OFF;
			led_control->led_3->color = OFF;
			led_control->led_4->color = OFF;
			state_SetColor(led_control);
			break;
		default:
			led_control->state = 0;
			break;
	}
}
void set_state_rainbow_follow(LED_CONTROL *led_control)
{
	
}
void state_rainbow_follow(LED_CONTROL *led_control)
{
	switch (led_control->state_rainbow)
	{
		case 0:
			if (HAL_GetTick() - led_control->start >= led_control->display_time)
			{
				state_1_rainbow(led_control);
				led_control->start = HAL_GetTick();
			}
			break;
		default:
			led_control->state_rainbow = 0;
			break;
	}
}