#ifndef SPI_MASTER_H
#define SPI_MASTER_H
#include "stm32f1xx_hal.h"


#define spi_read 0x80
#define spi_wri 0x00

#define led_address 0xAE
#define led_on 0x01
#define led_off 0x10

void spi_slave_write_reg(SPI_HandleTypeDef *hspi, uint8_t address, uint16_t data);
void spi_slave_read_reg(SPI_HandleTypeDef *hspi, uint8_t receive_buffer[]);
void spi_process_command(uint8_t receive_buffer[]);
#endif