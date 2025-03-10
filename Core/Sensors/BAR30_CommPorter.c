#include <stdint.h>
#include "BAR30_CommPorter.h"
#include "I2C.h"

uint8_t BAR30_CommPorter_SendReceive(uint8_t I2CNo, uint8_t DevAddress, uint8_t *txBuff, uint8_t txLenght, uint8_t *rxBuff, uint8_t rxLenght){
	return I2C_ReadWrite(I2CNo, DevAddress, txBuff, txLenght, rxBuff, rxLenght);
}
