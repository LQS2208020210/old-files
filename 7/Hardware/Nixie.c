#include "stm32f10x.h"                  // Device header
#include "Nixie.h"



void Nixie_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15| GPIO_Pin_5;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	

}
	

void GetNum(uint8_t Num)
{
	
	switch (Num)
	{
	case 0:
		Clean_Num();
		A;B;C;D;E;F;
		break;
	case 1:
		Clean_Num();
		B;C;
		break;
	case 2:
		Clean_Num();		
		A;B;D;E;G;
		break;
	case 3:
		Clean_Num();
		A;B;C;D;G;
		break;
	case 4:
		Clean_Num();
		B;C;F;G;
		break;
	case 5:
		Clean_Num();
		A;C;D;F;G;
		break;
	case 6:
		Clean_Num();
		A;C;D;E;F;G;
		break;
	case 7:
		Clean_Num();
		A;B;C;
		break;
	case 8:
		Clean_Num();
		A;B;C;D;E;F;G;
		break;
	case 9:
		Clean_Num();
		A;B;C;D;F;G;
		break;
	}
}

void Clean_Num(void)
{
	Empty1;Empty2;Empty3;Empty4;Empty5;Empty6;Empty7;
}
