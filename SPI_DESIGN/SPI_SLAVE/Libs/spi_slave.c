#include "spi_slave.h"
#include "main.h"

void spi_slave_write_reg (SPI_HandleTypeDef *hspi, uint8_t address, uint16_t data)
{
	uint8_t send_buffer[] = {address, data >> 8, data & 0xFF};
	
	HAL_SPI_Transmit(hspi, send_buffer, 3, 100);
}

void spi_slave_read_reg(SPI_HandleTypeDef *hspi, uint8_t receive_buffer[])
{
	HAL_SPI_Receive(hspi, receive_buffer, 2, 100);
}



void spi_process_command(uint8_t receive_buffer[])
{
	uint8_t address = receive_buffer[0];
	uint8_t data = 0;
	switch (address)
	{
		case led_address:
			data = receive_buffer[1];
			break;
		default:
			break;
	}
		
	switch (data)
	{
		case led_on:
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
			break;
		case led_off:
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);
			break;
		default:
			break;
	}
}
