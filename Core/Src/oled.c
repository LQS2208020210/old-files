#include "oled.h"
#include "oledfont.h"

//������������
//uint8_t **Hzk;

//��ʼ������
uint8_t CMD_Data[]={
0xAE, 0x00, 0x10, 0x40, 0x81, 0xCF, 0xA1, 0xC8, 0xA6, 0xA8, 0x3f,
					
0xD3, 0x00, 0xD5, 0x80, 0xD9, 0xF1, 0xDA, 0x12, 0xDB, 0x40, 0x20,
					
0x02, 0x8D, 0x14, 0xA4, 0xA6, 0xAF};
void WriteCmd()
{
	/*uint8_t i = 0;
	for(i=0; i<28; i++){
		HAL_I2C_Mem_Write(&hi2c1 ,0x78,0x00,I2C_MEMADD_SIZE_8BIT,CMD_Data+i,2,0x100);
	}*/
OLED_WR_CMD(0xAE);//--turn off oled panel
	OLED_WR_CMD(0x00);//---set low column address
	OLED_WR_CMD(0x10);//---set high column address
	OLED_WR_CMD(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_CMD(0x81);//--set contrast control register
	OLED_WR_CMD(0xCF);// Set SEG Output Current Brightness
	OLED_WR_CMD(0xA1);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_WR_CMD(0xC8);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
	OLED_WR_CMD(0xA6);//--set normal display
	OLED_WR_CMD(0xA8);//--set multiplex ratio(1 to 64)
	OLED_WR_CMD(0x3f);//--1/64 duty
	OLED_WR_CMD(0xD3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_CMD(0x00);//-not offset
	OLED_WR_CMD(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_WR_CMD(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_CMD(0xD9);//--set pre-charge period
	OLED_WR_CMD(0xF1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_CMD(0xDA);//--set com pins hardware configuration
	OLED_WR_CMD(0x12);
	OLED_WR_CMD(0xDB);//--set vcomh
	OLED_WR_CMD(0x40);//Set VCOM Deselect Level
	OLED_WR_CMD(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_CMD(0x02);//
	OLED_WR_CMD(0x8D);//--set Charge Pump enable/disable
	OLED_WR_CMD(0x14);//--set(0x10) disable
	OLED_WR_CMD(0xA4);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_CMD(0xA6);// Disable Inverse Display On (0xa6/a7) 
	OLED_Clear();
	OLED_WR_CMD(0xAF);
}
//ˮƽ����
void OLED_ver_scroll()
{
  OLED_WR_CMD(0x2e);//�ع���
  OLED_WR_CMD(0x27);//29���ң�2a����
  OLED_WR_CMD(0x00);//A:���ֽ�
  OLED_WR_CMD(0x02);//B:ˮƽ��ʼҳ
  OLED_WR_CMD(0x07);//C:ˮƽ�����ٶ�
  OLED_WR_CMD(0x03);//D:ˮƽ����ҳ
  OLED_WR_CMD(0x00);//E:ÿ�δ�ֱ����λ��
  OLED_WR_CMD(0xFF);//E:ÿ�δ�ֱ����λ��
  OLED_WR_CMD(0x2f);//������
  
}
//���豸д��������
void OLED_WR_CMD(uint8_t cmd)
{
	HAL_I2C_Mem_Write(&hi2c1 ,0x78,0x00,I2C_MEMADD_SIZE_8BIT,&cmd,1,0x100);
}
//���豸д����
void OLED_WR_DATA(uint8_t data)
{
	HAL_I2C_Mem_Write(&hi2c1 ,0x78,0x40,I2C_MEMADD_SIZE_8BIT,&data,1,0x100);
}
//��ʼ��oled��Ļ
void OLED_Init(void)
{ 	
	HAL_Delay(500);
	WriteCmd();
}
//����size12 size16Ҫ�����У������������������
void OLED_Clear()
{
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_CMD(0xb0+i);
		OLED_WR_CMD (0x00); 
		OLED_WR_CMD (0x10); 
		for(n=0;n<128;n++)
			OLED_WR_DATA(0x00);
	} 
}
//����
void OLED_Clearrow(uint8_t i)
{
	  uint8_t n;
	  OLED_WR_CMD(0xb0+i);
		OLED_WR_CMD (0x20); 
		OLED_WR_CMD (0x00); 
		for(n=0;n<128;n++)
			OLED_WR_DATA(0x00);
}
//����OLED��ʾ    
void OLED_Display_On(void)
{
	OLED_WR_CMD(0X8D);  //SET DCDC����
	OLED_WR_CMD(0X14);  //DCDC ON
	OLED_WR_CMD(0XAF);  //DISPLAY ON
}
//�ر�OLED��ʾ     
void OLED_Display_Off(void)
{
	OLED_WR_CMD(0X8D);  //SET DCDC����
	OLED_WR_CMD(0X10);  //DCDC OFF
	OLED_WR_CMD(0XAE);  //DISPLAY OFF
}		   			 
void OLED_Set_Pos(uint8_t x, uint8_t y) 
{ 	
	OLED_WR_CMD(0xb0+y);
	OLED_WR_CMD(((x&0xf0)>>4)|0x10);
	OLED_WR_CMD(x&0x0f);
} 
 
void OLED_On(void)  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_CMD(0xb0+i);    //����ҳ��ַ��0~7��
		OLED_WR_CMD(0x00);      //������ʾλ�á��е͵�ַ
		OLED_WR_CMD(0x10);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)
			OLED_WR_DATA(0x00); 
	} //������ʾ
}
unsigned int oled_pow(uint8_t m,uint8_t n)
{
	unsigned int result=1;	 
	while(n--)result*=m;    
	return result;
}

//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ				 
//size:ѡ������ 16/12 
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//�õ�ƫ�ƺ��ֵ			
		if(x>128-1){x=0;y=y+2;}
		if(Char_Size <=16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_DATA(F8x16[c*16+i]);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_DATA(F8x16[c*16+i+8]);
			}
			else {	
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_WR_DATA(F6x8[c][i]);
				
			}
}
 //��ʾ2������
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);	 		  
void OLED_ShowNum(uint8_t x,uint8_t y,unsigned int num,uint8_t len,uint8_t size2)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 
//��ʾһ���ַ��Ŵ�
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}

unsigned char Hzk[][16]=
{

 {0x04,0xE4,0xA4,0xA4,0xBF,0xA4,0xA6,0xE4,0x48,0x48,0xFF,0x48,0x68,0x4C,0x08,0x00},
 {0x10,0x13,0x12,0x12,0xFE,0x12,0x12,0x1B,0x12,0x02,0xFF,0x02,0x12,0x22,0x1E,0x00},

 {0x00,0x80,0xC0,0xBC,0x84,0x84,0x84,0xF4,0x82,0x82,0x83,0x82,0x80,0xC0,0x80,0x00},
 {0x00,0x40,0x20,0x10,0x0C,0x40,0x80,0x7F,0x00,0x00,0x04,0x08,0x30,0x60,0x00,0x00},

 {0x00,0xFE,0x22,0xFE,0x00,0xFE,0x22,0xFE,0x00,0xFC,0x06,0x55,0x84,0x7E,0x04,0x00},
 {0x40,0x3F,0x02,0x3F,0x40,0x3F,0x42,0x7F,0x10,0x13,0x12,0x12,0x5A,0x92,0x7E,0x00},
};
//��ʾ����
//hzk ��ȡģ����ó�������
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no)
{      			    
	uint8_t t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_DATA(Hzk[2*no][t]);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_DATA(Hzk[2*no+1][t]);
				adder+=1;
      }					
}
