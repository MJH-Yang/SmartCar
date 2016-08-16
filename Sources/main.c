/********************************************************************************/
/********************************************************************************
���ߣ�jnu_fangze
ʱ�䣺2014/8/18

                  
��λ������
  ������   115200
  ͼ���� 80
  ͼ��߶� 40

���ߣ�
      S0(��Ƭ���ϵ�RXD)  -----> ����ģ��TXD:��
      S1(��Ƭ���ϵ�TXD)  -----> ����ģ��RXD����
      GND(��Ƭ���ϵĵ�)  -----> ����ģ��GND      //�����Ƭ���ʹ���ʹ�ò�ͬ��Դ��Ҳ��Ҫ����
      ������115200
      
      A0-A7  -----------------> ����ͷģ�� (����)Y0 - Y7
      T0     -----------------> ����ͷģ�� (���ж�)HREF
      T1     -----------------> ����ͷģ�� (���ж�)VSYN
      PE7 -----------------------����ͷ��ż���ź�
      
  �����
      P3------------------------��ɫ��
  �����
      P1------------------------��һ·
      P5------------------------�ڶ�· 
  905��
      TXEN------PORTK_PK0;  TRX_CE------PORTK_PK1 ;  PWR ------PORTK_PK2;	
      MISO------PORTK_PK3;  MOSI------PORTK_PK4;    SCK ------PORTK_PK5;
      CSN ------PORTK_PK7;  AM  ------PORTE_PE2;    DR  ------PORTE_PE3;
      CD  ------PORTE_PE4;  AM,DR,MISO,CD Ϊ���룬����Ϊ���           
*********************************************************************************
*********************************************************************************/
#include <hidef.h>          
#include "derivative.h"         
#include <mc9s12xs128.h>
#include "system.h" 
#include "sci.h"
#include "mydefine.h"
#include "ccd.h"
#include "duoji.h"
#include "motor.h"
#include "camera_deal.h"
#include "nrf905.h"
#include "motor_zhuansu_measure.h"
#include "PIDcontrol.h"

extern unsigned char SampleFlag;


/*************************************************************/
/*                          ������                           */
/*************************************************************/
void main(void) 
{ 
  
 /* put your own code here */ 
   PLL_Init();  //��ʼ�����໷
   CCD_Init();  //��ʼ���ж�
   IO_Init();   //��ʼ��IO��
   SCI_Init();  //��ʼ������
   SCI_Init1();
   PWM_Init();  //��ʼ��PWM   
   nRF905Init();//��ʼ��NRF905
   Config905(); //����NRF905
   //PIDInit();
   //Rampinterrupt_init();

  
 
  EnableInterrupts; 
  
  for(;;) 
  {
      if(data_temp[3]==0xA5 && data_temp[2]==0x5A&&data_temp[1]==0x49&&data_temp[0]==0xAA)
      {
       PWMDTY01 = 0;
       PWMDTY45 = 0; 
      }
      else
      {
          if(SampleFlag==0) 
            { 
              PORTB=0X00;
              Process_Data();           //����Դ��ڷ������ɼ���ͼ��
              
              SeachCenter();
              //Process_Erzhi();       //���Ͷ�ֵ�����ͼ������
      		    //Process_zx();         //������������
              big_curve();
              //Process_canshu();   //���Ͳ���
              
              //Send_data();
              
              //Send_zhongxian();
             
              //duoji_driver();
              
              motor_driver(); 
              
                                         
            } 
          else 
            {
            PORTB=0XFF;
            }
      }
   }   
 
           //   _FEED_COP(); /* feeds the dog */ 

          /* loop forever */ 
         /* please make sure that you never leave main */ 
} 

