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
	TDOA_S->r21=(t2-t1)*0.34;//2和1的时间差
	TDOA_S->r31=(t3-t1)*0.34;//3和1的时间差
	TDOA_S->r41=(t4-t1)*0.34;//4和1的时间差
	TDOA_S->r42=(t4-t2)*0.34;//4和2的时间差
	TDOA_S->r12=(t1-t2)*0.34;//1和2的时间差
	TDOA_S->r13=(t1-t3)*0.34;//1和3的时间差
	TDOA_S->r14=(t1-t4)*0.34;//1和4的时间差
	TDOA_S->r24=(t2-t4)*0.34;//2和4的时间差
	TDOA_S->r23=(t2-t3)*0.34;//2和3的时间差
	TDOA_S->r32=(t3-t2)*0.34;//3和2的时间差
	TDOA_S->r34=(t3-t4)*0.34;//3和4的时间差
	TDOA_S->r43=(t4-t3)*0.34;//4和3的时间差

	
	TDOA_S->c1 = 90 * pow(2.0, 0.5);//对角线的长度
	TDOA_S->c2 = 90 * pow(2.0, 0.5);//对角线的长度

	TDOA_S->a1=fabs((t3-t1)*0.34/2);//双曲线a1的长度
	TDOA_S->a2=fabs((t4-t2)*0.34/2);//双曲线a2的长度
	
	TDOA_S->b1 = pow(pow(TDOA_S->c1, 2.0) - pow(TDOA_S->a1, 2.0), 0.5);//双曲线b1的长度
	TDOA_S->b2 = pow(pow(TDOA_S->c2, 2.0) - pow(TDOA_S->a2, 2.0), 0.5);//双曲线b2的长度
	
	//求得x的平方与y的平方
	TDOA_S->dx = pow(TDOA_S->a1, 2.0) * pow(TDOA_S->b2, 2.0) * (pow(TDOA_S->a2, 2.0) + pow(TDOA_S->b1, 2.0)) / ((pow(TDOA_S->b1, 2.0) * pow(TDOA_S->b2, 2.0) - pow(TDOA_S->a1, 2.0) * pow(TDOA_S->a2, 2.0)));
	TDOA_S->dy = pow(TDOA_S->a2, 2.0) * pow(TDOA_S->b1, 2.0) * (pow(TDOA_S->a1, 2.0) + pow(TDOA_S->b2, 2.0)) / ((pow(TDOA_S->b1, 2.0) * pow(TDOA_S->b2, 2.0) - pow(TDOA_S->a1, 2.0) * pow(TDOA_S->a2, 2.0)));

	
	/*根据时间差对x，y进行正负判断*/
	
	/*第一象限*/
    if(TDOA_S->r31>0&&TDOA_S->r42>0)
{
	TDOA_S->dx=pow(TDOA_S->dx,0.5);
	TDOA_S->dy=pow(TDOA_S->dy,0.5);
}
	/*第二象限*/
	else if(TDOA_S->r31<0&&TDOA_S->r42>0)
{
	TDOA_S->dx=-pow(TDOA_S->dx,0.5);
	TDOA_S->dy=pow(TDOA_S->dy,0.5);
}
	/*第四象限*/
	else if(TDOA_S->r31>0&&TDOA_S->r42<0)
{
	TDOA_S->dx=pow(TDOA_S->dx,0.5);
	TDOA_S->dy=-pow(TDOA_S->dy,0.5);
}
	/*第三象限*/
	else if(TDOA_S->r31<0&&TDOA_S->r42<0)
{
	
	TDOA_S->dy=-pow(TDOA_S->dy,0.5);
	TDOA_S->dx=-pow(TDOA_S->dx,0.5);
}
	/*转换坐标*/
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















