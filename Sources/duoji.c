#include "duoji.h"
#include <hidef.h>   //common defines and macros 
#include "derivative.h"   //derivative-specific definitions                    

unsigned int average=0,average_temp;

void duoji_driver (void)  //dtyΪ�����PWMDTY��ֵ
{
   unsigned int dty,i,j=0;
   
  
   unsigned int total=0;
   
   unsigned int steer;
   
   for(i=0;i<ROW;i+=4)
   {
      //if(Image_Center[i]!=0)
      //{
        //j++;
        total+=Image_Center[i];
     // }
   }
   if(Image_Center[39]==0 && Image_Center[38]==0)
   {
    average = average_temp;
   }
   else
     {
      average=total / 10;
      average_temp = average;
     }
   
   if(average>40)
   {
       i=9/8;
       j=average-40;
       steer=i*j;
       dty=1500 - 11*steer;
       if(dty<1005)
          dty=1005;
   } 
   else
   {
       i=9/8;
       j=40-average;
       steer=i*j;
       dty=1500 + 11*steer;
       if(dty>1995)
          dty=1995;
   }
   
   
   
  /* if(judge_line == 1)                      
   {
     dty=1500;//judge_line����1ʱΪֱ�ߣ����ת��Ϊ0��
   }
   else 
      if(turn_flag == 0)
        { 
        dty= 1500 - 11*angle;    //����ת
        
        if(dty<1005)
          dty=1005;
        }
      else            //����ת���Ƕ�Ϊ��
        {
         dty= 1500+ 11*angle;
         
         if(dty>1995)
          dty=1995;
        }    */
   PWMDTY23=dty;
  
}



