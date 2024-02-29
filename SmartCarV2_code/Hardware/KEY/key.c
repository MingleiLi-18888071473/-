#include "key.h"
#include "led.h"


/**
************************************************************************************************
* @brief    按键状态读取函数，可以读取按键的状态
* @param    None
* @return   返回 1 时表示按键松开，返回 0 时表示按键按下
* @author   Jiangnan University - 遥遥领先队
************************************************************************************************
**/
uint8_t Key_StaRead( void )
{
    return( HAL_GPIO_ReadPin( KEY_PORT, KEY_PIN ) );
}

/**
************************************************************************************************
* @brief    EXTI0 中断回调函数
* @param    GPIO_Pin: Specifies the pins connected EXTI line
* @return   None
* @author   一点创绘——卢佳威
************************************************************************************************
**/
// 写在这的话 platformio无法识别到，但比如说在 keil5 MDK 里面都是可以检测到的
// void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
// {
//     if( Key_StaRead() == 0 )     // 确保是按键按下触发的
//     {
//         LED_Toggle();
//     }
// }

