#include "sci.h"
unsigned char data_receive=0;
unsigned char data_temp[4]=0;

/*************************************************************/
/*                       ����0��ʼ������                     */
/*************************************************************/
void SCI_Init() 

{ 
          SCI0BD=48000000/16/115200;              //115200bps     Baud Rate=BusClock/(16*SCIBD) 
         //SCI0BD=261;              //19200bps     Baud Rate=BusClock/(16*SCIBD) 
         //SCI0BD=521;
         SCI0CR1=0;              //����8 λģʽ������żУ�� 
         SCI0CR2=0X2C;           //��������  �����ж����� 
} 

void SCI_Init1()
{
  SCI1BD = 48000000/16/9600;   //����SCI0������Ϊ9600
  SCI1CR1 = 0x00;        //����SCI0Ϊ����ģʽ����λ����λ������żУ��
  SCI1CR2 = 0x2c;        //������պͷ������ݣ���������жϹ���
}

unsigned char SCI_receive(void) 
{
  while(!SCI1SR1_RDRF);          //�ȴ��������ݼĴ�����
  return(SCI1DRL);
}


/*************************************************************/
/*                        ����0���ͺ���                      */
/*************************************************************/
void SCI_Write(unsigned char SendChar) 
{ 
                                         
      while (!(SCI0SR1&0x80)); 
      SCI0DRH=0; 
      SCI0DRL=SendChar; 
} 

/*************************************************************/
/*                 ����Դ��ڷ������ɼ���ͼ��                */
/*************************************************************/
void Process_Data(void) 
{ 
   unsigned char i,j; 
   
   for(i=0;i<ROW;i++) 
   { 
      for(j=0;j<COLUMN;j++) 
       { 
          if(Image_Data[i][j] == 0xFF) 
            SCI_Write(0xFE); 
          else
            SCI_Write(Image_Data[i][j]); 
      } 
      //SCI_Write(0x0D); 
      //SCI_Write(0X0A);    
   } 
   SCI_Write(0xFF);
} 

/*************************************************************/
/*                 ����Դ��ڷ������ɼ���ͼ��                */
/*************************************************************/
void Process_Erzhi(void) 
{ 
   unsigned char i,j; 
   
   for(i=0;i<ROW;i++) 
   { 
      for(j=0;j<COLUMN;j++) 
       { 
            SCI_Write(ImageBuffer[i][j]) ; 
      } 
      //SCI_Write(0x0D); 
      //SCI_Write(0X0A);    
   } 
   SCI_Write(0xFF);
} 

/*************************************************************/
/*                 ����Դ��ڷ�������������                */
/*************************************************************/
//���ܣ������������鷢�͵�������λ��
void Process_zx(void) 
{ 
   unsigned char i;
   unsigned char temp;
   SCI_Write(0xff);  
   for(i=0;i<ROW;i++) 
   { 
      temp = (char)Image_Center[i];
      SCI_Write(temp);   
         
   } 
}   


/***************************************************************
                   ����Է��͸�������
****************************************************************
���ܣ����Ͳ���*/
void Process_canshu(void)
{ 
  SCI_Write(0xff);
  SCI_Write(big_curve_c);
  
  SCI_Write(0xaa);
  SCI_Write(judge_line);
  
  SCI_Write(0xbb);
  //SCI_Write(angle);
  
  SCI_Write(0xcc);
  //SCI_Write(left_turn[2]);
  
  SCI_Write(0xdd);
}

/*************************************************************/
/*                     �����жϽ��պ���                      */
/*************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void receivedata(void) 
{
    data_receive = SCI_receive();
    
    
    data_temp[3] = data_temp[2];
    data_temp[2] = data_temp[1];
    data_temp[1] = data_temp[0];
    data_temp[0] = data_receive;
    
    
    
   
    
}
#pragma CODE_SEG DEFAULT