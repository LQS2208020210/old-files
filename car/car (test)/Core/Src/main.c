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
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "MOTOR.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
uint8_t RecData;
uint8_t Recbuf[10];
uint8_t IS_FIRST_CAPTURED = 0;
uint32_t IC_Val1=0;
uint32_t IC_Val2=0;
uint32_t Difference=0;
uint16_t Distance=0;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
uint16_t HCSR04_Read(void );
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
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
  printf("Are you ready?\r\n");
  HAL_TIM_Base_Start(&htim2);	
	HAL_TIM_Base_Start(&htim3);
	HAL_TIM_Base_Start(&htim4);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
//		printf("%d\n%d\n", IC_Val1,IC_Val2);
//		printf ("distance = %d cm \r\n",HCSR04_Read());	
//	 __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1,500);
//		HAL_Delay(1000);
		while(1)
		{ 
	
			HCSR04_Read();
		printf ("distance = %d cm \r\n",Distance);
		if(Distance<15)
			OK();
	else
					DOWN();
	}
			 if(HAL_UART_Receive(&huart1,Recbuf,5,100)==HAL_OK)
		{
        HAL_UART_Transmit(&huart1,Recbuf,5,100);
		}
	if(scanf("%c",&RecData)==1)
			{
				if(RecData=='U')
			{
				UP();
       printf("UP");				
			}
			  if(RecData=='D')
				{
					DOWN();
				printf("DOWN");
				}
				 if(RecData=='O')
				 {
					 OK();
				printf("STOP");
				 }
				 if(RecData=='R')
				 {
					 RIGHT();
				printf("RIGHT");
				 }if(RecData=='L')
				 {
					 LEFT();
				printf("LEFT");
				 }
	  }	
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
int fputc(int ch,FILE *f)
{
	HAL_UART_Transmit(&huart1,(uint8_t*)&ch,1,HAL_MAX_DELAY);
	return ch;
	
}
int fgetc(FILE *f)
{
	uint8_t ch;
	HAL_UART_Receive(&huart1,(uint8_t*)&ch,1,HAL_MAX_DELAY);
		return ch;
	
}
void delay_us(uint16_t us)
{
	__HAL_TIM_SET_COUNTER (&htim4 ,10);
	while(__HAL_TIM_GET_COUNTER (&htim4 )<us );
}

uint16_t HCSR04_Read(void )
{
	HAL_GPIO_WritePin (TRIG_GPIO_Port ,TRIG_Pin ,GPIO_PIN_RESET );
	delay_us (2);
	HAL_GPIO_WritePin (TRIG_GPIO_Port ,TRIG_Pin ,GPIO_PIN_SET );
	delay_us (12);
	HAL_GPIO_WritePin (TRIG_GPIO_Port ,TRIG_Pin ,GPIO_PIN_RESET );	
	__HAL_TIM_ENABLE_IT (&htim4 ,TIM_IT_CC3 );
//	HAL_TIM_IC_Start_IT(&htim2,TIM_CHANNEL_3);	
	HAL_Delay (100);
	return Distance ;
}
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim ->Channel ==HAL_TIM_ACTIVE_CHANNEL_3 )
	{
		if(IS_FIRST_CAPTURED ==0)
		{
			IS_FIRST_CAPTURED =1;
			IC_Val1 =	HAL_TIM_ReadCapturedValue (&htim4 ,TIM_CHANNEL_3 );//读取当前值
			__HAL_TIM_SET_CAPTUREPOLARITY (&htim4 ,TIM_CHANNEL_3 ,TIM_INPUTCHANNELPOLARITY_FALLING );//下降沿
		}	
		else if (IS_FIRST_CAPTURED ==1)
		{
			IS_FIRST_CAPTURED =0;
			IC_Val2 =	HAL_TIM_ReadCapturedValue (&htim4 ,TIM_CHANNEL_3 );
			__HAL_TIM_SET_COUNTER (&htim4 ,0);
			
			if(IC_Val1 <IC_Val2 )
			{
				Difference=IC_Val2 -IC_Val1 ;
			}
			else if(IC_Val1 >IC_Val2)
			{
				Difference=0xffff- IC_Val1 +IC_Val2 ;
			}
		Distance = Difference *0.017;
		__HAL_TIM_SET_CAPTUREPOLARITY (&htim4 ,TIM_CHANNEL_3 ,TIM_INPUTCHANNELPOLARITY_RISING );//上升沿
		__HAL_TIM_DISABLE_IT (&htim4 ,TIM_IT_CC3 );
//			HAL_TIM_IC_Stop_IT(&htim2,TIM_CHANNEL_3);
	
		 }
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
