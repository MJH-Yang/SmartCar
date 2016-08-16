#include "system.h"
/*************************************************************/
/*                        ��ʼ��PLL����                      */
/*************************************************************/
void PLL_Init(void) {

    CLKSEL=0X00;			                	//disengage PLL to system
    PLLCTL_PLLON=1;			                //turn on PLL
    SYNR =0xc0 | 0x05;                        
    REFDV=0x80 | 0x01; 
    POSTDIV=0x00;                       //pllclock=2*osc*(1+SYNR)/(1+REFDV)=96MHz;
    _asm(nop);                          //BUS CLOCK=48M
    _asm(nop);
    while(!(CRGFLG_LOCK==1));	          //when pll is steady ,then use it;
    CLKSEL_PLLSEL =1;		                //engage PLL to system; 

}  

void Rampinterrupt_init(void) 
{
   PPSJ_PPSJ0 = 1 ;      //PJ0�ڴ�����ʽ��=1�����������ش�����=0�������½��ش���
   PIEJ_PIEJ0 = 1 ;      //PJ0�ж�ʹ�� �� =1�����жϣ� =0 �������ж�
}


 //--------PID������ʼ��--------//
/*void PID_init(void) 
{
  //pid->SetPWMDTY = 0;  
  //pid->CurrentError = 0;  //Error[0]
  pid->LastError = 0;  //Error[-1]
  pid->PrevError = 0;  //Error[-2]
  pid->LastUk = 0;   //��һ������
  //PIDϵ�����޸������������ֵ
  pid->Proportion = 0;   //��������Proportion Const
  pid->Integral = 0;     //���ֳ���Integral Const
  pid->Derivative = 0;   //΢�ֳ���Derivative Const
}   */


/*************************************************************/
/*                      IO�ڳ�ʼ������                       */
/*************************************************************/

void IO_Init(void) 
{ 

         DDRA = 0X00;             //�˿�A���ó�����
         DDRB = 0XFF;             //
         DDRK = 0XB7;
         DDRE &= 0X63;          //E�˿��У�E7��E4��3��2Ϊ����
         PORTB = 0X00;  
} 

void PWM_Init(void)    //PWM��ʼ������������Ͷ��
{     
    //SB,B for ch2367
    //SA,A for ch0145         
    PWMCTL_CON45=1;  //4��5���ϳ�16λPWM
    PWMCTL_CON01=1;  //01��45���Ƶ��
    PWMCTL_CON23=1;  //2��3���ϳ�16λPWM�����ƶ��
   
    PWMCAE_CAE5=0; //ѡ�����ģʽΪ��������ģʽ
    PWMCAE_CAE1=0;
    PWMCAE_CAE3=0; //ѡ�����ģʽΪ��������ģʽ
    
    PWMCNT45=0;  //����������
    PWMCNT01=0;
    PWMCNT23=0;  //����������
    
    PWMPOL_PPOL5=1;
    PWMPOL_PPOL1=1; //������ߵ�ƽ��������DTYʱ����ת��ƽ
    PWMPOL_PPOL3=1; //������ߵ�ƽ��������DTYʱ����ת��ƽ
    
    PWMPRCLK=0X31; //clockA2��Ƶ,clockA=24MHz��clockB����8��Ƶ,clockB=busclock/4=6MHz
    PWMSCLB=3; //��clock SB ����2*3=6��Ƶ�SSB clock=clockB/6=1MHz;
    PWMCLK_PCLK1=0; //ѡ��clock  A��ʱ��Դ
    
    PWMCLK_PCLK5=0;  //ѡ��clock A��ʱ��Դ
    PWMCLK_PCLK3=1; //ѡ��clock SB��ʱ��Դ
    
    PWMPER45=2000; //���� 25KHz
    PWMPER01=2000;
    PWMPER23=20000; //����20ms�� 50Hz
    
    PWMDTY01=48;
    PWMDTY45=48;  //���ó�ʼ����ٶ�Ϊ0
    PWMDTY23=1500;  //���ó�ʼ����Ƕ�Ϊ0
     
    PWME_PWME1=1; 
    PWME_PWME5=1;
    PWME_PWME3=1; 
    
    
    
} 


/*************************************************************/
/*                     ��ʱ����                              */
/*************************************************************/

void delays(unsigned int m){

 while(m--);
 
 }
 
 