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

float Convert_IEE754_To_FloatValue(const uint32_t value){
	float f;
	memcpy(&f, &value, sizeof(float));
	return f;
}

BAR30_ReturnTypeDef_T BAR30_Calc_Pressure(BAR30_Sensor_T *handle){
	switch(handle->mode){
		case Zero_At_Atm    : handle->miliPressure = (((handle->Pressure_RawData - handle->PMin)*((handle->PMax-handle->PMin)*1000))/handle->PMax)-handle->PMin; break;
		case Zero_At_1Bar   : handle->miliPressure = (((handle->Pressure_RawData-16384)*((handle->PMax-handle->PMin)*1000))/32768)+handle->PMin;break;
		case Zero_At_Vacuum : handle->miliPressure = ((handle->Pressure_RawData-handle->PMin)*((handle->PMax-handle->PMin)*1000))/handle->PMax+handle->PMin;     break;
	}
}
/** Brief description which ends at this dot. Details follow
 *  here.
 */
BAR30_ReturnTypeDef_T BAR30_Init(BAR30_Sensor_T *handle, uint8_t i2cNo, uint8_t devI2CAddress){
	handle->devParam.I2C_No = i2cNo;
	handle->devParam.DevAdress = devI2CAddress;
	return BAR30_OK;
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
BAR30_ReturnTypeDef_T BAR30_StartPressureConversion(BAR30_Sensor_T *handle){
	BAR30_ReturnTypeDef_T res;
	res =  BAR30_Write(handle, 0xA0);
	return res;
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
BAR30_ReturnTypeDef_T BAR30_ReadPressure(BAR30_Sensor_T *handle){
	uint8_t RxBuff[5], state;
	if(!BAR30_Read(handle, 0xAC, RxBuff)){
		handle->Pressure_RawData = RxBuff[2] | (RxBuff[1]<<8);
	    handle->Temperature_RawData = RxBuff[4] | (RxBuff[3]<<8);
	    state = RxBuff[0];
	    BAR30_Calc_Pressure(handle);
	}
	else
		return BAR30_ERROR;
}

//BAR30_ReturnTypeDef_T BAR30_Get_CustIds(BAR30_Sensor_T *handle){
//	uint8_t RxBuff[1];
//	if(!BAR30_Read(handle, BAR30_MTP_ADDRESS_CUST_ID_0, RxBuff)){
//		handle->CustIDs_1 = RxBuff[1] | RxBuff[0]<<8;
//	}
//	if(!BAR30_Read(handle, BAR30_MTP_ADDRESS_CUST_ID_1, RxBuff)){
//			handle->CustIDs_2 = RxBuff[1] | RxBuff[0]<<8;
//			return BAR30_OK;
//	}
//	return BAR30_ERROR;
//}

BAR30_ReturnTypeDef_T BAR30_Get_ScalingValues(BAR30_Sensor_T *handle){
	uint8_t RxBuff[3];
	uint16_t ScaleData[5];
    uint32_t iee754;
	for(int i=0; i<5;i++){
		if(!BAR30_Read(handle, BAR30_MTP_ADDRESS_SCALING_BASE + i, RxBuff)){
			ScaleData[i]= RxBuff[2]<<0 | RxBuff[1]<<8;
		}else{
			return BAR30_ERROR;
		}
	}

    handle->mode = ScaleData[0]&(0x0003);
    iee754 = ScaleData[1]<<16 | ScaleData[2];
    handle->PMin = Convert_IEE754_To_FloatValue(iee754);
    iee754 = ScaleData[3]<<16 | ScaleData[4];
    handle->PMax = Convert_IEE754_To_FloatValue(iee754);
	return BAR30_OK;
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
BAR30_ReturnTypeDef_T BAR30_Write(BAR30_Sensor_T *handle, uint8_t command){
	uint8_t TxBuff[1];
	TxBuff[0] = command;
	return BAR30_SendReceive(handle, TxBuff, 1, NULL, 0);
}

BAR30_ReturnTypeDef_T BAR30_Read(BAR30_Sensor_T *handle, uint8_t command, uint8_t *buffer){
	uint8_t lenght;

	if(command == 0xAC)
		lenght = 5;
	else
		lenght = 3;

	return BAR30_SendReceive(handle, &command, 1, buffer, lenght);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
BAR30_ReturnTypeDef_T BAR30_SendReceive(BAR30_Sensor_T *handle, uint8_t *txBuff, uint8_t txLenght, uint8_t *rxBuff, uint8_t rxLenght){
	HAL_Delay(10);
	return BAR30_CommPorter_SendReceive(handle->devParam.I2C_No, handle->devParam.DevAdress, txBuff, txLenght, rxBuff, rxLenght);
}
