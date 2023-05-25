#include "TDOA.h"
#include "exti.h"
#include "usart.h"
#include "stdio.h"
_TDOA TDOA_S;

void TDOA_Init(_TDOA *TDOA_S)
{
	TDOA_S->L=90;
	TDOA_S->a1=0;
	TDOA_S->r21=0;
	TDOA_S->r31=0;
	TDOA_S->r41=0;
	TDOA_S->x=0;
	TDOA_S->y=0;
	TDOA_S->a2=0;
	
}



void TDOA_Get_distanceANDangle(_TDOA *TDOA_S)
{
	TDOA_S->r21=(MIT2_S.mit_count-MIT1_S.mit_count)*0.34;
	TDOA_S->r31=(MIT3_S.mit_count-MIT1_S.mit_count)*0.34;
	TDOA_S->r41=(MIT4_S.mit_count-MIT1_S.mit_count)*0.34;
	
	TDOA_S->a1=(TDOA_S->r31*TDOA_S->r31 - TDOA_S->r21*TDOA_S->r21 - TDOA_S->r41*TDOA_S->r41)/(TDOA_S->r21 + TDOA_S->r41 - TDOA_S->r31);
	
	TDOA_S->x=(TDOA_S->r21 * TDOA_S->r21 + TDOA_S->r21 -TDOA_S->a1)/(4*TDOA_S->L);
	
	TDOA_S->y=(TDOA_S->r41 * TDOA_S->r41 + TDOA_S->r41 -TDOA_S->a1)/(4*TDOA_S->L);
	
	printf("r21:%lf\r\n",TDOA_S->r21);
	printf("r31:%lf\r\n",TDOA_S->r31);
	printf("r41:%lf\r\n",TDOA_S->r41);
	printf("a1:%lf\r\n",TDOA_S->a1);
	printf("x:%lf\r\n",TDOA_S->x);
	printf("y:%lf\r\n",TDOA_S->y);
}















