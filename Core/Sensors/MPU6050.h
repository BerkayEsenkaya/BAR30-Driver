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

#define MPU6050_REGISTER_SAMPLERATE_DIV (0x19)
#define MPU6050_REGISTER_CONFIG (0x1A)
#define MPU6050_REGISTER_GYRO_CONFIG (0x1B)
#define MPU6050_REGISTER_ACCEL_CONFIG (0x1C)
#define MPU6050_REGISTER_FIFO_ENABLE (0x23)
#define MPU6050_REGISTER_INTERRUPT_PIN_CONFIG (0x37)
#define MPU6050_REGISTER_INTERRUPT_ENABLE (0x38)
#define MPU6050_REGISTER_INTERRUPT_STATUS (0x3A)
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
#define MPU6050_REGISTER_FIFO_COUNT_H (0x72)
#define MPU6050_REGISTER_FIFO_COUNT_L (0x73)
#define MPU6050_REGISTER_FIFO_READ (0x74)
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

#define MPU6050_DATA_LP_WU_FREQUENCY_1p2 (0x00)
#define MPU6050_DATA_LP_WU_FREQUENCY_5 (0x01<<6)
#define MPU6050_DATA_LP_WU_FREQUENCY_20 (0x02<<6)
#define MPU6050_DATA_LP_WU_FREQUENCY_40 (0x03<<6)
#define MPU6050_DATA_LP_ACCEL_AXIS_X_GO_STANDBY (0x01<<5)
#define MPU6050_DATA_LP_ACCEL_AXIS_Y_GO_STANDBY (0x01<<4)
#define MPU6050_DATA_LP_ACCEL_AXIS_Z_GO_STANDBY (0x01<<3)
#define MPU6050_DATA_LP_GYRO_AXIS_X_GO_STANDBY (0x01<<2)
#define MPU6050_DATA_LP_GYRO_AXIS_Y_GO_STANDBY (0x01<<1)
#define MPU6050_DATA_LP_GYRO_AXIS_Z_GO_STANDBY (0x01)

#define MPU6050_DATA_INT_OTO_CLEAR (0x01<<4)
#define MPU6050_DATA_INT_LATCH_DISABLE (0x00<<5)
#define MPU6050_DATA_INT_PUSHPULL (0x00<<6)
#define MPU6050_DATA_INT_OPENDRAIN (0x01<<6)
#define MPU6050_DATA_INT_LEVEL_ACTIVE_LOW (0x00<<7)
#define MPU6050_DATA_INT_LEVEL_ACTIVE_HIGH (0x01<<7)

#define MPU6050_DATA_INT_DATA_RDY_ENABLE (0x01)

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
	int16_t GYRO_Axis_X_Filtered;
	int16_t GYRO_Axis_Y_Filtered;
	int16_t GYRO_Axis_Z_Filtered;
}MPU6050_AvarageFilteredValue;

typedef struct{
	int16_t ACCEL_Axis_X_mG;
	int16_t ACCEL_Axis_Y_mG;
	int16_t ACCEL_Axis_Z_mG;

	int16_t GYRO_Axis_X_mDDS;
	int16_t GYRO_Axis_Y_mDDS;
	int16_t GYRO_Axis_Z_mDDS;
}MPU6050_G_Values_T;

typedef struct{
	volatile uint8_t dataReadyFlag;
	MPU6050_DeviceParam_T devParam;
	MPU6050_Config_Registers_T RegGroup_Config;
	volatile MPU6050_Data_Registers_T RegGroup_Data;
	volatile MPU6050_AvarageFilteredValue FilteredValues;
	volatile MPU6050_G_Values_T CalculatedValues;
}MPU6050_Sensor_T;

extern MPU6050_Sensor_T MPU6050_1;

MPU6050_ReturnTypeDef_T MPU6050_DeviceReset(MPU6050_Sensor_T *handle);
MPU6050_ReturnTypeDef_T MPU6050_DeviceSleep(MPU6050_Sensor_T *handle);
MPU6050_ReturnTypeDef_T MPU6050_DeviceModeLowPower(MPU6050_Sensor_T *handle);
MPU6050_ReturnTypeDef_T MPU6050_Init(MPU6050_Sensor_T *handle, uint8_t I2C_No, uint8_t DevAddress);
MPU6050_ReturnTypeDef_T MP6050_Get_WhoIAm_Data(MPU6050_Sensor_T *handle);
MPU6050_ReturnTypeDef_T MPU6050_Set_SampleRateDivider(MPU6050_Sensor_T *handle, uint8_t divider);
MPU6050_ReturnTypeDef_T MPU6050_Set_ConfigRegister(MPU6050_Sensor_T *handle, uint8_t sampleRate, uint8_t ExtSyncSet);
MPU6050_ReturnTypeDef_T MPU6050_Set_GYROConfigRegister(MPU6050_Sensor_T *handle, uint8_t scaleRange, uint8_t STaxisEnabled);
MPU6050_ReturnTypeDef_T MPU6050_Set_ACCELConfigRegister(MPU6050_Sensor_T *handle, uint8_t scaleRange, uint8_t STaxisEnabled);
MPU6050_ReturnTypeDef_T MPU6050_Select_FIFO_Members(MPU6050_Sensor_T *handle, uint8_t members);
MPU6050_ReturnTypeDef_T MPU6050_Read_ACCEL_Data(MPU6050_Sensor_T *handle);
MPU6050_ReturnTypeDef_T MPU6050_Read_GYRO_Data(MPU6050_Sensor_T *handle);
MPU6050_ReturnTypeDef_T MPU6050_Interrupt_Pin_Config(MPU6050_Sensor_T *handle, uint8_t data);
MPU6050_ReturnTypeDef_T MPU6050_Interrupt_Config(MPU6050_Sensor_T *handle, uint8_t data);
MPU6050_ReturnTypeDef_T MPU6050_Config_LowPowerMode(MPU6050_Sensor_T *handle, uint8_t LowPowerWakeUpFrequency, uint8_t ShutdownAxises);
MPU6050_ReturnTypeDef_T MPU6050_Write(MPU6050_Sensor_T *handle, uint8_t Register, uint8_t Data);
MPU6050_ReturnTypeDef_T MPU6050_Read(MPU6050_Sensor_T *handle, uint8_t Register, uint8_t *RxBuff);
MPU6050_ReturnTypeDef_T MPU6050_MultiRead(MPU6050_Sensor_T *handle, uint8_t *TxBuff, uint8_t *RxBuff, uint8_t RxLenght);
