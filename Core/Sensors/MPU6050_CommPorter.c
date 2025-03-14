/*
 * MPU6050_CommPorter.c
 *
 *  Created on: Mar 10, 2025
 *      Author: esenk
 */

#include "I2C.h"

uint8_t MPU6050_SendReceive(uint8_t I2CNo, uint8_t DevAddress, uint8_t *txBuff, uint8_t txLenght, uint8_t *rxBuff, uint8_t rxLenght){
	HAL_Delay(1);
	return I2C_ReadWrite_DMA(I2CNo, DevAddress, txBuff, txLenght, rxBuff, rxLenght);
}
/*
itoa(MPU6050_1.CalculatedValues.ACCEL_Axis_X_mG, bufferX, 10);
itoa(MPU6050_1.CalculatedValues.ACCEL_Axis_Y_mG, bufferY, 10);
itoa(MPU6050_1.CalculatedValues.ACCEL_Axis_Z_mG, bufferZ, 10);
sprintf(AccelBuffer, "ACC X : %06s ACC Y : %06s  ACC Z : %06s\r\n ", bufferX, bufferY, bufferZ);
*/
