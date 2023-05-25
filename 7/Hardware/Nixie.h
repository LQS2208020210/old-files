#ifndef __NIXIE_H
#define __NIXIE_H


void Nixie_Init(void);
void GetNum(unsigned int Num);
void Clean_Num(void);


#define A		GPIO_SetBits(GPIOB, GPIO_Pin_15)
#define B		GPIO_SetBits(GPIOA, GPIO_Pin_8)
#define C		GPIO_SetBits(GPIOA, GPIO_Pin_9)
#define D		GPIO_SetBits(GPIOA, GPIO_Pin_10)
#define E		GPIO_SetBits(GPIOA, GPIO_Pin_11)
#define F		GPIO_SetBits(GPIOA, GPIO_Pin_12)
#define G		GPIO_SetBits(GPIOB, GPIO_Pin_5)


#define Empty1		GPIO_ResetBits(GPIOB, GPIO_Pin_15)
#define Empty2		GPIO_ResetBits(GPIOA, GPIO_Pin_8)
#define Empty3		GPIO_ResetBits(GPIOA, GPIO_Pin_9)
#define Empty4		GPIO_ResetBits(GPIOA, GPIO_Pin_10)
#define Empty5		GPIO_ResetBits(GPIOA, GPIO_Pin_11)
#define Empty6		GPIO_ResetBits(GPIOA, GPIO_Pin_12)
#define Empty7		GPIO_ResetBits(GPIOB, GPIO_Pin_5)


#endif
