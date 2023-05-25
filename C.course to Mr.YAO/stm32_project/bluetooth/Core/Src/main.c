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
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include <string.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
void Usart_SendString(uint8_t *str)//发送字符串
{
	uint32_t k = 0;
	do
	{
		HAL_UART_Transmit(&huart3,(uint8_t *)(str + k),1,1000);
		k++;
	}while(*(str + k) !='\0');
}
int fputc(int ch,FILE *f)
{
	uint8_t temp[1] = {ch};
	HAL_UART_Transmit(&huart3, temp, 1,1000);
	return ch;
}
int fgetc(FILE *f)
{
	uint8_t ch=0;
	HAL_UART_Receive(&huart3 ,(uint8_t *)&ch,1,1000);
	return ch;
}
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;
extern UART_HandleTypeDef huart1;

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t receive_buff[255];
  uint8_t flag[2];
	uint8_t flag1[1];
	uint8_t data[20];
	uint8_t temp[] = {0};
	uint32_t Buffer[16] = {0X00000000,0X11111111,0X022222222,0X033333333,0X044444444,0X055555555,0X066666666,0X077777777,0X88888888,0X99999999,0XAAAAAAAA,0XBBBBBBBB,0XCCCCCCCC,0XDDDDDDDD,0XEEEEEEEE,0XFFFFFFFF};
	uint32_t Buf[16];
	
	uint8_t Buffer_1[8] = {0X00,0X01,0X02,0X03,0X04,0X05,0X06,0X07};
	uint8_t Buf_1[8];
	 uint8_t Buf_2[10],a;
#define  BUFFER_SIZE  (255)
	#define RXBUFFERSIZE  1024
uint8_t aRxBuffer[RXBUFFERSIZE];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
 void delay(int m)
 {
	 while(m)
	 {
	    m--;
	 }
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
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
//		HAL_UART_Receive_IT(&huart3,flag,1);
   __HAL_UART_ENABLE_IT(&huart3,UART_IT_IDLE);//空闲中断使能 
	 HAL_UART_Receive_DMA(&huart3, (uint8_t*)receive_buff, 255);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		
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
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_pin)
{
	if(GPIO_PIN_3 == GPIO_pin)
	{
		
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3) == GPIO_PIN_RESET)
		{
			delay(100);//按键消抖
			 
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3) == GPIO_PIN_RESET)
		{
			HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
			
		}
		}
		
	}
}


// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	  #if 1  //条件编译
//		if(huart->Instance==USART3)
//		{
//      HAL_UART_Receive(&huart3, data, 4, 1000);//串口接收函数   不要点发送新行
//			HAL_UART_Transmit(&huart3,data, 4,1000);//串口发送函数
//			
//		}
//		printf("\r\nstm32\r\n");
//	
//		HAL_UART_Receive_IT(&huart3,flag,1);//串口中断服务函数初始化  这个初始化函数吃发送的数据的前1个  剩下的留给接收函数接收
//		#endif  //条件编译
//	}


void HAL_UART_IDLECallback(UART_HandleTypeDef *huart)
{
	
	if(huart->Instance==USART3)
 {
    HAL_UART_DMAStop(&huart3);                                                     //停止本次DMA传输
    
    uint8_t data_length  = BUFFER_SIZE -   __HAL_DMA_GET_COUNTER(&hdma_usart3_rx);
    
    printf("Receive Data(length = %d): ",data_length);

    HAL_UART_Transmit(&huart3,(uint8_t *)receive_buff,data_length,1000);                       //测试函数：将接收到的数据打印出去
    printf("\r\n");

    memset(receive_buff,0,data_length);                                            //清零接收缓冲区
    data_length = 0;
    HAL_UART_Receive_DMA(&huart3, (uint8_t*)receive_buff, 255);                    //重启开始DMA传输 每次255字节数据
   
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
