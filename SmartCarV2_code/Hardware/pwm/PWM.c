#include "PWM.h"
//////////////////////////////////////////
// ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
// ���ߣ�Jiangnan University - ңң���ȶ�
//////////////////////////////////////////

extern TIM_HandleTypeDef PWM_HAL_TIMX;


/**
***********************************************************************************************************
*	@Function		: PWM_Init
*	@Description	:	PWM��ʼ������
*	@Input			:	None
*	@Return			: None
***********************************************************************************************************
*/
void PWM_Init( void )
{
  HAL_TIM_PWM_Start( &PWM_HAL_TIMX, PWM_CHANNELX );     //��ʼ��ͨ��1
	HAL_TIM_PWM_Start( &PWM_HAL_TIMX, PWM_CHANNELX2);     //��ʼ��ͨ��2
}

/**
***********************************************************************************************************
*	@Function		: PWM_DutySet
*	@Description	:	PWMռ�ձ����ú�������ʵ�Ǹߵ�ƽʱ�����ú�����ռ�ձ���һ���ٷֱȣ�
*	@Input			:	
*         *timx : ��ʱ�����֣���TIM1��TIM2��TIM3�ȵ�
*         channel : ��ʱ��ͨ���ţ���1��2��3��4
*         duty : ���õ�ռ�ձȣ�ע��Ҫ��������
*	@Return			: None
***********************************************************************************************************
*/
void PWM_DutySet( TIM_TypeDef* timx, uint8_t channel, uint16_t duty )
{
  switch( channel )
  {
    case 1:
    {
      timx->CCR1 = duty;
      break;
    }
    case 2:
    {
      timx->CCR2 = duty;
      break;
    }
    case 3:
    {
      timx->CCR3 = duty;
      break;
    }
    case 4:
    {
      timx->CCR4 = duty;
      break;
    }
  }
}

// user define
void Motor_Control( uint16_t speed )
{
	uint16_t set_speed = speed;
	
	if( set_speed > 999 )	set_speed = 999;
	
	if( speed == 0 )
	{
		PWM_DutySet( PWM_TIMX, 1, 999 );
		PWM_DutySet( PWM_TIMX, 2, 999 );
	}
	else
	{
		PWM_DutySet( PWM_TIMX, 1, 0 );
		PWM_DutySet( PWM_TIMX, 2, speed );
	}
}
  


