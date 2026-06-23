#include "srf05.h"

void sensor_init(SENSOR *sensor, TIM_HandleTypeDef *htim, GPIO_TypeDef *sensor_port, uint16_t sensor_pin)
{
	sensor->htim = htim;
	sensor->sensor_port = sensor_port;
	sensor->sensor_pin = sensor_pin;
	
	sensor->sensor_state = SENSOR_IDLE;
	
	sensor->trigger_time = 100;
	sensor->echo_high_time = 0;
	sensor->distance = 0.0f;
	
	sensor->sensor_handle_time = 100;
	sensor->sensor_trigger_time = 0;
	sensor->sensor_process_time = 0;
}


void sensor_trigger(SENSOR *sensor)
{
	HAL_GPIO_WritePin(sensor->sensor_port, sensor->sensor_pin, 1);
	HAL_Delay(sensor->trigger_time);
	HAL_GPIO_WritePin(sensor->sensor_port, sensor->sensor_pin, 0);
	
	sensor->sensor_trigger_time = HAL_GetTick();
}


void sensor_process(SENSOR *sensor)
{
	if (HAL_GPIO_ReadPin(sensor->sensor_port, sensor->sensor_pin) == 1)
	{
		sensor->htim->Instance->CNT = 0;
		HAL_TIM_Base_Start(sensor->htim);
	}
	else
	{
		HAL_TIM_Base_Stop(sensor->htim);	
		sensor->sensor_process_time = HAL_GetTick();
	}
}


void sensor_error(SENSOR *sensor)
{
	if (HAL_GetTick() - sensor->sensor_trigger_time >= sensor->sensor_handle_time)
	{
		sensor->sensor_state = SENSOR_ERROR;
	}
	if (HAL_GetTick() - sensor->sensor_process_time >= sensor->sensor_handle_time)
	{
		sensor->sensor_state = SENSOR_ERROR;
	}
}


void sensor_results(SENSOR *sensor)
{
	sensor->echo_high_time = sensor->htim->Instance->CNT;
	sensor->distance = (343 * sensor->echo_high_time) * 1e-6; //meter
}


void sensor_handle(SENSOR *sensor)
{
	switch (sensor->sensor_state)
	{
		case SENSOR_IDLE:
			sensor->sensor_state = SENSOR_TRIGGER;
			break;
		case SENSOR_TRIGGER:
			sensor_trigger(sensor);
			sensor->sensor_state = SENSOR_PROCESS;
			break;
		case SENSOR_PROCESS:
			sensor_process(sensor);
			sensor->sensor_state = SENSOR_RESULTS;
			break;
		case SENSOR_RESULTS:
			sensor_results(sensor);
			sensor->sensor_state = SENSOR_IDLE;
			break;
		case SENSOR_ERROR:
			sensor_error(sensor);
			sensor->sensor_state = SENSOR_IDLE;
			break;
		default:
			break;
	}
}