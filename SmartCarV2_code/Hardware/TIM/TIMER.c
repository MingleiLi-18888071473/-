#include "TIMER.h"
#include "LED.h"
#include "PWM.h"
//////////////////////////////////////////
// 本程序只供学习使用，未经作者许可，不得用于其它任何用途
// Jiangnan University - 遥遥领先队
//////////////////////////////////////////

extern TIM_HandleTypeDef TIMER_HAL_TIMX;


/**
***********************************************************************************************************
*	@Function		: Timer_Init
*	@Description	:	定时器初始化
*	@Input			:	None
*	@Return			: None
***********************************************************************************************************
*/
void Timer_Init( void )
{
  HAL_TIM_Base_Start_IT( &TIMER_HAL_TIMX );    // 打开定时器中断
}


/**
***********************************************************************************************************
*	@Function		: HAL_TIM_PeriodElapsedCallback
*	@Description	:	定时器中断回调函数
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
  if( htim == &TIMER_HAL_TIMX )    // TIM1中断判断
  {
    static uint32_t count = 0;
  
    count++;  // 自加一用来计数，单位 ms
		
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
    
    if( count >= 1000*1000 )   // 当计数到 1000s 时
    {
      count = 1000*1000;
    }
  }
}






