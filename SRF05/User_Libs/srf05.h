#ifndef SRF05_H
#define SRF05_H
#include "stm32f1xx_hal.h"
#include "main.h"

typedef enum
{
	SENSOR_IDLE,
	SENSOR_ERROR,
	SENSOR_TRIGGER,
	SENSOR_PROCESS,
	SENSOR_RESULTS,
} SENSOR_STATE;

typedef struct
{
	TIM_HandleTypeDef *htim;
	GPIO_TypeDef *sensor_port; 
	uint16_t sensor_pin;
	
	SENSOR_STATE sensor_state;
	
	uint8_t trigger_time;
	uint32_t echo_high_time;
	float distance;
	
	uint32_t sensor_handle_time;
	uint32_t sensor_trigger_time;
	uint32_t sensor_process_time;
	
} SENSOR;

void sensor_init(SENSOR *sensor, TIM_HandleTypeDef *htim, GPIO_TypeDef *sensor_port, uint16_t sensor_pin);

void sensor_trigger(SENSOR *sensor);
void sensor_process(SENSOR *sensor);
void sensor_results(SENSOR *sensor);
void sensor_error(SENSOR *sensor);

void sensor_handle(SENSOR *sensor);

#endif