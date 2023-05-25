#include "MOTOR.h"
#include "tim.h"
//#include "usart.h"
//#include "stdio.h"
//uint8_t RecData;
//uint8_t Recbuf[10];
//void CONTROL()
//{
//			
//  }
	
void LEFT()
{
	      __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,0);
		    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,12000); 
	     	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,0);
		    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,0);
	
	      __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1,0);
		    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2,0); 
	      __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3,0);
		    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4,12000);
	
}

void RIGHT()
{
	      __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,0);
		    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,0); 
	     	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,0);
		    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,12000);
	
	      __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1,12000);
		    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2,0); 
	      __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3,0);
		    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4,0);
	
}

void DOWN()
{
	      __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,12000);
		    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,0); //右前轮后转
				__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,12000);
		    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,0);//左前轮后转
		
        __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1,0);
		    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2,12000); //左后轮后转
				__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3,0);
		    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4,12000);//右后轮后转
}
void UP()
{
	      __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,0);
		    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,12000); 
				__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,0);
		    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,12000);
		
        __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1,12000);
		    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2,0); 
				__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3,12000);
		    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4,0);
	
}
void OK()
{
	      __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1,0);
		    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2,0); 
				__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3,0);
		    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4,0);
		
        __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1,0);
		    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2,0); 
				__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3,0);
		    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4,0);
}

	