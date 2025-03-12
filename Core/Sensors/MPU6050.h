/*
 * MPU6050.h
 *
 *  Created on: Mar 10, 2025
 *      Author: esenk
 */

#ifndef SENSORS_MPU6050_H_
#define SENSORS_MPU6050_H_
#endif /* SENSORS_MPU6050_H_ */

#define MPU6050_DEVICE_ADDRESS (0xD0)

#define MPU6050_REGISTER_CONFIG (0x1A)
#define MPU6050_REGISTER_GYRO_CONFIG (0x1B)
#define MPU6050_REGISTER_ACCEL_CONFIG (0x1C)
#define MPU6050_REGISTER_ACCEL_OUT_X_H (0x3B)
#define MPU6050_REGISTER_ACCEL_OUT_X_L (0x3C)
#define MPU6050_REGISTER_ACCEL_OUT_Y_H (0x3D)
#define MPU6050_REGISTER_ACCEL_OUT_Y_L (0x3E)
#define MPU6050_REGISTER_ACCEL_OUT_Z_H (0x3F)
#define MPU6050_REGISTER_ACCEL_OUT_Z_L (0x40)
#define MPU6050_REGISTER_TEMP_OUT_H (0x41)
#define MPU6050_REGISTER_TEMP_OUT_L (0x42)
#define MPU6050_REGISTER_GYRO_OUT_X_H (0x43)
#define MPU6050_REGISTER_GYRO_OUT_X_L (0x44)
#define MPU6050_REGISTER_GYRO_OUT_Y_H (0x45)
#define MPU6050_REGISTER_GYRO_OUT_Y_L (0x46)
#define MPU6050_REGISTER_GYRO_OUT_Z_H (0x47)
#define MPU6050_REGISTER_GYRO_OUT_Z_L (0x48)
#define MPU6050_REGISTER_SIGNAL_PATH_RESET (0x68)
#define MPU6050_REGISTER_PWR_MGMT_1 (0x6B)
#define MPU6050_REGISTER_PWR_MGMT_2 (0x6C)
#define MPU6050_REGISTER_WHOIAM (0x75)

#define MPU6050_DATA_WHOIAM (0x68)

#define MPU6050_DATA_SAMPLERATE_260 (0x00)
#define MPU6050_DATA_SAMPLERATE_184 (0x01)
#define MPU6050_DATA_SAMPLERATE_94  (0x02)
#define MPU6050_DATA_SAMPLERATE_44  (0x03)
#define MPU6050_DATA_SAMPLERATE_21  (0x04)
#define MPU6050_DATA_SAMPLERATE_10  (0x05)
#define MPU6050_DATA_SAMPLERATE_5   (0x06)

#define MPU6050_DATA_GYRO_SCALERANGE_250 (0x00<<3)
#define MPU6050_DATA_GYRO_SCALERANGE_500 (0x01<<3)
#define MPU6050_DATA_GYRO_SCALERANGE_1000 (0x02<<3)
#define MPU6050_DATA_GYRO_SCALERANGE_2000 (0x03<<3)

#define MPU6050_DATA_GYRO_ST_XAXIS_ENABLED (0x01<<7)
#define MPU6050_DATA_GYRO_ST_YAXIS_ENABLED (0x01<<6)
#define MPU6050_DATA_GYRO_ST_ZAXIS_ENABLED (0x01<<5)

#define MPU6050_DATA_ACCEL_SCALERANGE_2  (0x00<<3)
#define MPU6050_DATA_ACCEL_SCALERANGE_4  (0x01<<3)
#define MPU6050_DATA_ACCEL_SCALERANGE_8  (0x02<<3)
#define MPU6050_DATA_ACCEL_SCALERANGE_16 (0x03<<3)

#define MPU6050_DATA_ACCEL_ST_XAXIS_ENABLED (0x01<<7)
#define MPU6050_DATA_ACCEL_ST_YAXIS_ENABLED (0x01<<6)
#define MPU6050_DATA_ACCEL_ST_ZAXIS_ENABLED (0x01<<5)

#define MPU6050_DATA_DEVICE_RESET (0x01<<7)
#define MPU6050_DATA_DEVICE_SLEEP (0x01<<6)
#define MPU6050_DATA_DEVICE_CYCLE (0x01<<5)
#define MPU6050_DATA_TEMP_DISABLE (0x01<<3)
#define MPU6050_DATA_CLK_INTERNAL (0x00)

#define MPU6050_DATA_ALL_SIGNALPATH_RESET (0x07)

typedef enum{
	MPU6050_OK,
	MPU6050_ERROR,
}MPU6050_ReturnTypeDef_T;

typedef struct{
	uint8_t I2C_No;
	uint8_t DevAdress;
}MPU6050_DeviceParam_T;

typedef struct{
	uint8_t ConfigRegister;
	uint8_t GYRO_ConfigRegister;
	uint8_t ACCEL_ConfigRegister;
}MPU6050_Config_Registers_T;

typedef struct{
	int16_t ACCEL_Axis_X_Data;
	int16_t ACCEL_Axis_Y_Data;
	int16_t ACCEL_Axis_Z_Data;

	int16_t GYRO_Axis_X_Data;
	int16_t GYRO_Axis_Y_Data;
	int16_t GYRO_Axis_Z_Data;
}MPU6050_Data_Registers_T;

typedef struct{
	int16_t ACCEL_Axis_X_Filtered;
	int16_t ACCEL_Axis_Y_Filtered;
	int16_t ACCEL_Axis_Z_Filtered;
}MPU6050_AvarageFilteredValue;

typedef struct{
	int16_t ACCEL_Axis_X_Mg;
	int16_t ACCEL_Axis_Y_Mg;
	int16_t ACCEL_Axis_Z_Mg;
}MPU6050_G_Values_T;

typedef struct{
	MPU6050_DeviceParam_T devParam;
	MPU6050_Config_Registers_T RegGroup_Config;
	MPU6050_Data_Registers_T RegGroup_Data;
	MPU6050_AvarageFilteredValue FilteredValues;
	MPU6050_G_Values_T CalculatedValues;
}MPU6050_Sensor_T;

extern MPU6050_Sensor_T MPU6050_1;

MPU6050_ReturnTypeDef_T MPU6050_DeviceReset(MPU6050_Sensor_T *handle);
MPU6050_ReturnTypeDef_T MPU6050_DeviceSleep(MPU6050_Sensor_T *handle);
MPU6050_ReturnTypeDef_T MPU6050_DeviceStartCycle(MPU6050_Sensor_T *handle);
MPU6050_ReturnTypeDef_T MPU6050_Init(MPU6050_Sensor_T *handle, uint8_t I2C_No, uint8_t DevAddress);
MPU6050_ReturnTypeDef_T MP6050_Get_WhoIAm_Data(MPU6050_Sensor_T *handle);
MPU6050_ReturnTypeDef_T MPU6050_Set_ConfigRegister(MPU6050_Sensor_T *handle, uint8_t sampleRate, uint8_t ExtSyncSet);
MPU6050_ReturnTypeDef_T MPU6050_Set_GYROConfigRegister(MPU6050_Sensor_T *handle, uint8_t scaleRange, uint8_t STaxisEnabled);
MPU6050_ReturnTypeDef_T MPU6050_Set_ACCELConfigRegister(MPU6050_Sensor_T *handle, uint8_t scaleRange, uint8_t STaxisEnabled);
MPU6050_ReturnTypeDef_T MPU6050_Read_ACCEL_Data(MPU6050_Sensor_T *handle);
MPU6050_ReturnTypeDef_T MPU6050_Write(MPU6050_Sensor_T *handle, uint8_t Register, uint8_t Data);
MPU6050_ReturnTypeDef_T MPU6050_Read(MPU6050_Sensor_T *handle, uint8_t Register, uint8_t *RxBuff);
MPU6050_ReturnTypeDef_T MPU6050_MultiRead(MPU6050_Sensor_T *handle, uint8_t *TxBuff, uint8_t *RxBuff, uint8_t RxLenght);
