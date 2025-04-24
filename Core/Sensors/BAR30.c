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

const uint8_t BAR30_CRC_LU_Table[16] = {
    0x0, 0x3, 0x6, 0x5,
    0xC, 0xF, 0xA, 0x9,
    0xB, 0x8, 0xD, 0xE,
    0x7, 0x4, 0x1, 0x2
};

/**
 * @brief MS5837 için 4-bit CRC hesaplayıcı
 * @param prom PROM registerlarının dizisi (8 eleman, her biri 16-bit)
 * @return 4-bit CRC değeri (0-15)
 */
uint8_t BAR30_Calc_Crc(uint16_t AllPromData[8]) {
    uint8_t n_rem = 0x00;
    uint16_t crc_read = AllPromData[0] & 0x000F; // PROM'dan okunan CRC (4 bit)
    AllPromData[0] &= 0xFFF0; // CRC alanını sıfırla (hesaplamayı etkileyen kısmı temizle)

    for (int cnt = 0; cnt < 16; cnt++) {
        uint8_t byte;
        if (cnt % 2 == 0)
            byte = (uint8_t)(AllPromData[cnt >> 1] >> 8);
        else
            byte = (uint8_t)(AllPromData[cnt >> 1] & 0x00FF);

        uint8_t tmp = (n_rem >> 4) ^ (byte >> 4);
        n_rem = (n_rem << 4) ^ BAR30_CRC_LU_Table[tmp & 0x0F];

        tmp = (n_rem >> 4) ^ (byte & 0x0F);
        n_rem = (n_rem << 4) ^ BAR30_CRC_LU_Table[tmp & 0x0F];
    }

    n_rem = (n_rem >> 12) & 0x0F; // Sadece 4 bitlik CRC değeri kalır

//    handle->PromData[7] |= crc_read; // CRC alanını geri yükle (opsiyonel)

    if((n_rem ^ 0x00) == crc_read)
    	return BAR30_OK;
    else
    	return BAR30_ERROR;
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
BAR30_ReturnTypeDef_T BAR30_Reset(BAR30_Sensor_T *handle){
	return BAR30_Write(handle, BAR30_COMMAND_RESET);
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
	uint8_t RxBuff[3];
	if(!BAR30_ReadMeasData(handle, BAR30_COMMAND_ADC_READ, RxBuff))
		handle->PressureData = RxBuff[0] | (RxBuff[1]<<8) | RxBuff[2]<<16;
	else
		return BAR30_ERROR;
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
BAR30_ReturnTypeDef_T BAR30_Get_AllPromData(BAR30_Sensor_T *handle){
	BAR30_ReturnTypeDef_T res = 0, crc;
	uint8_t RxBuff[2];
	uint16_t AllPromData[7];
	BAR30_Read(handle, BAR30_COMMAND_PROM_READ_1,  RxBuff);
	AllPromData[0] = RxBuff[1] | (RxBuff[0]<<8);
	BAR30_Read(handle, BAR30_COMMAND_PROM_READ_2,  RxBuff);
	AllPromData[1] = RxBuff[1] | (RxBuff[0]<<8);
	BAR30_Read(handle, BAR30_COMMAND_PROM_READ_3,  RxBuff);
	AllPromData[2] = RxBuff[1] | (RxBuff[0]<<8);
	BAR30_Read(handle, BAR30_COMMAND_PROM_READ_4,  RxBuff);
	AllPromData[3] = RxBuff[1] | (RxBuff[0]<<8);
    BAR30_Read(handle, BAR30_COMMAND_PROM_READ_5,  RxBuff);
    AllPromData[4] = RxBuff[1] | (RxBuff[0]<<8);
	BAR30_Read(handle, BAR30_COMMAND_PROM_READ_6,  RxBuff);
	AllPromData[5] = RxBuff[1] | (RxBuff[0]<<8);
    BAR30_Read(handle, BAR30_COMMAND_PROM_READ_7,  RxBuff);
    AllPromData[6] = RxBuff[1] | (RxBuff[0]<<8);
//    BAR30_Read(handle, BAR30_COMMAND_PROM_READ_8,  RxBuff);
//    AllPromData[7] = RxBuff[1] | (RxBuff[0]<<8);
//    BAR30_Read(handle, BAR30_COMMAND_PROM_READ_9,  RxBuff);
//    AllPromData[8] = RxBuff[1] | (RxBuff[0]<<8);
    if(BAR30_Calc_Crc(AllPromData) == BAR30_OK){
    	for(int i=0; i<7; i++){
    		handle->PromData[i] = AllPromData[i];
    	}
    	return BAR30_OK;
    }else
    	return BAR30_ERROR;
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
	return BAR30_SendReceive(handle, TxBuff, 2, NULL, 0);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
BAR30_ReturnTypeDef_T BAR30_Read(BAR30_Sensor_T *handle, uint8_t command, uint8_t *buffer){
	uint8_t TxBuff[1];
	TxBuff[0] = command;
	return BAR30_SendReceive(handle, TxBuff, 1, buffer, 2);
}

BAR30_ReturnTypeDef_T BAR30_ReadMeasData(BAR30_Sensor_T *handle, uint8_t command, uint8_t *buffer){
	uint8_t TxBuff[1];
	TxBuff[0] = command;
	return BAR30_SendReceive(handle, TxBuff, 1, buffer, 3);
}

/** Brief description which ends at this dot. Details follow
 *  here.
 */
BAR30_ReturnTypeDef_T BAR30_SendReceive(BAR30_Sensor_T *handle, uint8_t *txBuff, uint8_t txLenght, uint8_t *rxBuff, uint8_t rxLenght){
	HAL_Delay(10);
	return BAR30_CommPorter_SendReceive(handle->devParam.I2C_No, handle->devParam.DevAdress, txBuff, txLenght, rxBuff, rxLenght);
}
