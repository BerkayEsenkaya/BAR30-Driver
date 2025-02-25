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

BAR30_DeviceParam_T BAR30_1, BAR30_2, BAR30_3;

/** Brief description which ends at this dot. Details follow
 *  here.
 */
BAR30_ReturnTypeDef_T BAR30_Init(BAR30_DeviceParam_T *handle, uint8_t i2cNo, uint8_t devI2CAddress){
	handle->I2C_No = i2cNo;
	handle->TxDevAdress = devI2CAddress<<1;
	handle->RxDevAdress = (devI2CAddress<<1) | (0x01);
	return BAR30_OK;
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
BAR30_ReturnTypeDef_T BAR30_Reset(BAR30_DeviceParam_T *handle){
	return BAR30_Write(handle, BAR30_COMMAND_RESET);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
BAR30_ReturnTypeDef_T BAR30_StartPressureConversion(BAR30_DeviceParam_T *handle){
	return BAR30_Write(handle, BAR30_COMMAND_START_PRESSURE_CONVERT_WITH_OSR_1024);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
uint16_t BAR30_ReadPressure(BAR30_DeviceParam_T *handle){
	uint8_t RxBuff[2];
	if(!BAR30_Read(handle, BAR30_COMAND_ADC_READ, RxBuff))
		return RxBuff[0] | (RxBuff[0]<<8);
	else
		return BAR30_INCORRECTED_DATA;
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
uint16_t BAR30_Read_PromData(BAR30_DeviceParam_T *handle){
	uint8_t RxBuff[2];
	if(!BAR30_Read(handle, BAR30_COMAND_PROM_READ, RxBuff))
		return RxBuff[0] | (RxBuff[1]<<8);
	else
		return BAR30_INCORRECTED_DATA;
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
BAR30_ReturnTypeDef_T BAR30_Write(BAR30_DeviceParam_T *handle, uint8_t command){
	uint8_t TxBuff[1];
	TxBuff[0] = command;
	return BAR30_SendReceive(handle, TxBuff, 2, NULL, 0);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
BAR30_ReturnTypeDef_T BAR30_Read(BAR30_DeviceParam_T *handle, uint8_t command, uint8_t *data){
	uint8_t TxBuff[1];
	TxBuff[0] = command;
	return BAR30_SendReceive(handle, TxBuff, 1, data, 2);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
BAR30_ReturnTypeDef_T BAR30_SendReceive(BAR30_DeviceParam_T *handle, uint8_t *txBuff, uint8_t txLenght, uint8_t *rxBuff, uint8_t rxLenght){
	HAL_Delay(5);
	return BAR30_CommPorter_SendReceive(handle->I2C_No, handle->TxDevAdress, handle->RxDevAdress, txBuff, txLenght, rxBuff, rxLenght);
}
