#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"


void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//开启时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				//上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0;		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
	{
		Delay_ms(10);
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
		{LED1_ON();}
		Delay_ms(10);
		LED1_OFF();
		KeyNum = 1;
	}
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0)
	{
		Delay_ms(10);
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0)
		{LED2_ON();}
		Delay_ms(10);
		LED2_OFF();
		KeyNum = 2;
	}
	
	return KeyNum;
}
