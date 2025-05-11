/*
 * MPU9250.h
 *
 *  Created on: May 10, 2025
 *      Author: Nicolas Acker
 *
 *  The periphepals register may change depending on the MPU version.
 *  SWV needs to be enabled if you want the debug message.
 */

#ifndef INC_MPU9250_H_
#define INC_MPU9250_H_

#define DEVICE_ADRESS 0b1101000

#define FS_GYRO_250   0b00000000
#define FS_GYRO_500   0b00001000
#define FS_GYRO_1000  0b00010000
#define FS_GYRO_2000  0b00011000

#define FS_ACC_2G     0b00000000
#define FS_ACC_4G     0b00001000
#define FS_ACC_8G     0b00010000
#define FS_ACC_16G    0b00011000

#define REG_CONFIG_GYRO 27
#define REG_CONFIG_ACC  28
#define REG_PWR_CTRL    107
#define REG_DATA_X      59
#define REG_DATA_Y      61
#define REG_DATA_Z		63

void MPU9250_Init();
float MPU9250_ReadX();
float MPU9250_ReadY();

#endif /* INC_MPU9250_H_ */
