/*
 * MPU6050_CommPorter.c
 *
 *  Created on: Mar 10, 2025
 *      Author: esenk
 */

#include "I2C.h"

uint8_t MPU6050_SendReceive(uint8_t I2CNo, uint8_t DevAddress, uint8_t *txBuff, uint8_t txLenght, uint8_t *rxBuff, uint8_t rxLenght){
	HAL_Delay(5);
	return I2C_ReadWrite_DMA(I2CNo, DevAddress, txBuff, txLenght, rxBuff, rxLenght);
}
