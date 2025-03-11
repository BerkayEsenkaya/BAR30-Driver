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
#include "main.h"

MPU6050_Sensor_T MPU6050_1;

/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MPU6050_DeviceReset(MPU6050_Sensor_T *handle){
	uint8_t TxBuff[2];
	TxBuff[0] = MPU6050_REGISTER_PWR_MGMT_1;
	TxBuff[1] = MPU6050_DATA_DEVICE_RESET;
	return MPU6050_Write(handle, TxBuff);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MPU6050_AllSignalPathReset(MPU6050_Sensor_T *handle){
	uint8_t TxBuff[2];
	TxBuff[0] = MPU6050_REGISTER_SIGNAL_PATH_RESET;
	TxBuff[1] = MPU6050_DATA_ALL_SIGMALPATH_RESET;
	return MPU6050_Write(handle, TxBuff);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MPU6050_DeviceSleep(MPU6050_Sensor_T *handle){
	uint8_t TxBuff[2];
	TxBuff[0] = MPU6050_REGISTER_PWR_MGMT_1;
	TxBuff[1] = MPU6050_DATA_DEVICE_SLEEP;
	return MPU6050_Write(handle, TxBuff);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MPU6050_DeviceStartCycle(MPU6050_Sensor_T *handle){
	uint8_t TxBuff[2];
	TxBuff[0] = MPU6050_REGISTER_PWR_MGMT_1;
	TxBuff[1] = MPU6050_DATA_DEVICE_CYCLE;
	return MPU6050_Write(handle, TxBuff);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MPU6050_Init(MPU6050_Sensor_T *handle, uint8_t I2C_No, uint8_t DevAddress){
	handle->devParam.I2C_No = I2C_No;
	handle->devParam.DevAdress = DevAddress;
	MPU6050_DeviceReset(handle);
	HAL_Delay(100);
	MPU6050_AllSignalPathReset(handle);
    if(!MP6050_Get_WhoIAm_Data(handle)){
    	MPU6050_Set_ConfigRegister(handle, MPU6050_DATA_SAMPLERATE_260, 0);
		MPU6050_Set_GYROConfigRegister(handle, MPU6050_DATA_GYRO_SCALERANGE_250, 0);
		MPU6050_Set_ACCELConfigRegister(handle, MPU6050_DATA_ACCEL_SCALERANGE_2, 0); //MPU6050_DATA_ACCEL_ST_XAXIS_ENABLED | MPU6050_DATA_ACCEL_ST_YAXIS_ENABLED | MPU6050_DATA_ACCEL_ST_ZAXIS_ENABLED);
		HAL_Delay(100);
		MPU6050_DeviceStartCycle(handle);
		HAL_Delay(100);
    }
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MP6050_Get_WhoIAm_Data(MPU6050_Sensor_T *handle){
	uint8_t TxBuff[1], RxBuff[2];
	TxBuff[0] = MPU6050_REGISTER_WHOIAM;
	MPU6050_Read(handle, TxBuff, RxBuff);
	if(RxBuff[0] == MPU6050_DATA_WHOIAM)
		return MPU6050_OK;
	return MPU6050_ERROR;
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MPU6050_Set_ConfigRegister(MPU6050_Sensor_T *handle, uint8_t sampleRate, uint8_t ExtSyncSet){
	uint8_t TxBuff[2], RxBuff[1];
	TxBuff[0] = MPU6050_REGISTER_CONFIG;
	handle->RegGroup_Config.ConfigRegister = sampleRate | ExtSyncSet;
	TxBuff[1] = handle->RegGroup_Config.ConfigRegister;
	MPU6050_Write(handle, TxBuff);
	HAL_Delay(50);
	TxBuff[1] = 0;
	return MPU6050_Read(handle, TxBuff, RxBuff);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MPU6050_Set_GYROConfigRegister(MPU6050_Sensor_T *handle, uint8_t scaleRange, uint8_t STaxisEnabled){
	uint8_t TxBuff[2];
	TxBuff[0] = MPU6050_REGISTER_GYRO_CONFIG;
	handle->RegGroup_Config.GYRO_ConfigRegister = scaleRange | STaxisEnabled;
	TxBuff[1] = handle->RegGroup_Config.GYRO_ConfigRegister;
	return MPU6050_Write(handle, TxBuff);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MPU6050_Set_ACCELConfigRegister(MPU6050_Sensor_T *handle, uint8_t scaleRange, uint8_t STaxisEnabled){
	uint8_t TxBuff[2];
	TxBuff[0] = MPU6050_REGISTER_ACCEL_CONFIG;
	handle->RegGroup_Config.ACCEL_ConfigRegister = scaleRange | STaxisEnabled;
	TxBuff[1] = handle->RegGroup_Config.ACCEL_ConfigRegister;
	return MPU6050_Write(handle, TxBuff);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MPU6050_Read_ACCEL_Data(MPU6050_Sensor_T *handle){
	uint8_t TxBuff[1], DataH[1], DataL[1] ;
	TxBuff[0] = MPU6050_REGISTER_ACCEL_OUT_X_H;
	MPU6050_Read(handle, TxBuff, DataH);
	TxBuff[0] = MPU6050_REGISTER_ACCEL_OUT_X_L;
	MPU6050_Read(handle, TxBuff, DataL);
	handle->RegGroup_Data.ACCEL_Axis_X_Data = (int16_t)((DataH[0]<<8) | DataL[0]);

	TxBuff[0] = MPU6050_REGISTER_ACCEL_OUT_Y_H;
	MPU6050_Read(handle, TxBuff, DataH);
	TxBuff[0] = MPU6050_REGISTER_ACCEL_OUT_Y_L;
	MPU6050_Read(handle, TxBuff, DataL);
	handle->RegGroup_Data.ACCEL_Axis_Y_Data = (int16_t)(DataH[0]<<8) | DataL[0];

	TxBuff[0] = MPU6050_REGISTER_ACCEL_OUT_Z_H;
	MPU6050_Read(handle, TxBuff, DataH);
	TxBuff[0] = MPU6050_REGISTER_ACCEL_OUT_Z_L;
	MPU6050_Read(handle, TxBuff, DataL);
	handle->RegGroup_Data.ACCEL_Axis_Z_Data = (int16_t)((DataH[0]<<8) | DataL[0]);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MPU6050_Write(MPU6050_Sensor_T *handle, uint8_t *TxBuff){
	MPU6050_ReturnTypeDef_T res;
	res = MPU6050_SendReceive(handle->devParam.I2C_No, handle->devParam.DevAdress, TxBuff, 2, 0, 0);
	if(res == MPU6050_OK)
		return MPU6050_OK;
	else
		return MPU6050_ERROR;
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MPU6050_Read(MPU6050_Sensor_T *handle, uint8_t *TxBuff, uint8_t *RxBuff){
	MPU6050_ReturnTypeDef_T res;
	res = MPU6050_SendReceive(handle->devParam.I2C_No, handle->devParam.DevAdress, TxBuff, 1, RxBuff, 1);
	if(res == MPU6050_OK)
		return MPU6050_OK;
	else
		return MPU6050_ERROR;
}
