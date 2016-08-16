#include "motor_zhuansu_measure.h"

float motor_n1=0,motor_n2=0;
float ave_motor = 0; 
unsigned int pulsenum1,pulsenum2,a1,a3;
char di,gao;

/****************************************************/
/*                     ���ٺ���                     */
/*                  �źŽӿ�ΪT7��                  */
/****************************************************/
void speed_measure1() 
{ 
  unsigned int data1,data2;
 
  unsigned int i;
  float n=457.1429;  //n��ֵ����ʱ��Ĳ�ͬ���ı�,n=45714.29/�ۼ������ʱ�䳤��
  
  TFLG1_C2F = 1;  //�����λ
   
   TC2=TCNT+100;
   data1 = PACNT; //�������ۼӼ�������ǰֵ����data1���Ա�֮ǰ�ĳ�����ˣ���Ϊdata2Ĭ�ϳ�ʼ��ֵΪ�����

    for(i=0;i<3;i++)          //��ʱ0.1ms
    {
        while(TFLG1_C2F == 0);  
        TFLG1_C2F = 1;  //�����λ
        TC2 =TCNT+100;    //TCNTΪ��ʱ�������Ĵ���  
    }
    
    data2 = PACNT;  //�����ۼӼ����Ĵ���
    pulsenum1 = data2-data1;   //����100us�ɼ��������ص�����(float)
    motor_n1= n * pulsenum1;    //����ת��n
} 

void speed_measure2 () 
{ 
  unsigned int data1,data2;
 
  unsigned int i;
  float n=457.1429;  //n��ֵ����ʱ��Ĳ�ͬ���ı�,n=45714.29/�ۼ������ʱ�䳤��
  //float n=10;
  TFLG1_C2F = 1;  //�����λ
   
   TC2=TCNT+100;
   data1 = PACNT; //�������ۼӼ�������ǰֵ����data1���Ա�֮ǰ�ĳ�����ˣ���Ϊdata2Ĭ�ϳ�ʼ��ֵΪ�����

    for(i=0;i<3;i++)          //��ʱ0.1ms
    {
        while(TFLG1_C2F == 0);  
        TFLG1_C2F = 1;  //�����λ
        TC2 =TCNT+100;    //TCNTΪ��ʱ�������Ĵ���  
    }
    
    data2 = PACNT;  //�����ۼӼ����Ĵ���
    pulsenum2 = data2-data1;   //����100us�ɼ��������ص�����(float)
    motor_n2= n * pulsenum2;    //����ת��n
} 

void speed(void)
{
  speed_measure1();
  speed_measure2();
  ave_motor = (motor_n1 + motor_n2) / 2;
  //pwm = (int)(93.5427 + 0.135269 *ave_motor);   //��ǰ�ٶ�PWM
  a1 = (int)ave_motor;
  di = (char)a1;    //ת�ٵ�8λ
  a3 = a1 >> 8;     //����8λ
  gao = (char)a3;    //ת�ٸ�8λ
}



/*
����˼·�ǣ�
Ŀ�ģ���һ�����������T
�����趨һ��ʱ��t(100us)
T = t / �������

��tֵ���趨Ҫ�ڵ�Ƭ�������־������趨�ü�������0��������ʱ��Ϊ tt(ʱ������)����������Ҫ��ʱ����t,�Ǿ�Ҫ����t/tt ��
�����������ʱ������Ϊ1/3us,����300�ξ���100us�ˣ�������300�ξ���3 * 100 �Σ�����forѭ��3�Σ�
pulsenum����������������������ֵ - ��ʼ������ֵ
*/

