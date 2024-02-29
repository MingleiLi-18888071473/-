#include "BSP_USART.h"
#include "stdio.h"
#include "LED.h"


static void BufClear( uint8_t* buf );
  
extern UART_HandleTypeDef HAL_USARTX;

#define USARTX_RX_LEN         100

uint8_t usartx_rx_buf[USARTX_RX_LEN];
uint16_t usartx_rx_status = 0;

/**
************************************************************************************************
* @brief    开启串口接收中断
* @param    rx_num: 接收几个字节
* @return   None
************************************************************************************************
**/
void Usartx_RxIT_Start( uint16_t rx_num )
{  
  HAL_UART_Receive_IT( &HAL_USARTX, usartx_rx_buf, rx_num );
}

/**
************************************************************************************************
* @brief    使用c语言标准库的 printf 函数需进行如下修改
* @param    None
* @return   None
************************************************************************************************
**/
int fputc(int ch,FILE * fp)
{
  HAL_UART_Transmit( &HAL_USARTX, (uint8_t * )&ch, 1, 0xffff );
  return ch;
}

/**
************************************************************************************************
* @brief    串口数据发送函数
* @param    str: 要发送的字符串
* @return   None
************************************************************************************************
**/
void Usartx_SendString( uint8_t *str )
{
  uint16_t i = 0;
  while( str[i] )
  {
    HAL_UART_Transmit( &HAL_USARTX, (uint8_t *)(str+i), 1, 0xffff );
    i++;
  }
  
}


