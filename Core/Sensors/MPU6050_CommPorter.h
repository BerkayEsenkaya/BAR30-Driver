/*
 * MPU6050_CommPorter.h
 *
 *  Created on: Mar 10, 2025
 *      Author: esenk
 */

#ifndef SENSORS_MPU6050_COMMPORTER_H_
#define SENSORS_MPU6050_COMMPORTER_H_

uint8_t MPU6050_SendReceive(uint8_t I2CNo, uint8_t DevAddress, uint8_t *txBuff, uint8_t txLenght, uint8_t *rxBuff, uint8_t rxLenght);

#endif /* SENSORS_MPU6050_COMMPORTER_H_ */
