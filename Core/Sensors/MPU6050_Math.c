/*
 * MPU6050_Math.c
 *
 *  Created on: Mar 11, 2025
 *      Author: esenk
 */
#include <stdint.h>
#include "MPU6050.h"
#include "MPU6050_Math.h"

/** Brief description which ends at this dot. Details follow
 *  here.
 */
void MPU6050_MATH_Calculate_ACCEL_mG_Value(MPU6050_Sensor_T *handle){
	int64_t tempValue;
	uint16_t MPU_Accel_LSB_Value = MPU6050_MATH_Get_ACCEL_LSB_Value(handle);

	tempValue = (int64_t)(MPU6050_1.FilteredValues.ACCEL_Axis_X_Filtered*1000);
	handle->CalculatedValues.ACCEL_Axis_X_mG = tempValue / MPU_Accel_LSB_Value;

	tempValue = (int64_t)(MPU6050_1.FilteredValues.ACCEL_Axis_Y_Filtered*1000);
	handle->CalculatedValues.ACCEL_Axis_Y_mG = tempValue / MPU_Accel_LSB_Value;

	tempValue = (int64_t)(MPU6050_1.FilteredValues.ACCEL_Axis_Z_Filtered*1000);
	handle->CalculatedValues.ACCEL_Axis_Z_mG = tempValue / MPU_Accel_LSB_Value;
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
uint16_t MPU6050_MATH_Get_ACCEL_LSB_Value(MPU6050_Sensor_T *handle){
	switch(handle->RegGroup_Config.ACCEL_ConfigRegister>>3){
		case  MPU6050_DATA_ACCEL_SCALERANGE_2 : return MPU6050_ACCEL_2G_LSB_VALUE ;
		break;
		case  MPU6050_DATA_ACCEL_SCALERANGE_4 : return MPU6050_ACCEL_4G_LSB_VALUE ;
		break;
		case  MPU6050_DATA_ACCEL_SCALERANGE_8 : return MPU6050_ACCEL_8G_LSB_VALUE ;
		break;
		case  MPU6050_DATA_ACCEL_SCALERANGE_16 :return MPU6050_ACCEL_16G_LSB_VALUE ;
		break;
		default : return 0;
	}
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
void MPU6050_MATH_Calculate_GYRO_mG_Value(MPU6050_Sensor_T *handle){
	int64_t tempValue;
	uint16_t MPU_Accel_LSB_Value = MPU6050_MATH_Get_GYRO_LSB_Value(handle);

	tempValue = (int64_t)(MPU6050_1.FilteredValues.GYRO_Axis_X_Filtered*100);
	handle->CalculatedValues.GYRO_Axis_X_mDDS = tempValue / MPU_Accel_LSB_Value;

	tempValue = (int64_t)(MPU6050_1.FilteredValues.GYRO_Axis_Y_Filtered*100);
	handle->CalculatedValues.GYRO_Axis_Y_mDDS = tempValue / MPU_Accel_LSB_Value;

	tempValue = (int64_t)(MPU6050_1.FilteredValues.GYRO_Axis_Z_Filtered*100);
	handle->CalculatedValues.GYRO_Axis_Z_mDDS = tempValue / MPU_Accel_LSB_Value;
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
uint16_t MPU6050_MATH_Get_GYRO_LSB_Value(MPU6050_Sensor_T *handle){
	switch(handle->RegGroup_Config.GYRO_ConfigRegister>>3){
		case  MPU6050_DATA_GYRO_SCALERANGE_250 : return MPU6050_GYRO_250DDS_LSB_VALUE ;
		break;
		case  MPU6050_DATA_GYRO_SCALERANGE_500 : return MPU6050_GYRO_500DDS_LSB_VALUE ;
		break;
		case  MPU6050_DATA_GYRO_SCALERANGE_1000 : return MPU6050_GYRO_1000DDS_LSB_VALUE ;
		break;
		case  MPU6050_DATA_GYRO_SCALERANGE_2000 :return MPU6050_GYRO_2000DDS_LSB_VALUE ;
		break;
		default : return 0;
	}
}
