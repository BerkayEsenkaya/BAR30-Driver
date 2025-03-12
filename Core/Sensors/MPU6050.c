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
	return MPU6050_Write(handle, MPU6050_REGISTER_PWR_MGMT_1, MPU6050_DATA_DEVICE_RESET);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MPU6050_AllSignalPathReset(MPU6050_Sensor_T *handle){
	return MPU6050_Write(handle, MPU6050_REGISTER_SIGNAL_PATH_RESET, MPU6050_DATA_ALL_SIGNALPATH_RESET);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MPU6050_DeviceSleep(MPU6050_Sensor_T *handle){
	return MPU6050_Write(handle, MPU6050_REGISTER_PWR_MGMT_1, MPU6050_DATA_DEVICE_SLEEP);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MPU6050_DeviceStartCycle(MPU6050_Sensor_T *handle){
	return MPU6050_Write(handle, MPU6050_REGISTER_PWR_MGMT_1, MPU6050_DATA_DEVICE_CYCLE);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MPU6050_Init(MPU6050_Sensor_T *handle, uint8_t I2C_No, uint8_t DevAddress){
	handle->devParam.I2C_No = I2C_No;
	handle->devParam.DevAdress = DevAddress;
	while(MPU6050_DeviceReset(handle))
		HAL_Delay(1);
	HAL_Delay(10);
	MPU6050_AllSignalPathReset(handle);
    if(!MP6050_Get_WhoIAm_Data(handle)){
    	MPU6050_Set_ConfigRegister(handle, MPU6050_DATA_SAMPLERATE_184, 0);
		MPU6050_Set_GYROConfigRegister(handle, MPU6050_DATA_GYRO_SCALERANGE_250, 0);
		MPU6050_Set_ACCELConfigRegister(handle, MPU6050_DATA_ACCEL_SCALERANGE_2, 0); //MPU6050_DATA_ACCEL_ST_XAXIS_ENABLED | MPU6050_DATA_ACCEL_ST_YAXIS_ENABLED | MPU6050_DATA_ACCEL_ST_ZAXIS_ENABLED);
		HAL_Delay(10);
		MPU6050_DeviceStartCycle(handle);
		HAL_Delay(100);
		return MPU6050_OK;
    }
    return MPU6050_ERROR;
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MP6050_Get_WhoIAm_Data(MPU6050_Sensor_T *handle){
	uint8_t RxBuff[2];
	MPU6050_Read(handle, MPU6050_REGISTER_WHOIAM, RxBuff);
	if(RxBuff[0] == MPU6050_DATA_WHOIAM)
		return MPU6050_OK;
	return MPU6050_ERROR;
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MPU6050_Set_ConfigRegister(MPU6050_Sensor_T *handle, uint8_t sampleRate, uint8_t ExtSyncSet){
	handle->RegGroup_Config.ConfigRegister = sampleRate | ExtSyncSet;
	return MPU6050_Write(handle, MPU6050_REGISTER_CONFIG, handle->RegGroup_Config.ConfigRegister);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MPU6050_Set_GYROConfigRegister(MPU6050_Sensor_T *handle, uint8_t scaleRange, uint8_t STaxisEnabled){
	handle->RegGroup_Config.GYRO_ConfigRegister = scaleRange | STaxisEnabled;
	return MPU6050_Write(handle, MPU6050_REGISTER_GYRO_CONFIG, handle->RegGroup_Config.GYRO_ConfigRegister);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MPU6050_Set_ACCELConfigRegister(MPU6050_Sensor_T *handle, uint8_t scaleRange, uint8_t STaxisEnabled){
	handle->RegGroup_Config.ACCEL_ConfigRegister = scaleRange | STaxisEnabled;
	return MPU6050_Write(handle, MPU6050_REGISTER_ACCEL_CONFIG , handle->RegGroup_Config.ACCEL_ConfigRegister);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MPU6050_Read_ACCEL_Data(MPU6050_Sensor_T *handle){
//	uint8_t  Data[6];
//	if(MPU6050_MultiRead(handle, MPU6050_REGISTER_ACCEL_OUT_X_H, Data, 6))
//		return MPU6050_ERROR;
//	handle->RegGroup_Data.ACCEL_Axis_X_Data = (int16_t)((Data[0]<<8) | Data[1]);
//	handle->RegGroup_Data.ACCEL_Axis_Y_Data = (int16_t)((Data[2]<<8) | Data[3]);
//	handle->RegGroup_Data.ACCEL_Axis_Z_Data = (int16_t)((Data[4]<<8) | Data[5]);
//	return MPU6050_OK;
	uint8_t DataH[1], DataL[1] ;
	MPU6050_Read(handle, MPU6050_REGISTER_ACCEL_OUT_X_H, DataH);
	MPU6050_Read(handle, MPU6050_REGISTER_ACCEL_OUT_X_L, DataL);
	handle->RegGroup_Data.ACCEL_Axis_X_Data = (int16_t)((DataH[0]<<8) | DataL[0]);

	MPU6050_Read(handle, MPU6050_REGISTER_ACCEL_OUT_Y_H, DataH);
	MPU6050_Read(handle, MPU6050_REGISTER_ACCEL_OUT_Y_L, DataL);
	handle->RegGroup_Data.ACCEL_Axis_Y_Data = (int16_t)(DataH[0]<<8) | DataL[0];

	MPU6050_Read(handle, MPU6050_REGISTER_ACCEL_OUT_Z_H, DataH);
	MPU6050_Read(handle, MPU6050_REGISTER_ACCEL_OUT_Z_L, DataL);
	handle->RegGroup_Data.ACCEL_Axis_Z_Data = (int16_t)((DataH[0]<<8) | DataL[0]);
	return MPU6050_OK;
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MPU6050_Write(MPU6050_Sensor_T *handle, uint8_t Register, uint8_t Data){
	MPU6050_ReturnTypeDef_T res;
	uint8_t TxBuff[2];
	TxBuff[0] = Register;
	TxBuff[1] = Data;
	res = MPU6050_SendReceive(handle->devParam.I2C_No, handle->devParam.DevAdress, TxBuff, 2, 0, 0);
	if(res == MPU6050_OK)
		return MPU6050_OK;
	else
		return MPU6050_ERROR;
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MPU6050_Read(MPU6050_Sensor_T *handle, uint8_t Register, uint8_t *RxBuff){
	MPU6050_ReturnTypeDef_T res;
	uint8_t TxBuff[1];
	TxBuff[0] = Register;
	res = MPU6050_SendReceive(handle->devParam.I2C_No, handle->devParam.DevAdress, TxBuff, 1, RxBuff, 1);
	if(res == MPU6050_OK)
		return MPU6050_OK;
	else
		return MPU6050_ERROR;
}


/** Brief description which ends at this dot. Details follow
 *  here.
 */
MPU6050_ReturnTypeDef_T MPU6050_MultiRead(MPU6050_Sensor_T *handle, uint8_t *TxBuff, uint8_t *RxBuff, uint8_t RxLenght){
	MPU6050_ReturnTypeDef_T res;
	res = MPU6050_SendReceive(handle->devParam.I2C_No, handle->devParam.DevAdress, TxBuff, 1, RxBuff, RxLenght);
	if(res == MPU6050_OK)
		return MPU6050_OK;
	else
		return MPU6050_ERROR;
}
