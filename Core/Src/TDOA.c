#include "TDOA.h"

#include "usart.h"
#include "stdio.h"
#include "math.h"
#include "oled.h"
extern int t1,t2,t3,t4;
_TDOA TDOA_S;
extern uint8_t A[3];
extern uint8_t B[3];
float x1,y1;
void TDOA_Init(_TDOA *TDOA_S)
{
	TDOA_S->L=90;
	TDOA_S->r31=0;
	TDOA_S->r42=0;
	TDOA_S->r13=0;
	TDOA_S->r24=0;
	TDOA_S->r32=0;
	TDOA_S->r23=0;
	TDOA_S->r14=0;
	TDOA_S->r41=0;
	TDOA_S->r12=0;
	TDOA_S->r21=0;
	TDOA_S->r34=0;
	TDOA_S->r43=0;
	TDOA_S->c1=0;
	TDOA_S->c2=0;
	TDOA_S-> b1=0;
	TDOA_S-> b2=0;
	TDOA_S->a1=0;
	TDOA_S->a2=0;
	
}



void TDOA_Get_distanceANDangle(_TDOA *TDOA_S)
{
	TDOA_S->r21=(t2-t1)*0.34;//2��1��ʱ���
	TDOA_S->r31=(t3-t1)*0.34;//3��1��ʱ���
	TDOA_S->r41=(t4-t1)*0.34;//4��1��ʱ���
	TDOA_S->r42=(t4-t2)*0.34;//4��2��ʱ���
	TDOA_S->r12=(t1-t2)*0.34;//1��2��ʱ���
	TDOA_S->r13=(t1-t3)*0.34;//1��3��ʱ���
	TDOA_S->r14=(t1-t4)*0.34;//1��4��ʱ���
	TDOA_S->r24=(t2-t4)*0.34;//2��4��ʱ���
	TDOA_S->r23=(t2-t3)*0.34;//2��3��ʱ���
	TDOA_S->r32=(t3-t2)*0.34;//3��2��ʱ���
	TDOA_S->r34=(t3-t4)*0.34;//3��4��ʱ���
	TDOA_S->r43=(t4-t3)*0.34;//4��3��ʱ���

	
	TDOA_S->c1 = 90 * pow(2.0, 0.5);//�Խ��ߵĳ���
	TDOA_S->c2 = 90 * pow(2.0, 0.5);//�Խ��ߵĳ���

	TDOA_S->a1=fabs((t3-t1)*0.34/2);//˫����a1�ĳ���
	TDOA_S->a2=fabs((t4-t2)*0.34/2);//˫����a2�ĳ���
	
	TDOA_S->b1 = pow(pow(TDOA_S->c1, 2.0) - pow(TDOA_S->a1, 2.0), 0.5);//˫����b1�ĳ���
	TDOA_S->b2 = pow(pow(TDOA_S->c2, 2.0) - pow(TDOA_S->a2, 2.0), 0.5);//˫����b2�ĳ���
	
	//���x��ƽ����y��ƽ��
	TDOA_S->dx = pow(TDOA_S->a1, 2.0) * pow(TDOA_S->b2, 2.0) * (pow(TDOA_S->a2, 2.0) + pow(TDOA_S->b1, 2.0)) / ((pow(TDOA_S->b1, 2.0) * pow(TDOA_S->b2, 2.0) - pow(TDOA_S->a1, 2.0) * pow(TDOA_S->a2, 2.0)));
	TDOA_S->dy = pow(TDOA_S->a2, 2.0) * pow(TDOA_S->b1, 2.0) * (pow(TDOA_S->a1, 2.0) + pow(TDOA_S->b2, 2.0)) / ((pow(TDOA_S->b1, 2.0) * pow(TDOA_S->b2, 2.0) - pow(TDOA_S->a1, 2.0) * pow(TDOA_S->a2, 2.0)));

	
	/*����ʱ����x��y���������ж�*/
	
	/*��һ����*/
    if(TDOA_S->r31>0&&TDOA_S->r42>0)
{
	TDOA_S->dx=pow(TDOA_S->dx,0.5);
	TDOA_S->dy=pow(TDOA_S->dy,0.5);
}
	/*�ڶ�����*/
	else if(TDOA_S->r31<0&&TDOA_S->r42>0)
{
	TDOA_S->dx=-pow(TDOA_S->dx,0.5);
	TDOA_S->dy=pow(TDOA_S->dy,0.5);
}
	/*��������*/
	else if(TDOA_S->r31>0&&TDOA_S->r42<0)
{
	TDOA_S->dx=pow(TDOA_S->dx,0.5);
	TDOA_S->dy=-pow(TDOA_S->dy,0.5);
}
	/*��������*/
	else if(TDOA_S->r31<0&&TDOA_S->r42<0)
{
	
	TDOA_S->dy=-pow(TDOA_S->dy,0.5);
	TDOA_S->dx=-pow(TDOA_S->dx,0.5);
}
	/*ת������*/
    /*x1=TDOA_S->dx;
    y1=TDOA_S->dy;*/
if(TDOA_S->b1*TDOA_S->b2>TDOA_S->a1*TDOA_S->a2)
{
	
		TDOA_S->y = pow(2, 0.5)/2*(TDOA_S->dx+TDOA_S->dy);
		TDOA_S->x = pow(2, 0.5)/2*(TDOA_S->dx-TDOA_S->dy);
}
		
	printf("x:%.2lf\r\n",TDOA_S->x);
	printf("y:%.2lf\r\n",TDOA_S->y);

  A[0] = TDOA_S->x;
  B[0] = TDOA_S->y;

            OLED_Clear(); 
	          OLED_ShowString(0,0,A,sizeof(A));
            OLED_ShowString(50,0,B,sizeof(B));


   }















