 #include "ramp_deal(1).h"

  /*////////////////////////////////////////////////////////////
  //���������20cm���ң���2cm���ϣ������������һ�鵲�壬�������
  ,����ģ�������߷ֱ�ӵأ���5v��ѹ���ⲿ�жϿ�PT2   */
  //////////////////////////////////////////////////////////////
  ////////////////////////////////////////
  //camera-deal.c���޸�һ�㣬ʹ��PT2
  //�øÿ���Ϊ�жϿ�
  
  
void Speed_less(void) 
{
      PWMDTY45 = 300;
      PWMDTY01 = 48;    //��ֵ���������һ��
      
}//���ü��ٺ������ɻ����Ǳ��ṩ,����Ҫ�����٣�Ҫʵ��

#pragma CODE_SEG __NEAR_SEG NON_BANKED 

void interrupt VectorNumber_Vtimch2  PT2_Interrupt()
{
 
   PIFJ_PIFJ0 = 1;  //����жϱ�־λ
   Speed_less(); 
   
}

//#pragma CODE_SEG DEFAULT