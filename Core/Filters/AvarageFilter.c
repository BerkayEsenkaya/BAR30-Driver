/**
 * \file AvarageFilter.c
 * \author Berkay Esenkaya (BAUROV Software Team)
 * \brief Avarage Filter Functions
 * \date 11.03.2025
 *
 */
#include "AvarageFilter.h"

AvarageFilterParam_T AvarageFilter_MPU6050_1;

void AvarageFilter_Init(AvarageFilterParam_T *handle, uint8_t FilterBufferSize){
	handle->FilterBufferSize = FilterBufferSize;
	handle->DataCounter = 0;
	handle->sum = 0;

}

uint8_t AvarageFilter(AvarageFilterParam_T *handle, uint16_t data){

//	if(handle->DataCounter+1 == handle->FilterBufferSize){
//		for(int i = 0; i <=handle->DataCounter; i++ ){
//			handle->sum +=  buffer[i];
//		}
//		handle->Avarage = handle->sum / handle->FilterBufferSize;
//		handle->sum = 0;
//		for(int i = 0; i <=handle->DataCounter; i++ ){
//			handle->buffer[i] = handle->buffer[i+1];
//		}
//		handle->DataCounter -= 2;
//	}else{
//		handle->buffer[handle->DataCounter] = data;
//	}
//	++handle->DataCounter;
}
