#include <stdint.h>

#ifndef FILTERS_AVARAGEFILTER_H_
#define FILTERS_AVARAGEFILTER_H_

#define AvarageFilter_DataNumber 10

typedef struct{
	uint8_t FilterBufferSize;
	int16_t buffer[64];
	int64_t sum;
	int16_t Avarage;
	uint8_t DataCounter;
}AvarageFilterParam_T;

extern AvarageFilterParam_T AvarageFilter_MPU6050_X, AvarageFilter_MPU6050_Y, AvarageFilter_MPU6050_Z;
void AvarageFilter_Init(AvarageFilterParam_T *handle, uint8_t FilterBufferSize);
uint8_t AvarageFilter(AvarageFilterParam_T *handle, int16_t data);
#endif /* FILTERS_AVARAGEFILTER_H_ */
