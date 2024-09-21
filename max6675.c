/*
 * MAX6675.c
 *
 *  Created on: Sep 20, 2024
 *      Author: CounterMader
 */

#include "MAX6675.h"

uint16_t max6675_read(max6675Handle_t *handle){

	uint8_t data[2];
	uint16_t ret = 0;
	HAL_StatusTypeDef status;

	status = HAL_SPI_Receive(handle -> max6675_spi_handle, data, 1, HAL_MAX_DELAY);

	if(status != HAL_OK)
		Error_Handler();

	ret = (data[0] << 8) | (data[1]);

	return ret;
}

HAL_StatusTypeDef max6675_init(uint32_t TC_num, max6675Handle_t *handle){

	uint16_t buff;
	uint32_t tnum = 0;

	if(handle == NULL)
		return HAL_ERROR;

	handle -> tnum = TC_num;

	/*
	 * Set CS Pin's High
	 */

	HAL_GPIO_WritePin(TC1_CS_PORT, TC1_CS_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(TC2_CS_PORT, TC2_CS_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(TC3_CS_PORT, TC3_CS_PIN, GPIO_PIN_SET);

	/*
	 * Check Connection of Thermocouples
	 */

	HAL_GPIO_WritePin(TC1_CS_PORT, TC1_CS_PIN, GPIO_PIN_RESET);
	buff = max6675_read(handle);
	HAL_GPIO_WritePin(TC1_CS_PORT, TC1_CS_PIN, GPIO_PIN_SET);

	if((buff & 0x0004) == 0)
		tnum++;

	HAL_GPIO_WritePin(TC2_CS_PORT, TC2_CS_PIN, GPIO_PIN_RESET);
	buff = max6675_read(handle);
	HAL_GPIO_WritePin(TC2_CS_PORT, TC2_CS_PIN, GPIO_PIN_SET);

	if((buff & 0x0004) == 0)
		tnum++;

	HAL_GPIO_WritePin(TC3_CS_PORT, TC3_CS_PIN, GPIO_PIN_RESET);
	buff = max6675_read(handle);
	HAL_GPIO_WritePin(TC3_CS_PORT, TC3_CS_PIN, GPIO_PIN_SET);

	if((buff & 0x0004) == 0)
		tnum++;

	if(tnum == handle -> tnum)
		return HAL_OK;
	else
		return HAL_ERROR;
}


float max6675_get_temp(uint32_t tcn, max6675Handle_t *handle){
	uint16_t buff;
	float temprature;

	if(tcn == 1){
		HAL_GPIO_WritePin(TC1_CS_PORT, TC1_CS_PIN, GPIO_PIN_RESET);
		buff = max6675_read(handle);
		HAL_GPIO_WritePin(TC1_CS_PORT, TC1_CS_PIN, GPIO_PIN_SET);
	}
	else if(tcn == 2){
		HAL_GPIO_WritePin(TC2_CS_PORT, TC2_CS_PIN, GPIO_PIN_RESET);
		buff = max6675_read(handle);
		HAL_GPIO_WritePin(TC2_CS_PORT, TC2_CS_PIN, GPIO_PIN_SET);
	}
	else if(tcn == 3){
		HAL_GPIO_WritePin(TC3_CS_PORT, TC3_CS_PIN, GPIO_PIN_RESET);
		buff = max6675_read(handle);
		HAL_GPIO_WritePin(TC3_CS_PORT, TC3_CS_PIN, GPIO_PIN_SET);
	}

	buff = (buff >> 3);
	temprature = (float)buff * 0.25;

	return temprature;
}

