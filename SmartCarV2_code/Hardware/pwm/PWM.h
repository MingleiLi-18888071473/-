#ifndef __PWM_H

#define __PWM_H

//////////////////////////////////////////
// 本程序只供学习使用，未经作者许可，不得用于其它任何用途
// 作者：Jiangnan University - 遥遥领先队
//////////////////////////////////////////

#include "stm32f1xx_hal.h"


/********** PWM定时器设置 ************/
#define PWM_HAL_TIMX          htim2
#define PWM_TIMX              TIM2
#define PWM_CHANNELX          TIM_CHANNEL_1 
#define PWM_CHANNELX2         TIM_CHANNEL_2 


void PWM_Init( void );
void PWM_DutySet( TIM_TypeDef* timx, uint8_t channel, uint16_t duty );
void Motor_Control( uint16_t speed );


#endif
