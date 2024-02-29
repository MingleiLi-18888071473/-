#include <stdio.h>
#if __has_include(<sys/stat.h>)
#include <sys/stat.h>
#include "usart.h"
#include "stm32f1xx_hal.h"


#ifdef __cplusplus
extern "C"
{
#endif
    // 重定向到串口1
    int _write(int fd, uint8_t *pBuffer, int size)
    {
        for (int i = 0; i < size; i++)
        {
            while (!(USART1->SR & USART_SR_TXE))
            {
            }
            HAL_UART_Transmit(&huart1, &pBuffer[i], 1, 0xFFFF);
        }
        return size;
    }
 
    int _read(int fd, uint8_t *pBuffer, int size)
    {
        for (int i = 0; i < size; i++)
        {
            while ((USART1->SR & USART_SR_RXNE) == 0)
            {
            }
            pBuffer[i] = HAL_UART_Receive(&huart1, &pBuffer[i], 1, 0xFFFF);
        }
        return size;
    }
 
    caddr_t _sbrk(int increment)
    {
        extern char end asm("end");
        register char *pStack asm("sp");
 
        static char *s_pHeapEnd;
 
        if (!s_pHeapEnd)
            s_pHeapEnd = &end;
 
        if (s_pHeapEnd + increment > pStack)
            return (caddr_t)-1;
 
        char *pOldHeapEnd = s_pHeapEnd;
        s_pHeapEnd += increment;
        return (caddr_t)pOldHeapEnd;
    }
 
    int _close(int fd)
    {
        return -1;
    }
 
    int _lseek(int fd1, int fd2, int fd3)
    {
        return -1;
    }
 
    int _fstat(int fd, struct stat *pStat)
    {
        pStat->st_mode = S_IFCHR;
        return 0;
    }
 
    int _isatty(int fd)
    {
        return 1;
    }
 
#ifdef __cplusplus
}
#endif

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
 
  return ch;
}

#endif

