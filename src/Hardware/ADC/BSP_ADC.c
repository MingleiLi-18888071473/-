#include "BSP_ADC.h"
//////////////////////////////////////////
// ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
// ���ߣ�Jiangnan University - ңң���ȶ�
//////////////////////////////////////////

extern ADC_HandleTypeDef   HAL_ADCX;


/**
***********************************************************************************************************
*	@Function		: ADC_Init
*	@Description	:	ADC��ʼ��
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
*	@Description	:	��ȡADC��ֵ
*	@Input			:	None
*	@Return			: ����ADC��ȡ������ֵ
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


