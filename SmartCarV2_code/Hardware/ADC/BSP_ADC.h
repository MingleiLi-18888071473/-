#ifndef __BSP_ADC_H

#define __BSP_ADC_H

//////////////////////////////////////////
// 本程序只供学习使用，未经作者许可，不得用于其它任何用途
// 作者：Jiangnan University - 遥遥领先队
//////////////////////////////////////////

#include "stm32f1xx_hal.h"



/********** ADC 设置 ************/
#define HAL_ADCX              hadc1




void ADC_Init( void );
uint32_t Get_ADC_Value( void );

#endif 
