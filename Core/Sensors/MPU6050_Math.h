/*
 * MPU6050_Math.h
 *
 *  Created on: Mar 11, 2025
 *      Author: esenk
 */

#ifndef SENSORS_MPU6050_MATH_H_
#define SENSORS_MPU6050_MATH_H_

#define MPU6050_2G_LSB_VALUE (16384)
#define MPU6050_4G_LSB_VALUE (8192)
#define MPU6050_8G_LSB_VALUE (4096)
#define MPU6050_16G_LSB_VALUE (2048)

void MPU6050_MATH_Calculate_mG_Value(MPU6050_Sensor_T *handle);
uint16_t MPU6050_MATH_Get_LSB_Value(MPU6050_Sensor_T *handle);
#endif /* SENSORS_MPU6050_MATH_H_ */
