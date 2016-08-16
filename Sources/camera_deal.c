
//******************author:tan**************************************************
//******************input:�������� *********************************************
//******************output:�ж�ֱ�����������ת�ķ���ת�ĽǶ�*****************
#include "camera_deal.h"

#define square_c  50


unsigned char angle=0;        //ת�ĽǶ�
unsigned char judge_line;     //�ж�ֱ�����������1Ϊֱ��
unsigned char big_curve_c;    //�������־ 
unsigned int square=0;
unsigned int base;              //��׼
unsigned char slow_speed_flag;  //���ٱ�־
unsigned char left_flag;       //��ת��־
unsigned char right_flag;      //��ת��־
unsigned char turn_flag;       //ת���־
unsigned char far_temp;
unsigned char mid_temp;
unsigned char big_curve_turn_flag;


//************���ã�ȡ����ֵ****************************************************
//************���룺��Զ�˵����ģ�a�� ���Ͻ��˵����ģ�b������i �����жϵķ���***
//************����� ��i ���ߵ�б�ʺͷ���*************************************** 
unsigned int Abs(unsigned int a,unsigned int b)//Absolute value
{
	unsigned int value;
	
	if(a<=b) 
	{
	    value=b-a;      //����ֵ 
	    left_flag = 1;
	    right_flag = 0;
  }
	else 
	{
	    value=a-b;
	    right_flag = 1;
	    left_flag =0;
	}
	
	return(value);
}

/**************************************************************************
                            ����ƫ����ƫת��
***************************************************************************
���ܣ�ʹ�ò������ƫת��*/
unsigned char angle_x1(unsigned int x) 
{
  const unsigned char angle_temp[6]={11,13,14,16,18,19};
  return (angle_temp[x-8]);
}

unsigned char angle_x2(unsigned int x) 
{
  const unsigned char angle_temp2[7]={19,21,24,28,33,37,42};
  return (angle_temp2[x]);
}

//***********ͼ�������*******************************************************
//***********���룺��������*****************************************************
//***********���: �ж�ֱ�����������ת�ķ���ת�ĽǶ�*************************
void c_deal(void)
{
   unsigned int offset;
   unsigned char angle_tp;

   //�� �� ���ߵķ�����ͬ�����Խ��˵ĽǶȾ������ת�ǣ������Խ��˵���Զ�˵�����߽ǶȾ������ 
   offset = Abs(Image_Center[middle],base);
   angle_tp = angle_x1(offset);
   
   
   if (angle_tp <= 3)             
   {
      judge_line = 1;                         //straightawayֱ�� 
      slow_speed_flag = 0;
   } 
   else
   {
      if (left_flag == 1)
        turn_flag = 1;                     //turn_flag=1  ��ת
      else 
      {
        if (right_flag == 1)
           turn_flag = 0;                  //turn_flag=0  ��ת
      }
      
      judge_line = 0;                         //curve
      
      angle = angle_tp;
   }
}

//****************************������ж�**************************************** 
void big_curve(void) 
{
    unsigned char i,j,k,edge,angle1,next_angle=0,big_angle;
    unsigned int x,average=0,sum=0,valve_temp0=0, valve_temp1=0,valve_temp2=0;
    unsigned int offset1,valve_temp3=0,base_temp;
    
    for (i=ROW-1; i>(ROW-6); i--)
	     sum += Image_Center[i];
	  base_temp = sum/5;                //��ǰ���е�ƽ��ֵΪ��׼
	  
	  if (base_temp>=25 && base_temp<=55)
	     base = base_temp;
	  else
	     base = (40+base_temp)/2;
	  
	  for(x=0; x<ROW; x++)
	    {
	    average += Image_Center[x];
	    } 
    average = average/ROW;          //��ƽ��ֵ
    
    for(x=0; x<ROW; x++)
      {
      	square += ((average-Image_Center[x])*(average-Image_Center[x]));
      }  
    square = square/ROW;            //�������
    
    if(square > square_c)
    {
   	  big_curve_c = 1;      //�ж�Ϊ����� ������
   	  judge_line = 0;
   	  slow_speed_flag = 1;
   	  
   	  for(k=1; k<ROW; k++)              //ȡԶ������
   	  {
   	    valve_temp3 = Abs(Image_Center[k],base);
   	    if (valve_temp3>=9 && valve_temp3<=12) 
   	    {
   	      edge = k;
   	      far_temp = edge;
   	      break;
   	    }
   	  }
   	  
   	  for(j=35; j>edge; j--)               //ȡ�м�����
   	  {  
   	    valve_temp0 = Abs(Image_Center[j],base);
 
   	    if (valve_temp0 > 2)
   	    {
   	       mid_temp = j-1;
   	       break;
   	    } 
   	  } /*
   	  if (big_curve_turn_flag == 1) 
   	  {
   	     big_curve_turn_flag =0;
   	     angle = next_angle;
   	  }
   	  */
   	  
   	  
   	  if (far_temp>= 14 && far_temp<=18) 
   	  {
   	    offset1 = Abs(far_temp, mid_temp); 
   	    angle1 = angle_x2(offset1);
   	    judge_line = 0;
   	    big_curve_turn_flag =1;
   	    big_angle = angle1/2;
   	    next_angle = angle1/2;
   	    
   	    if (left_flag == 1)
           turn_flag = 1;                     //turn_flag=1  ��ת
        else 
        {
        if (right_flag == 1)
           turn_flag = 0;                  //turn_flag=0  ��ת
        }
        angle = big_angle;
   	  } 
   	  else
   	    if (far_temp < 14) 
   	    {
   	       judge_line = 1;
   	    }
    } 
    else
  	{
	     big_curve_c = 0; 
       c_deal(); 
    }
}



