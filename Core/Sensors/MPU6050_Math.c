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
void MPU6050_MATH_Calculate_mG_Value(MPU6050_Sensor_T *handle){
	int64_t tempValue;
	uint16_t MPU_Accel_LSB_Value = MPU6050_MATH_Get_LSB_Value(handle);

	tempValue = (int64_t)(MPU6050_1.FilteredValues.ACCEL_Axis_X_Filtered*1000);
	handle->CalculatedValues.ACCEL_Axis_X_Mg = tempValue / MPU_Accel_LSB_Value;

	tempValue = MPU6050_1.FilteredValues.ACCEL_Axis_Y_Filtered*1000;
	handle->CalculatedValues.ACCEL_Axis_Y_Mg = tempValue / MPU_Accel_LSB_Value;

	tempValue = MPU6050_1.FilteredValues.ACCEL_Axis_Z_Filtered*1000;
	handle->CalculatedValues.ACCEL_Axis_Z_Mg = tempValue / MPU_Accel_LSB_Value;
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
uint16_t MPU6050_MATH_Get_LSB_Value(MPU6050_Sensor_T *handle){
	switch(handle->RegGroup_Config.ACCEL_ConfigRegister>>3){
		case  MPU6050_DATA_ACCEL_SCALERANGE_2 : return MPU6050_2G_LSB_VALUE ;
		break;
		case  MPU6050_DATA_ACCEL_SCALERANGE_4 : return MPU6050_4G_LSB_VALUE ;
		break;
		case  MPU6050_DATA_ACCEL_SCALERANGE_8 : return MPU6050_8G_LSB_VALUE ;
		break;
		case  MPU6050_DATA_ACCEL_SCALERANGE_16 :return MPU6050_16G_LSB_VALUE ;
		break;
		default : return 0;
	}
}
