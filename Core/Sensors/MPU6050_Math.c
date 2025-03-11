/*
 * MPU6050_Math.c
 *
 *  Created on: Mar 11, 2025
 *      Author: esenk
 */
#include <stdint.h>
#include "MPU6050.h"

#define MPU6050_2G_LSB_VALUE (16384)

void MPU6050_Calculate_mG_Value(MPU6050_Sensor_T *handle){
	int64_t tempValue = (int64_t)(MPU6050_1.FilteredValues.ACCEL_Axis_X_Filtered*1000);
	handle->CalculatedValues.ACCEL_Axis_X_Mg = tempValue/MPU6050_2G_LSB_VALUE;
	tempValue = MPU6050_1.FilteredValues.ACCEL_Axis_Y_Filtered*1000;
	handle->CalculatedValues.ACCEL_Axis_Y_Mg = tempValue/MPU6050_2G_LSB_VALUE;
	tempValue = MPU6050_1.FilteredValues.ACCEL_Axis_Z_Filtered*1000;
	handle->CalculatedValues.ACCEL_Axis_Z_Mg = tempValue/MPU6050_2G_LSB_VALUE;
}
