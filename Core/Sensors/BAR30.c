/**
 * \file BAR30.c
 * \author Berkay Esenkaya (BAUROV Software Team)
 * \brief BAR30 sensor control functions
 * \date 24.02.2025
 *
 */

#include <stdint.h>
#include "BAR30.h"
#include "BAR30_CommPorter.h"
#include "main.h"

BAR30_Sensor_T BAR30_1, BAR30_2, BAR30_3;

/** Brief description which ends at this dot. Details follow
 *  here.
 */
BAR30_ReturnTypeDef_T BAR30_Init(BAR30_Sensor_T *handle, uint8_t i2cNo, uint8_t devI2CAddress){
	handle->devParam.I2C_No = i2cNo;
	handle->devParam.TxDevAdress = devI2CAddress;
	handle->devParam.RxDevAdress = (devI2CAddress<<1) | (0x01);
	return BAR30_OK;
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
BAR30_ReturnTypeDef_T BAR30_Reset(BAR30_Sensor_T *handle){
//	return BAR30_Write(handle, BAR30_COMMAND_RESET);
	uint8_t buff[1],res;
	buff[0] = BAR30_COMMAND_RESET;
	res = HAL_I2C_Master_Transmit(&hi2c2,(0x76<<1), buff, 2, 300);
//	HAL_I2C_Mem_Write(&hi2c2, 0x76, MemAddress, MemAddSize, pData, Size, Timeout);
	if(!res)
		return BAR30_OK;
	else
		return BAR30_ERROR;
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
BAR30_ReturnTypeDef_T BAR30_StartPressureConversion(BAR30_Sensor_T *handle){
	return BAR30_Write(handle, BAR30_COMMAND_START_PRESSURE_CONVERT_WITH_OSR_1024);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
BAR30_ReturnTypeDef_T BAR30_ReadPressure(BAR30_Sensor_T *handle){
	uint8_t RxBuff[2];
	if(!BAR30_Read(handle, BAR30_COMAND_ADC_READ, RxBuff))
		return RxBuff[0] | (RxBuff[1]<<8);
	else
		return BAR30_ERROR;
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
BAR30_ReturnTypeDef_T BAR30_Get_AllPromData(BAR30_Sensor_T *handle){
	BAR30_ReturnTypeDef_T res = 0;
	uint8_t RxBuff[2];
	uint8_t buff[1];
	buff[0] = BAR30_COMAND_PROM_READ_1;
	HAL_I2C_Mem_Read(&hi2c2, 0x76<<1, BAR30_COMAND_PROM_READ_1,I2C_MEMADD_SIZE_8BIT , RxBuff, 2, 100);
	handle->PromData[0] = RxBuff[1] | (RxBuff[0]<<8);
/*	res += BAR30_Read(handle, BAR30_COMAND_PROM_READ_1, RxBuff);
	handle->PromData[0] = RxBuff[0] | (RxBuff[1]<<8);
	RxBuff[0] = 0;
	RxBuff[1] = 0;
	res += BAR30_Read(handle, BAR30_COMAND_PROM_READ_2, RxBuff);
	handle->PromData[1] = RxBuff[0] | (RxBuff[1]<<8);
	RxBuff[0] = 0;
	RxBuff[1] = 0;
	res += BAR30_Read(handle, BAR30_COMAND_PROM_READ_3, RxBuff);
	handle->PromData[2] = RxBuff[0] | (RxBuff[1]<<8);
	RxBuff[0] = 0;
	RxBuff[1] = 0;
	res += BAR30_Read(handle, BAR30_COMAND_PROM_READ_4, RxBuff);
	handle->PromData[3] = RxBuff[0] | (RxBuff[1]<<8);
	RxBuff[0] = 0;
	RxBuff[1] = 0;
	res += BAR30_Read(handle, BAR30_COMAND_PROM_READ_5, RxBuff);
	handle->PromData[4] = RxBuff[0] | (RxBuff[1]<<8);
	RxBuff[0] = 0;
	RxBuff[1] = 0;
	res += BAR30_Read(handle, BAR30_COMAND_PROM_READ_6, RxBuff);
	handle->PromData[5] = RxBuff[0] | (RxBuff[1]<<8);
	RxBuff[0] = 0;
	RxBuff[1] = 0;
	res += BAR30_Read(handle, BAR30_COMAND_PROM_READ_7, RxBuff);
	handle->PromData[6] = RxBuff[0] | (RxBuff[1]<<8);
	RxBuff[0] = 0;
	RxBuff[1] = 0;

	if(res)
		return BAR30_ERROR;
	else
		return BAR30_OK;*/
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
BAR30_ReturnTypeDef_T BAR30_Write(BAR30_Sensor_T *handle, uint8_t command){
	uint8_t TxBuff[1];
	TxBuff[0] = command;
	return BAR30_SendReceive(handle, TxBuff, 1, NULL, 0);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
BAR30_ReturnTypeDef_T BAR30_Read(BAR30_Sensor_T *handle, uint8_t command, uint8_t *buffer){
	uint8_t TxBuff[1];
	TxBuff[0] = command;
	return BAR30_SendReceive(handle, TxBuff, 1, buffer, 2);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
BAR30_ReturnTypeDef_T BAR30_SendReceive(BAR30_Sensor_T *handle, uint8_t *txBuff, uint8_t txLenght, uint8_t *rxBuff, uint8_t rxLenght){
	HAL_Delay(5);
	return BAR30_CommPorter_SendReceive(handle->devParam.I2C_No, handle->devParam.TxDevAdress, txBuff, txLenght, rxBuff, rxLenght);
}
