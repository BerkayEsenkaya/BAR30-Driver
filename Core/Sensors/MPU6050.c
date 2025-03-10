/**
 * \file MPU6050.c
 * \author Berkay Esenkaya (BAUROV Software Team)
 * \brief MPU6050 sensor control functions
 * \date 10.03.2025
 *
 */
#include <stdint.h>
#include "MPU6050.h"
#include "MPU6050_CommPorter.h"
MPU6050_Sensor_T MPU6050_1;

MPU6050_ReturnTypeDef_T MPU6050_Init(MPU6050_Sensor_T *handle, uint8_t I2C_No, uint8_t DevAddress){
	uint8_t TxBuff[1], RxBuff[2];
	TxBuff[0] = 0x75;
	handle->devParam.I2C_No = I2C_No;
	handle->devParam.DevAdress = DevAddress;
	MPU6050_Read(handle, TxBuff, RxBuff);
	HAL_Delay(10);
	if(RxBuff[0] == 0x68)
		return MPU6050_OK;
	return MPU6050_ERROR;
}

MPU6050_ReturnTypeDef_T MPU6050_Write(MPU6050_Sensor_T *handle, uint8_t *TxBuff){
	return MPU6050_SendReceive(handle->devParam.I2C_No, handle->devParam.DevAdress, TxBuff, 1, 0, 0);
}

MPU6050_ReturnTypeDef_T MPU6050_Read(MPU6050_Sensor_T *handle, uint8_t *TxBuff, uint8_t *RxBuff){
	return MPU6050_SendReceive(handle->devParam.I2C_No, handle->devParam.DevAdress, TxBuff, 1, RxBuff, 1);
}
