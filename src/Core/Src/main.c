/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  *@author          : Jiangnan University - 遥遥领先队
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "BSP_USART.h"
#include "stdio.h"
#include "led.h"
#include "Card.h"
#include "BSP_ADC.h"
#include "PWM.h"
#include "TIMER.h"
#include "Message.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
extern uint8_t card_res;
extern uint8_t card_res_flag;
uint8_t chinese_data[60];
int32_t chinese_block_num = 0;
extern CMD Cmd;
int32_t read_block = 4;
uint8_t wait_time = 0;
uint8_t wait_resend_times = 0;
uint32_t led_flash_counts = 0;
uint8_t test = 0;
int32_t led_close_counts = 0;
uint32_t res = 0;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
	
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
	LED_Sta( 0 );
	PWM_Init();
	Motor_Control( 0 );
	
	HAL_UART_Receive_IT(&CARD_HAL_USARTx,(uint8_t *)&card_res, 1);
	
	// 获取ADC值
	// uint32_t adc_value = 0;
	// for( uint8_t i = 0; i < 20; i++ )
	// {
	// 	adc_value += Get_ADC_Value();
	// 	HAL_Delay( 1 );
	// }
	// adc_value = adc_value/20;
	// res = adc_value >= 4095 ? 5000-5000 : 5000-adc_value*1000/(4095-adc_value);	// 阻值计算
	
	// 晚启动 1s 时间
	card_res_flag = CARD_FLAG_EXIST;
	
	// 定时器开启
	Timer_Init();
	#if START_SET == ENABLE
	 LED_Sta( 1 );
	HAL_Delay(800);
	 printf("????");
	#endif
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		if( card_res_flag == CARD_FLAG_EXIST )
		{
			BufClear( Cmd.block_data );
			ReadBlock( read_block+chinese_block_num );
			while( !__HAL_UART_GET_FLAG( &CARD_HAL_USARTx, UART_FLAG_TC ) );	// 还在发送数据
			card_res_flag = CARD_FLAG_WAIT;
			wait_time = 0;
			wait_resend_times = 0;
		}
		else if( card_res_flag == CARD_FLAG_RESDATA )	// 接收到一段数据
		{
			if( chinese_block_num == 0 && !Cmd.block_data[0] )	// 没有数据
			{
				chinese_block_num = -3;
				card_res_flag = CARD_FLAG_EXIST;
			}
			else if( chinese_block_num == -3 && !Cmd.block_data[0] )	// 没有数据
			{
				LED_Sta(1);                                           //有uid直接亮
				HAL_Delay( 600 );									  //硬件延时
				card_res_flag = CARD_FLAG_NONE;
				printf("UID????????");
				while( !__HAL_UART_GET_FLAG( &HAL_USARTX, UART_FLAG_TC ) );	// 还在发送数据
				HAL_Delay( 200 );
//				read_block++;
//				card_res_flag = CARD_FLAG_EXIST;
//				if( read_block == 10 )
//				{
//					card_res_flag = CARD_FLAG_NONE;
//				}
			}
			else	// 有数据
			{
				
				if( chinese_block_num == -3 )
				{
					if(Message_setting == ENABLE)
					{
						Usartx_SendString( Cmd.block_data );
						Message_setting = 3;
					}
					while( !__HAL_UART_GET_FLAG( &HAL_USARTX, UART_FLAG_TC ) );	// 还在发送数据
					HAL_Delay( 200 );
					card_res_flag = CARD_FLAG_LEDLIGHT;
					led_close_counts = 10;
				}
				else if( chinese_block_num > 2 )	// 读完整数据
				{
					LED_Sta( 1 );
					if(Message_setting == ENABLE)
					{
						Usartx_SendString( chinese_data );
						Message_setting = 3;
					}
					while( !__HAL_UART_GET_FLAG( &HAL_USARTX, UART_FLAG_TC ) );	// 还在发送数据
//				card_res_flag = CARD_FLAG_NONE;
				
				BufClear( Cmd.block_data );
//				BufClear_num( Cmd.ReceiveBuffer, 32 );
					HAL_Delay( 500 );
					card_res_flag = CARD_FLAG_LEDLIGHT;
					led_close_counts = 10;
				}
				else
				{
					MessageGet(Cmd.block_data[0],Cmd.block_data[1],Cmd.block_data[2]); 
					for( uint8_t i = 0; i < 16; i++ )
					{
						chinese_data[i+chinese_block_num*16] = Cmd.block_data[i];
					}
					chinese_block_num++;
					card_res_flag = CARD_FLAG_EXIST;
				}
				
			}
		}
		else if( card_res_flag == CARD_FLAG_WAIT )		// 等待模式
		{
			HAL_Delay( 1 );
			wait_time++;
			if( wait_time >= 20 )	// 等待超过20ms
			{
				wait_resend_times ++;
				card_res_flag = CARD_FLAG_EXIST;
			}
			if( wait_resend_times >= 3 )	// 超过3次
			{
				wait_resend_times = 0;
				wait_time = 0;
				card_res_flag = CARD_FLAG_NONE;
			}
		}
		
		if( card_res_flag == CARD_FLAG_NONE )		// 休眠模式
		{
			BufClear( chinese_data );
			chinese_block_num = 0;
			LED_Sta( 0 );
//			// 暂停滴答时钟，防止通过滴答时钟中断唤醒
//			HAL_SuspendTick();
//			// 进入睡眠模式
//			HAL_PWR_EnterSLEEPMode( PWR_MAINREGULATOR_ON,PWR_SLEEPENTRY_WFI );
//			// 被唤醒，开启滴答时钟
//			HAL_ResumeTick();
			wait_time = 0;
			wait_resend_times = 0;
//			card_res_flag = CARD_FLAG_EXIST;
		}
		else
		{
			if( card_res_flag == CARD_FLAG_LEDLIGHT )
			{
				LED_Sta( 1 );
				ReadCard();
				HAL_Delay( 10 );
			}
		}
		
//		if( led_flash_counts < 100000 )
//		{
//			led_flash_counts = led_flash_counts + 1;
//			if( led_flash_counts == 100000 )
//			{
//				LED_Sta( 0 );
//			}
//		}
		
		
//		HAL_Delay( 1000 );
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
