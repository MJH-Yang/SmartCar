/***************************************************************************
���ߣ�jnu_bin
ʱ�䣺2014/8/15
���ݣ�ͼ�����ӳ���
****************************************************************************/ 


#include "ccd.h"

#define  noise_min 5
#define  noise_max 50

unsigned char Image_Data[ROW][COLUMN]={0};       //���ɼ���ͼ���ά����
unsigned char ImageBuffer[ROW][COLUMN]={0};     //ͼ�񻺳�����
unsigned int Image_Center[ROW]={0};        //���ɼ���ͼ��������
 
unsigned char SampleFlag=0;       //��ż�����

unsigned int  m=0;                 //���б���
 
unsigned int  Line;               //���жϼ�������
unsigned int  hang;               

 
unsigned int  Get_Image[]={   
                         17,19,21,23,25,28,31,34,37,40,43,46,49,53,57, 
                         61,65,69,73,77,81,85,89,94,99,105,111,117,123,
                         129,135,141,147,153,159,166,173,180,187,189
                         
                         };     //��ÿ�����ļ��С� 
                        

/*************************************************************/
/*                      �г��жϳ�ʼ������                   */
/*************************************************************/
void CCD_Init(void) 
{ 
        TIOS=0x04;              //�ⲿ���벶׽0,1ͨ�� 
        TCTL4=0x09;             //ͨ��0 �����ش���,ͨ��1�½��ش��� 
        TCTL1 = 0x00;	    // ���ĸ�ͨ������Ϊ��ʱ����������ŶϿ�
        TCTL2 = 0x00;     // ǰ�ĸ�ͨ������Ϊ��ʱ����������ŶϿ�
        TSCR1=0x80;             //ʹ�� 
        TSCR2 = 0x04;	    // Ԥ��Ƶϵ��pr2-pr0:100,16��Ƶ��ʱ������Ϊ1/3us,
        TIE=0x03;               //ͨ�� 0��1 �ж�ʹ�� 
        TFLG1=0xFF;             //���жϱ�־λ 
        TFLG2 = 0xff;     // ������ɶ�ʱ���жϱ�־λ
        PACTL = 0x50;   //��ʼ���ۼ���
} 

 
//*****************************************************************************
//                           ��ֵ��
//*****************************************************************************
//���ܣ���ͼ��������ж�ֵ��
//����:����ͼ�� 
//�������ֵ�����ͼ������ 
//���ݴ���//��ֵ��
//����ͨ����2014/8/16�� 
void erzhiAll()  
{  
     unsigned char i,j;
     //unsigned char *p_Image; 
     //unsigned char *q_Image;
     
     //q_Image=&ImageBuffer[0][0];
     /*for ( i=0; i<ROW; i++)
      for(p_Image=&Image_Data[i][0],q_Image=&ImageBuffer[i][0];p_Image<=&Image_Data[i][COLUMN-1];p_Image++,q_Image++)  
       {
          if ((*p_Image >= THRESHOLD) && (*p_Image<256)) 
          {
            *q_Image = 1;
          } 
          else
          {
            *q_Image = 0;
          }
       }*/
       
      for(i=0; i<ROW; i++)
        for(j=0; j<COLUMN; j++)
          if (Image_Data[i][j] >= THRESHOLD && Image_Data[i][j] < 256) 
          {
            ImageBuffer[i][j] = 1;
          } 
          else 
          {
            ImageBuffer[i][j] = 0;
          }
} 

//*****************************************************************************
//                          ȥ��
//****************************************************************************** 
//���ܣ�ȥ����Ƚ�С��ϴ�����
//���룺����ͼ������
//�����ȥ����ͼ������ 
void quzao()
{
	unsigned char i,j;
	char k;
	unsigned int white_dop;
	for(i=0;i<ROW;i++)
		for(j=0;j<COLUMN;j++) {
		  if(ImageBuffer[i][j]==1) 	//�ӵ�һ���׵�ƽ��ʼ���� 
			{
				white_dop++;
				if(ImageBuffer[i][j+1]==0)  //��һ��Ϊ�ڵ�ƽʱֹͣ���� 
					{
					if(white_dop < noise_min || white_dop > noise_max)  //�˳�������խ����� 
						for(k=white_dop-1;k>=0;k--)
							ImageBuffer[i][j-k]=0;
					white_dop=0;
					}
						
			}
		}
			
}

//****************************************************************************
//                         ȥ����ֵ
//****************************************************************************
//���ܣ������ֵ 
unsigned int mid(unsigned int n1,unsigned int n2)//�����ֵ
{
   unsigned int dif;
   if(n1>n2)
   dif=n1-n2;
   else
   dif=n2-n1;
   return dif;
}/**/


//****************************************************************************
//                           ��������ȡ
//****************************************************************************
//����:��ȡ������
//���룺����ͼ�����飨ȥ���
//���������������
void center()
{
	unsigned int left,right,before,after;
	unsigned int j,i;	
	for(i=0;i<ROW;i++) 
      {
        if(ImageBuffer[i][0] == 0)     //�жϵ�һ�����Ƿ�Ϊ�ڵ� 
  	  	{
  		     for(j=0; j<COLUMN; j++)
		       {
 	            if(ImageBuffer[i][j] == 1)   //ȡ����� 
  		        {
  		          left = j;
  		          break;
  		        }
    	     }
   		     for(j=left; j<COLUMN; j++)
   	        {
     	         if(ImageBuffer[i][j] == 0)	//ȡ�ұ��� 
       	   	   {
       	  	     right = j;
       	  	     break;
       	  	   } 
       	  	   else
       	  	   {
       	  	      if(ImageBuffer[i][78]==1 && ImageBuffer[i][79]==1)
       	  	        right = 79;
       	  	   }
  	        }
 		     Image_Center[i]=(left+right)/2;		//���������� 
  		   } 
  	   	else
  	   	  if (ImageBuffer[i][1] == 1 && ImageBuffer[i][2] == 1)
 		      {
  	  	   for(j=0;j<120;j++)
  		      {
  	          if(ImageBuffer[i][j] == 0)		//ȡ�ұ��� 
              {
              right = j;
              break;
              } 
		        }
		        
	         Image_Center[i] = right/2;				//���������� 
  	  	  }
      }
   //�����Ż������� //��������ޣ�����ȥΪ������������ֵ��
   if(!(Image_Center[39] == 0&&Image_Center[38] == 0))
   {
    
   for(i=ROW-2;i>0;i--)
     if(Image_Center[i]==0) Image_Center[i]=Image_Center[i+1];
   for(i=ROW-3;i>0;i--)
     {
        after=mid(Image_Center[i],Image_Center[i-1]);
        before=mid(Image_Center[i-1],Image_Center[i+1]);
        if (before>error1)
        {
         if (after > error2) 
		         Image_Center[i]=Image_Center[i+1];
         else
            Image_Center[i]=(Image_Center[i-1]+Image_Center[i+1])/2;
        } 
        
     }
   before=mid(Image_Center[0],Image_Center[1]);
   if(before>error1)
     Image_Center[0]=Image_Center[1];
   }
} /* */

/*************************************************************
                       ��������
**************************************************************
���ܣ��ҳ���������
���ݣ�����ǰ��ĺ���*/
void SeachCenter(void) 
{
  erzhiAll(); //ͼ���ֵ��
  quzao();    //ͼ��ȥ��
  center();   //������ȡ
}

/*************************************************************/
/*                        ���жϴ�����                     */
/*************************************************************/

#pragma CODE_SEG __NEAR_SEG NON_BANKED 

void interrupt 8  PT0_Interrupt(){
 
   TFLG1_C0F=1;    //���жϱ�־λ������Ա����´����жϽ���

   Line++;         //���жϼ�������
   
   if ( Line<ROW_START || Line>ROW_MAX ){ 
      return;     //����Ҫ�ɼ�ͼ�����Ч�У�����                               
    } 
    
  if( Line==Get_Image[hang]){
   
    delays(23);//���ͼ�����м����޸�����
   
          
        Image_Data[m][0]=PORTA;_asm();_asm();Image_Data[m][1]=PORTA;_asm();_asm();Image_Data[m][2]=PORTA;_asm();_asm();Image_Data[m][3]=PORTA;_asm();_asm();Image_Data[m][4]=PORTA;_asm();_asm();
        Image_Data[m][5]=PORTA;_asm();_asm();Image_Data[m][6]=PORTA;_asm();_asm();Image_Data[m][7]=PORTA;_asm();_asm();Image_Data[m][8]=PORTA;_asm();_asm();Image_Data[m][9]=PORTA;_asm();_asm();
        Image_Data[m][10]=PORTA;_asm();_asm();Image_Data[m][11]=PORTA;_asm();_asm();Image_Data[m][12]=PORTA;_asm();_asm();Image_Data[m][13]=PORTA;_asm();_asm();Image_Data[m][14]=PORTA;_asm();_asm();
        Image_Data[m][15]=PORTA;_asm();_asm();Image_Data[m][16]=PORTA;_asm();_asm();Image_Data[m][17]=PORTA;_asm();_asm();Image_Data[m][18]=PORTA;_asm();_asm();Image_Data[m][19]=PORTA;_asm();_asm();
        Image_Data[m][20]=PORTA;_asm();_asm();Image_Data[m][21]=PORTA;_asm();_asm();Image_Data[m][22]=PORTA;_asm();_asm();Image_Data[m][23]=PORTA;_asm();_asm();Image_Data[m][24]=PORTA;_asm();_asm();
        Image_Data[m][25]=PORTA;_asm();_asm();Image_Data[m][26]=PORTA;_asm();_asm();Image_Data[m][27]=PORTA;_asm();_asm();Image_Data[m][28]=PORTA;_asm();_asm();Image_Data[m][29]=PORTA;_asm();_asm();
        Image_Data[m][30]=PORTA;_asm();_asm();Image_Data[m][31]=PORTA;_asm();_asm();Image_Data[m][32]=PORTA;_asm();_asm();Image_Data[m][33]=PORTA;_asm();_asm();Image_Data[m][34]=PORTA;_asm();_asm();
        Image_Data[m][35]=PORTA;_asm();_asm();Image_Data[m][36]=PORTA;_asm();_asm();Image_Data[m][37]=PORTA;_asm();_asm();Image_Data[m][38]=PORTA;_asm();_asm();Image_Data[m][39]=PORTA;_asm();_asm();
        Image_Data[m][40]=PORTA;_asm();_asm();Image_Data[m][41]=PORTA;_asm();_asm();Image_Data[m][42]=PORTA;_asm();_asm();Image_Data[m][43]=PORTA;_asm();_asm();Image_Data[m][44]=PORTA;_asm();_asm();
        Image_Data[m][45]=PORTA;_asm();_asm();Image_Data[m][46]=PORTA;_asm();_asm();Image_Data[m][47]=PORTA;_asm();_asm();Image_Data[m][48]=PORTA;_asm();_asm();Image_Data[m][49]=PORTA;_asm();_asm();
        Image_Data[m][50]=PORTA;_asm();_asm();Image_Data[m][51]=PORTA;_asm();_asm();Image_Data[m][52]=PORTA;_asm();_asm();Image_Data[m][53]=PORTA;_asm();_asm();Image_Data[m][54]=PORTA;_asm();_asm();
        Image_Data[m][55]=PORTA;_asm();_asm();Image_Data[m][56]=PORTA;_asm();_asm();Image_Data[m][57]=PORTA;_asm();_asm();Image_Data[m][58]=PORTA;_asm();_asm();Image_Data[m][59]=PORTA;_asm();_asm();
        Image_Data[m][60]=PORTA;_asm();_asm();Image_Data[m][61]=PORTA;_asm();_asm();Image_Data[m][62]=PORTA;_asm();_asm();Image_Data[m][63]=PORTA;_asm();_asm();Image_Data[m][64]=PORTA;_asm();_asm();
        Image_Data[m][65]=PORTA;_asm();_asm();Image_Data[m][66]=PORTA;_asm();_asm();Image_Data[m][67]=PORTA;_asm();_asm();Image_Data[m][68]=PORTA;_asm();_asm();Image_Data[m][69]=PORTA;_asm();_asm();
        Image_Data[m][70]=PORTA;_asm();_asm();Image_Data[m][71]=PORTA;_asm();_asm();Image_Data[m][72]=PORTA;_asm();_asm();Image_Data[m][73]=PORTA;_asm();_asm();Image_Data[m][74]=PORTA;_asm();_asm();
        Image_Data[m][75]=PORTA;_asm();_asm();Image_Data[m][76]=PORTA;_asm();_asm();Image_Data[m][77]=PORTA;_asm();_asm();Image_Data[m][78]=PORTA;_asm();_asm();Image_Data[m][79]=PORTA;_asm();_asm();
        Image_Data[m][80]=PORTA;_asm();
  
       hang++;               
       m++; 
   }
   //erzhi(m);

} 

/*************************************************************/
/*                        ���жϴ�����                     */
/*************************************************************/

#pragma CODE_SEG __NEAR_SEG NON_BANKED 
void interrupt 9 PT1_Interrupt() 

{ 
             TFLG1_C1F=1;              //���ж�������Ա����´εĳ��жϵ���������
             TFLG1_C0F=1;              //���ж�������Ա��ڿ�ʼ�ɼ�ͼ������
             m=0;                      //���м�������㣬�Ա��ڿ�ʼ�ӰѲɼ���ͼ��ŵ�����ĵ�һ��
             Line=0;                   //���ж���ʱ��������
             hang=0;                   //����ʱ�������
             if (oddField == 0) 
             {
               LineDisable;    //�����ж�
               SampleFlag=0;   //����Ǽ�Ϊ0�����ɼ�ͼ��
             }
             else 
             {
                SampleFlag=1;
                Linenable;      //ʹ�����ж�
              }             
}




