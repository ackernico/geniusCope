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

extern I2C_HandleTypeDef hi2c1;

void MPU9250_Init()
{
	uint8_t writeConfig = FS_GYRO_500;

	/* Verifying if the device is ready */
	HAL_StatusTypeDef ret = HAL_I2C_IsDeviceReady(&hi2c1, (DEVICE_ADRESS << 1) + 0, 1, 100);
	if(ret == HAL_OK)
	{
		printf("Device is ready to connect\n");
	}
	else
	{
		printf("Device is not ready to connect\n");
	}

	/* Configurating Gyroscope */
	ret = HAL_I2C_Mem_Write(&hi2c1, (DEVICE_ADRESS << 1) + 0, REG_CONFIG_GYRO, 1, &writeConfig, 1, 100);
	if(ret == HAL_OK)
	{
		printf("Gyroscope configured successfully\n");
	}
	else
	{
		printf("Error while configuring gyroscope\n");
	}

	/* Configurating Accelerometer */
	writeConfig = FS_ACC_4G;
	ret = HAL_I2C_Mem_Write(&hi2c1, (DEVICE_ADRESS << 1) + 0, REG_CONFIG_ACC, 1, &writeConfig, 1, 100);
	if(ret == HAL_OK)
	{
		printf("Accelerometer configured successfully\n");
	}
	else
	{
		printf("Error while configuring accelerometer\n");
	}
	/* Exiting from sleep mode */
	writeConfig = 0;
	ret = HAL_I2C_Mem_Write(&hi2c1, (DEVICE_ADRESS << 1) + 0, REG_PWR_CTRL, 1, &writeConfig, 1, 100);
	if(ret == HAL_OK)
	{
		printf("Sleep mode disabled\n");
	}
	else
	{
		printf("Error while exiting from sleep mode\n");
	}
}

float MPU9250_ReadX()
{
	uint8_t data[2];
	int16_t xAcc;
	HAL_I2C_Mem_Read(&hi2c1, (DEVICE_ADRESS << 1) + 1, REG_DATA_X, 1, data, 2, 100);
	xAcc = ((int16_t)data[0] << 8) + data[1];

	return xAcc;
}

float MPU9250_ReadY()
{
	uint8_t data[2];
	int16_t yAcc;
	HAL_I2C_Mem_Read(&hi2c1, (DEVICE_ADRESS << 1) + 1, REG_DATA_Y, 1, data, 2, 100);
	yAcc = ((int16_t)data[0] << 8) + data[1];

	return yAcc;
}

