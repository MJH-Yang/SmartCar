#include"motor.h"
int PWM_value=0,PWM_value1;
int motor_n; //n Ϊת��

/**********************************************************************
                         �������
**********************************************************************
���ܣ����������ֱ�������
���룺ֱ���������־
��������Ƶ����PWMDTY*/

void motor_driver(void) 
{
  //unsigned int dty;    //dtyָռ�ձȼĴ���5��ֵ�����������ڽ�ֹ�ж�֮ǰ���������� 
   /*
    PID_Line();
    speed();  //����ģ��
    motor_n = (int)ave_motor;
    Add_pid(motor_n);
    PWM_value = PWM_value1 + iIncpid;  //�ٶ�PID
    if (PWM_value < 0)
      PWM_value = 0;
    if (PWM_value > 1500)
      PWM_value = 1500;
    
    PWMDTY01 = PWM_value;
    PWM_value1 = PWM_value;
    PWMDTY45 = 48; 
    */
    PWMDTY01 = 1000;
    PWMDTY45 = 48; 
  
   /*
  if (judge_line == 1) 
  {
    //PWMDTY01 = 400;
    //PWMDTY45 = 48; 
    
    PID_Line();
    speed();  //����ģ��
    motor_n = (int)ave_motor;
    Add_pid(motor_n);
    PWM_value = PWM_value + iIncpid;  //�ٶ�PID
    if (PWM_value < 0)
      PWM_value = 0;
    if (PWM_value > 700)
      PWM_value = 700;
    
    PWMDTY01 = PWM_value;
    PWMDTY45 = 48; 
     
  } 
  else 
  {
    //PWMDTY01 = 300;
    //PWMDTY45 = 48;
    
    PID_Curve();
    speed();  //����ģ��
    motor_n = (int)ave_motor;
    Add_pid(motor_n);
    PWM_value = PWM_value + iIncpid;  //�ٶ�PID
    if (PWM_value < 0)
      PWM_value = 0;
    if (PWM_value > 700)
      PWM_value = 700;
    PWMDTY01 = PWM_value;
    PWMDTY45 = 48;
  }
  */
  
  //dty = (int)(44.552603319 + 0.16739543382 * motor_n);  //ȡ����
    
  //PWMDTY45=dty; //�ߵ�ƽʱ��
  //PWMDTY01=48;  //ռ�ձ�Ϊ5%
    
  //PWME_PWME5=1; //ʹ��ͨ��5      
  //PWME_PWME1=1;
}