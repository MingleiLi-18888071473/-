#include "TIMER.h"
#include "LED.h"
#include "PWM.h"
//////////////////////////////////////////
// ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
// Jiangnan University - ңң���ȶ�
//////////////////////////////////////////

extern TIM_HandleTypeDef TIMER_HAL_TIMX;


/**
***********************************************************************************************************
*	@Function		: Timer_Init
*	@Description	:	��ʱ����ʼ��
*	@Input			:	None
*	@Return			: None
***********************************************************************************************************
*/
void Timer_Init( void )
{
  HAL_TIM_Base_Start_IT( &TIMER_HAL_TIMX );    // �򿪶�ʱ���ж�
}


/**
***********************************************************************************************************
*	@Function		: HAL_TIM_PeriodElapsedCallback
*	@Description	:	��ʱ���жϻص�����
*	@Input			:	*htim
*	@Return			: None
***********************************************************************************************************
*/
#define PRE_CHARGE_TIME									3000		// 3s
#define RES_MAX													5000		// 5K
#define STOP_TIME_MIN										(10*1000)	// 10s
#define STOP_TIME_MAX										(10*60*1000)// 300s = 5min
extern uint32_t res;
uint32_t stop_time = 0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if( htim == &TIMER_HAL_TIMX )    // TIM1�ж��ж�
  {
    static uint32_t count = 0;
  
    count++;  // �Լ�һ������������λ ms
		
		if( count < PRE_CHARGE_TIME )
		{
			Motor_Control( 999*count/PRE_CHARGE_TIME );
		}
		else
		{
			Motor_Control( 999 );
		}
		
		stop_time = res > RES_MAX ? STOP_TIME_MAX : STOP_TIME_MIN+res*(STOP_TIME_MAX-STOP_TIME_MIN)/RES_MAX;
		
		if( count > stop_time )
		{
			Motor_Control( 0 );
		}
    
    if( count >= 1000*1000 )   // �������� 1000s ʱ
    {
      count = 1000*1000;
    }
  }
}






