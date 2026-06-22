#include "spi_master.h"
#include "main.h"
uint16_t data = 0;
void spi_master_write_reg (SPI_HandleTypeDef *hspi, uint8_t address, uint8_t data)
{
	uint8_t send_buffer[] = {address, data};
	
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, 0);
	HAL_SPI_Transmit(hspi, send_buffer, 8, 100);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, 1);
}

void spi_master_read_reg(SPI_HandleTypeDef *hspi, uint8_t receive_buffer[])
{
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, 0);
	HAL_SPI_Receive(hspi, receive_buffer, 3, 100);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, 1);
}


void spi_process_command(uint8_t receive_buffer[])
{
	uint8_t address = receive_buffer[0];
	switch (address)
	{
		case led_address:
			data = (receive_buffer[1] << 8) | receive_buffer[2];
			break;
		default:
			break;
	}
}
