#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "Nixie.h"
#include "OLED.h"


uint8_t KeyNum;
int8_t i = 0;

int main(void)
{
	LED_Init();
	Key_Init();
	OLED_Init();
	Nixie_Init();
	
	
	while (1)
	{
		GetNum(i);
		KeyNum = Key_GetNum();
		OLED_ShowNum(1, 1, i, 2);
		
		if(KeyNum == 1)
		{
			i++;
			if(i == 10)
				i = 0;
			OLED_ShowNum(1, 1, i, 2);
			GetNum(i);
		}
		if(KeyNum == 2)
		{
			i--;
				if(i == -1)
				i = 9;
			OLED_ShowNum(1, 1, i, 2);
			GetNum(i);
		}


//		GetNum(1);
//		Clean_Num();
		

	}
}
