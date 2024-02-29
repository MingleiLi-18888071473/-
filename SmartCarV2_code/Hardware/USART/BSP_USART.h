#ifndef __BSP_USART_H
#define __BSP_USART_H
#include "stm32f1xx_hal.h"


/********** 串口号设置 ************/
#define HAL_USARTX            huart2
#define USARTX                USART2



void Usartx_SendString( uint8_t *str );
void Usartx_RxIT_Start( uint16_t rx_num );
void BufClear( uint8_t* buf );
/**
************************************************************************************************
* @brief    数组清空
* @param    buf 要清空的数组
* @return   None
************************************************************************************************
**/
static void BufClear( uint8_t* buf )
{
	uint8_t k = 0;
	
	while( buf[k] != '\0' )
	{
		buf[k] = 0;
		k++;
	}
}

#endif
