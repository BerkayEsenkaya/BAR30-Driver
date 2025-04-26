#define BAR30_DEVICE_ADDRESS (0x40)

#define BAR30_MTP_ADDRESS_CUST_ID_0 (0x00)
#define BAR30_MTP_ADDRESS_CUST_ID_1 (0x01)
#define BAR30_MTP_ADDRESS_SCALING_BASE (0x12)
#define BAR30_MTP_ADDRESS_SCALING_1 (0x13)
#define BAR30_MTP_ADDRESS_SCALING_2 (0x14)
#define BAR30_MTP_ADDRESS_SCALING_3 (0x15)
#define BAR30_MTP_ADDRESS_SCALING_4 (0x16)

#define BAR30_COMMAND_START_CONVERSION (0xA0)
#define BAR30_COMMAND_READ_CONVERSION_DATA (0xAC)

#define BAR30_INCORRECTED_DATA 9999

typedef enum{
	BAR30_OK,
	BAR30_ERROR,
}BAR30_ReturnTypeDef_T;

typedef enum{
	Zero_At_Atm,
	Zero_At_1Bar,
	Zero_At_Vacuum,
}BAR30_Mode_T;

typedef struct{
	uint8_t I2C_No;
	uint8_t DevAdress;
}BAR30_DeviceParam_T;

typedef struct{
	BAR30_DeviceParam_T devParam;
	uint16_t PromData[10];
	uint32_t Temperature_RawData;
	uint32_t Pressure_RawData;
	uint16_t miliCelcius;
	uint16_t miliPressure;
	uint16_t producttype;
	uint32_t PMax;
	uint32_t PMin;
	BAR30_Mode_T mode;
}BAR30_Sensor_T;

extern BAR30_Sensor_T BAR30_1, BAR30_2, BAR30_3;

BAR30_ReturnTypeDef_T BAR30_Init(BAR30_Sensor_T *handle, uint8_t i2cNo, uint8_t devI2CAddress);
BAR30_ReturnTypeDef_T BAR30_Reset(BAR30_Sensor_T *handle);
BAR30_ReturnTypeDef_T BAR30_Write(BAR30_Sensor_T *handle, uint8_t command);
BAR30_ReturnTypeDef_T BAR30_Read(BAR30_Sensor_T *handle, uint8_t command, uint8_t *data);
BAR30_ReturnTypeDef_T BAR30_SendReceive(BAR30_Sensor_T *handle, uint8_t *txBuff, uint8_t txLenght, uint8_t *rxBuff, uint8_t rxLenght);
BAR30_ReturnTypeDef_T BAR30_Get_AllPromData(BAR30_Sensor_T *handle);
BAR30_ReturnTypeDef_T BAR30_ReadPressure(BAR30_Sensor_T *handle);
BAR30_ReturnTypeDef_T BAR30_ReadTemperature(BAR30_Sensor_T *handle);
BAR30_ReturnTypeDef_T BAR30_StartPressureConversion(BAR30_Sensor_T *handle);
BAR30_ReturnTypeDef_T BAR30_StartTemperatureConversion(BAR30_Sensor_T *handle);
BAR30_ReturnTypeDef_T BAR30_ReadMeasData(BAR30_Sensor_T *handle, uint8_t command, uint8_t *buffer);
BAR30_ReturnTypeDef_T BAR30_Get_CustIds(BAR30_Sensor_T *handle);
BAR30_ReturnTypeDef_T BAR30_Get_ScalingValues(BAR30_Sensor_T *handle);
