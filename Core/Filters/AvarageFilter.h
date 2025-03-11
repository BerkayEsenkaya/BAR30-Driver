#include <stdint.h>

#ifndef FILTERS_AVARAGEFILTER_H_
#define FILTERS_AVARAGEFILTER_H_

#define AvarageFilter_DataNumber 10

typedef struct{
	uint8_t FilterBufferSize;
	uint32_t sum;
	uint16_t Avarage;
	uint8_t DataCounter;
}AvarageFilterParam_T;
extern AvarageFilterParam_T AvarageFilter_MPU6050_1;
#endif /* FILTERS_AVARAGEFILTER_H_ */
