#include "BSP_ADC.h"
//////////////////////////////////////////
// 本程序只供学习使用，未经作者许可，不得用于其它任何用途
// 作者：Jiangnan University - 遥遥领先队
//////////////////////////////////////////

extern ADC_HandleTypeDef   HAL_ADCX;


/**
***********************************************************************************************************
*	@Function		: ADC_Init
*	@Description	:	ADC初始化
*	@Input			:	None
*	@Return			: None
***********************************************************************************************************
*/
void ADC_Init( void )
{
  HAL_ADC_Start( &HAL_ADCX );
  HAL_ADCEx_Calibration_Start( &HAL_ADCX );
}

/**
***********************************************************************************************************
*	@Function		: Get_ADC_Value
*	@Description	:	获取ADC数值
*	@Input			:	None
*	@Return			: 返回ADC读取到的数值
***********************************************************************************************************
*/
uint32_t Get_ADC_Value( void )
{
  uint32_t adc_value;
  
  HAL_ADC_Start( &HAL_ADCX );
  if( HAL_ADC_PollForConversion( &HAL_ADCX, 0xff ) == HAL_OK )
  {
    adc_value = HAL_ADC_GetValue( &HAL_ADCX );
  }
  return( adc_value );
}


