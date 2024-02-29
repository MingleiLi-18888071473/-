#include "led.h"



/**
************************************************************************************************
* @brief    控制LED灯电平反转
* @param    None
* @return   None
* @author   Jiangnan University - 遥遥领先队
************************************************************************************************
**/
void LED_Toggle( void )
{
    HAL_GPIO_TogglePin( LED_PORT, LED_PIN );    // 电平翻转
}

/**
************************************************************************************************
* @brief    控制LED灯亮或者灭
* @param    sta: 控制LED灯的状态，当为1时灯亮，当为0时灯灭，其他值不做响应
* @return   None
* @author   Jiangnan University - 遥遥领先队
************************************************************************************************
**/
extern uint8_t test;
void LED_Sta( uint8_t sta )
{
    switch( sta )
    {
        case 1:     //灯亮
        {
            HAL_GPIO_WritePin( LED_PORT, LED_PIN, GPIO_PIN_RESET );     // GPIO 置0
						HAL_GPIO_WritePin( GPIOB, GPIO_PIN_12, GPIO_PIN_RESET );
						HAL_GPIO_WritePin( GPIOA, GPIO_PIN_8, GPIO_PIN_RESET );
						test = 1;
            break;
        }
        case 0:     //灯灭
        {
            HAL_GPIO_WritePin( LED_PORT, LED_PIN, GPIO_PIN_SET );       // GPIO 置1
						HAL_GPIO_WritePin( GPIOB, GPIO_PIN_12, GPIO_PIN_SET );
						HAL_GPIO_WritePin( GPIOA, GPIO_PIN_8, GPIO_PIN_SET );
						test = 0;
            break;
        }
        default:
        {
            break;
        }
		}
				
}



