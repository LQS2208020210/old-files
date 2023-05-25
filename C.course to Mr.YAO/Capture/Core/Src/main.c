/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
void forward_ref()		//向前，左前右前
		{
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1,2100);//左前 
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3,2000);//右前
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2,0); 
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4,0); 
		}
		void back_ref()			//向后，左后右后
		{
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3,0);//右后
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1,0);
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2,2000);//左后
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4,2000);
		}
		void left_ref()			//左转，左后右前
		{
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4,0);
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1,0);
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2,1300);
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3,1800);
		}
		void right_ref()		//右转，左前右后
		{
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2,0);
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3,0);
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1,2000);
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4,0);		
		}
		void stop_ref()			//占空比都为0
		{
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1,0);
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2,0);
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3,0);
			__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4,0);
		}
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
	uint32_t capture_Buf[3] = {0};
	uint8_t capture_Cnt = 0;
	uint8_t overload_Cnt = 0;
	uint32_t high_time;
	uint32_t low_time;
	uint8_t a[1];
	double HL_time;
	double LL_time;
	double fre;
	double duty;
	float Distance;
	uint8_t data[20];
	uint8_t receive_buff[255]={0};
	#define  BUFFER_SIZE  (255)
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern UART_HandleTypeDef huart1;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
	int fputc(int ch,FILE *f)
	{
		uint8_t temp[1] = {ch};
		HAL_UART_Transmit(&huart1, temp, 1, 2);
		return ch;
	}
	int fgetc(FILE *f)
	{
		uint8_t ch=0;
		HAL_UART_Receive  (&huart1 ,(uint8_t *)&ch,1,0xffff);
		return ch;
	}	

	void delay_us(uint16_t us)
{
	__HAL_TIM_SET_COUNTER (&htim2 ,0);
	while(__HAL_TIM_GET_COUNTER (&htim2 )<us );
}

uint16_t HCSR04_Read(void )
{
	HAL_GPIO_WritePin (TRIG_GPIO_Port ,TRIG_Pin ,GPIO_PIN_RESET );
	delay_us (2);
	HAL_GPIO_WritePin (TRIG_GPIO_Port ,TRIG_Pin ,GPIO_PIN_SET );
	delay_us (12);
	HAL_GPIO_WritePin (TRIG_GPIO_Port ,TRIG_Pin ,GPIO_PIN_RESET );	
	HAL_Delay (100);
}
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
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim2); //开启定时器2中断
	HAL_TIM_Base_Start(&htim3);	
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);//空闲中断使能 
  HAL_UART_Receive_DMA(&huart1, (uint8_t*)receive_buff, 255); 
	
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1); //开PWM
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2); //开PWM
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3); //开PWM
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4); //开PWM
	

	__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_1,TIM_INPUTCHANNELPOLARITY_RISING);//在运行时设置输入极性  检测到上升沿了才会进入输入捕获中断回调函数

	HAL_TIM_IC_Start_IT(&htim2,TIM_CHANNEL_1);//在中断模式下启动TIM Input Capture测量。
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		HCSR04_Read();
		
		
//		printf("频率: %7.3lfHz, 占空比： %4.1lf%%, 高电平时间: %7.3lf ms, 低电平时间：%7.3lf ms\r\n", fre, duty, HL_time, LL_time);
//		printf("distance = %.3fcm \r\n",Distance);


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
}

/* USER CODE BEGIN 4 */


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim -> Instance == htim2.Instance)
	{
		overload_Cnt++;
	}
}
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim -> Instance == htim2.Instance)
	{
		switch(capture_Cnt)
		{
			case 0:
				capture_Buf[0] = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);
			  __HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_1, TIM_ICPOLARITY_FALLING);
			  overload_Cnt = 0;
			  capture_Cnt++;
				break;
			case 1:
				capture_Buf[1] = HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_1);
		  	high_time =  (capture_Buf[1] - capture_Buf[0]) + overload_Cnt * 100;		
				overload_Cnt = 0;	
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_1, TIM_ICPOLARITY_RISING);			
				capture_Cnt++;
		    break;
			case 2:
				capture_Buf[2] = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);	
			  HAL_TIM_IC_Stop_IT(&htim2,TIM_CHANNEL_1);//中断模式下停止输入捕获的测量
			 
				low_time = (capture_Buf[2] - capture_Buf[1]) + overload_Cnt * 100;
			
				HL_time = high_time * 0.001;
			  LL_time = low_time * 0.001;
				fre = 1000/(HL_time + LL_time);
				duty = HL_time/(HL_time + LL_time) * 100;
			 
//		  	__HAL_TIM_SET_COUNTER (&htim2, 0);//计数器内记的值变为0
	     Distance = high_time *0.017;
			if(Distance<20)
		{
			stop_ref();
		}
				capture_Cnt = 0;
			  overload_Cnt = 0;
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
				HAL_TIM_IC_Start_IT(&htim2,TIM_CHANNEL_1);////在中断模式下启动TIM Input Capture测量。
			  break;
		}
	}
}
void HAL_UART_IDLECallback(UART_HandleTypeDef *huart)
{
	
	if(huart->Instance==USART1)
 {
    HAL_UART_DMAStop(&huart1);                                                     //停止本次DMA传输
    
    uint8_t data_length  = BUFFER_SIZE -   __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);
	  

	switch(receive_buff[0])
			{
				case 'f':forward_ref();break;
				case 'b':back_ref();break;
				case 's':stop_ref();break;
				case 'l':left_ref();break;
				case 'r':right_ref();break;		
				 receive_buff[0] = 0;
			}
    printf("Receive Data(length = %d): ",data_length);

    HAL_UART_Transmit(&huart1,(uint8_t *)receive_buff,data_length,1000);                       //测试函数：将接收到的数据打印出去
    printf("\r\n");

    memset(receive_buff,0,data_length);                                            //清零接收缓冲区
    data_length = 0;
    HAL_UART_Receive_DMA(&huart1, (uint8_t*)receive_buff, 255);                    //重启开始DMA传输 每次255字节数据
   
 }
}

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
