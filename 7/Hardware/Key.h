#ifndef __KEY_H
#define __KEY_H

void Key_Init(void);
uint8_t Key_GetNum(void);


#define KEY1	GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)
#define KEY2	GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)

#endif
