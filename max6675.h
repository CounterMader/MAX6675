/*
 * MAX6675.h
 *
 *  Created on: Sep 20, 2024
 *      Author: CounterMader
 */

#ifndef INC_MAX6675_H_
#define INC_MAX6675_H_

#include "stm32f4xx_hal.h"
#include "main.h"

#define TC1_CS_PORT			GPIOB
#define TC1_CS_PIN			GPIO_PIN_3

#define TC2_CS_PORT			GPIOB
#define TC2_CS_PIN			GPIO_PIN_4

#define TC3_CS_PORT			GPIOB
#define TC3_CS_PIN			GPIO_PIN_5

typedef struct{
	SPI_HandleTypeDef *max6675_spi_handle;
	uint32_t tnum;												// Number of thermocouples (min = 1, max = 3)
}max6675Handle_t;



uint16_t max6675_read(max6675Handle_t *handle);
HAL_StatusTypeDef max6675_init(uint32_t TC_num, max6675Handle_t *handle);
float max6675_get_temp(uint32_t tcn, max6675Handle_t *handle);

#endif /* INC_MAX6675_H_ */
