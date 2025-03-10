/*
 * MPU6050.h
 *
 *  Created on: Mar 10, 2025
 *      Author: esenk
 */

#ifndef SENSORS_MPU6050_H_
#define SENSORS_MPU6050_H_

typedef enum{
	MPU6050_OK,
	MPU6050_ERROR,
}MPU6050_ReturnTypeDef_T;

typedef struct{
	uint8_t I2C_No;
	uint8_t DevAdress;
}MPU6050_DeviceParam_T;

typedef struct{
	MPU6050_DeviceParam_T devParam;

}MPU6050_Sensor_T;

extern MPU6050_Sensor_T MPU6050_1;

MPU6050_ReturnTypeDef_T MPU6050_Init(MPU6050_Sensor_T *handle, uint8_t I2C_No, uint8_t DevAddress);
MPU6050_ReturnTypeDef_T MPU6050_Write(MPU6050_Sensor_T *handle, uint8_t *TxBuff);
MPU6050_ReturnTypeDef_T MPU6050_Read(MPU6050_Sensor_T *handle, uint8_t *TxBuff, uint8_t *RxBuff);
#endif /* SENSORS_MPU6050_H_ */
