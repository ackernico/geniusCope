/*
 * MPU9250.c
 *
 *  Created on: May 10, 2025
 *      Author: Nicolas Acker
 */
#include "MPU9250.h"
#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;

void MPU9250_Init()
{
	uint8_t writeConfig = FS_GYRO_500;
	char message[100];

	/* Verifying if the device is ready */
	HAL_StatusTypeDef ret = HAL_I2C_IsDeviceReady(&hi2c1, (DEVICE_ADRESS << 1) + 0, 1, 100);
	if(ret == HAL_OK)
	{
		strncpy(message, "Device is ready to connect\r\n", sizeof(message));
	}
	else
	{
		strncpy(message, "Device is not ready to connect\r\n", sizeof(message));
	}
	HAL_UART_Transmit(&huart2, message, strlen(message), 50);

	/* Configurating Gyroscope */
	ret = HAL_I2C_Mem_Write(&hi2c1, (DEVICE_ADRESS << 1) + 0, REG_CONFIG_GYRO, 1, &writeConfig, 1, 100);
	if(ret == HAL_OK)
	{
		strncpy(message, "Gyroscope configured successfully\r\n", sizeof(message));
	}
	else
	{
		strncpy(message, "Error while configuring gyroscope\r\n", sizeof(message));
	}
	HAL_UART_Transmit(&huart2, message, strlen(message), 50);

	/* Configurating Accelerometer */
	writeConfig = FS_ACC_4G;
	ret = HAL_I2C_Mem_Write(&hi2c1, (DEVICE_ADRESS << 1) + 0, REG_CONFIG_ACC, 1, &writeConfig, 1, 100);
	if(ret == HAL_OK)
	{
		strncpy(message, "Accelerometer configured successfully\r\n", sizeof(message));
	}
	else
	{
		strncpy(message, "Error while configuring accelerometer\r\n", sizeof(message));
	}
	HAL_UART_Transmit(&huart2, message, strlen(message), 50);
	/* Exiting from sleep mode */
	writeConfig = 0;
	ret = HAL_I2C_Mem_Write(&hi2c1, (DEVICE_ADRESS << 1) + 0, REG_PWR_CTRL, 1, &writeConfig, 1, 100);
	if(ret == HAL_OK)
	{
		strncpy(message, "Sleep mode disabled\r\n", sizeof(message));
	}
	else
	{
		strncpy(message, "Error while exiting from sleep mode\r\n", sizeof(message));
	}
	HAL_UART_Transmit(&huart2, message, strlen(message), 50);
}

int MPU9250_Gyro_ReadX()
{
	uint8_t data[2];
	int16_t xGyro;
	HAL_I2C_Mem_Read(&hi2c1, (DEVICE_ADRESS << 1) + 1, REG_GYRO_DATA_X, 1, data, 2, 100);
	xGyro = ((int16_t)data[0] << 8) + data[1];

	return xGyro;
}

int MPU9250_Gyro_ReadY()
{
	uint8_t data[2];
	int16_t yGyro;
	HAL_I2C_Mem_Read(&hi2c1, (DEVICE_ADRESS << 1) + 1, REG_GYRO_DATA_Y, 1, data, 2, 100);
	yGyro = ((int16_t)data[0] << 8) + data[1];

	return yGyro;
}

int MPU9250_Gyro_ReadZ()
{
	uint8_t data[2];
	int16_t zGyro;
	HAL_I2C_Mem_Read(&hi2c1, (DEVICE_ADRESS << 1) + 1, REG_GYRO_DATA_Z, 1, data, 2, 100);
	zGyro = ((int16_t)data[0] << 8) + data[1];

	return zGyro;
}

int MPU9250_Acc_ReadX()
{
	uint8_t data[2];
	int16_t xAcc;
	HAL_I2C_Mem_Read(&hi2c1, (DEVICE_ADRESS << 1) + 1, REG_ACC_DATA_X, 1, data, 2, 100);
	xAcc = ((int16_t)data[0] << 8) + data[1];

	return xAcc;
}

int MPU9250_Acc_ReadY()
{
	uint8_t data[2];
	int16_t yAcc;
	HAL_I2C_Mem_Read(&hi2c1, (DEVICE_ADRESS << 1) + 1, REG_ACC_DATA_Y, 1, data, 2, 100);
	yAcc = ((int16_t)data[0] << 8) + data[1];

	return yAcc;
}

