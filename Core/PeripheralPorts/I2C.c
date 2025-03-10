/**
 * \file I2C.c
 * \author Berkay Esenkaya (BAUROV Software Team)
 * \brief I2C communication peripheral porters
 * \date 24.02.2025
 *
 */

#include "I2C.h"
#include "main.h"
#include "stm32f4xx.h"

I2C_HandleTypeDef_T I2C_1, I2C_2, I2C_3;

/**********************************************************
 * GLOBAL FUNCTIONS
 ********************************************************/
/** Brief description which ends at this dot. Details follow
 *  here.
 */
void I2C_Init(void *handle, uint8_t I2CNo){
	I2C_HandleTypeDef_T *i2c;
	i2c = I2C_GetModule(I2CNo);
    i2c->handle = handle;
}


/** Brief description which ends at this dot. Details follow
 *  here.
 */
I2C_ReturnTypeDef_T I2C_ReadWrite(uint8_t I2CNo, uint8_t DevAddress, uint8_t *txBuff, uint8_t txLenght, uint8_t *rxBuff, uint8_t rxLenght){
	I2C_HandleTypeDef_T *i2c;
	HAL_StatusTypeDef res;
	i2c = I2C_GetModule(I2CNo);
	if(rxLenght == 0){
		res = HAL_I2C_Master_Transmit(i2c->handle , DevAddress, txBuff, txLenght, 300);
		return res == I2C_ERROR;
	}else{
		HAL_I2C_Master_Transmit(i2c->handle , DevAddress, txBuff, txLenght, 300);

		res = HAL_I2C_Master_Receive(i2c->handle, DevAddress, rxBuff, rxLenght, 300);
		return res == I2C_ERROR;
	}
}

/**********************************************************
 * PRIVATE FUNCTIONS
 *********************************************************/
/** Brief description which ends at this dot. Details follow
 *  here.
 */
I2C_HandleTypeDef_T* I2C_GetModule(uint8_t I2CNo){
	switch(I2CNo){
		case I2CNO_1 : return &I2C_1; break;
		case I2CNO_2 : return &I2C_2; break;
		case I2CNO_3 : return &I2C_3; break;
		default : return NULL; break;
	}
}
