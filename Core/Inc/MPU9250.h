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
/*Device adress*/
#define DEVICE_ADRESS 0b1101000
/*Gyroscope multiples ranges*/
#define FS_GYRO_250   0b00000000
#define FS_GYRO_500   0b00001000
#define FS_GYRO_1000  0b00010000
#define FS_GYRO_2000  0b00011000
/*Accelerometer multiples ranges*/
#define FS_ACC_2G     0b00000000
#define FS_ACC_4G     0b00001000
#define FS_ACC_8G     0b00010000
#define FS_ACC_16G    0b00011000
/*Peripherals registers*/
#define REG_CONFIG_GYRO  27
#define REG_CONFIG_ACC   28
#define REG_PWR_CTRL     107
#define REG_GYRO_DATA_X  59
#define REG_GYRO_DATA_Y  61
#define REG_GYRO_DATA_Z	 63
#define REG_ACC_DATA_X   67
#define REG_ACC_DATA_Y	 69

/** MPU9250_Init() - Initiates MPU9250 peripherals
 *  @brief Initiate gyroscope, accelerometer, and gets out of the sleep mode
 *  @param None
 *  @ret None
 */
void MPU9250_Init();
/** MPU9250_Gyro_ReadX(); - Reads the X axis of the gyroscope
 *  @brief Reads the X axis of the gyroscope
 *  @param None
 *  @ret X axis inclination
 */
int MPU9250_Gyro_ReadX();
/** MPU9250_Gyro_ReadY(); - Reads the Y axis of the gyroscope
 *  @brief Reads the Y axis of the gyroscope
 *  @param None
 *  @ret Y axis inclination
 */
int MPU9250_Gyro_ReadY();
/** MPU9250_Acc_ReadX(); - Reads the X axis of the accelerometer
 *  @brief Reads the X axis of the gyroscope
 *  @param None
 *  @ret X axis acceleration
 */
int MPU9250_Acc_ReadX();
/** MPU9250_Acc_ReadY(); - Reads the Y axis of the accelerometer
 *  @brief Reads the Y axis of the gyroscope
 *  @param None
 *  @ret Y axis acceleration
 */
int MPU9250_Acc_ReadY();

#endif /* INC_MPU9250_H_ */
