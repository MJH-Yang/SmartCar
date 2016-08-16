#ifndef _NRF905_H_

#define _NRF905_H_
#include <hidef.h>      
#include "derivative.h"
#include "mydefine.h"
//#include "camera_deal.h"

extern unsigned char angle;        //ת�ĽǶ�
extern unsigned char judge_line;     //�ж�ֱ�����������1Ϊֱ��
extern unsigned char big_curve_c;    //�������־ 
extern unsigned int square;
extern unsigned int base;              //��׼
extern unsigned char slow_speed_flag;  //���ٱ�־
extern unsigned char left_flag;       //��ת��־
extern unsigned char right_flag;      //��ת��־
extern unsigned char turn_flag;       //ת���־
extern unsigned char far_temp;
extern unsigned char mid_temp;
extern unsigned char big_curve_turn_flag;
extern unsigned int Image_Center[ROW];
extern unsigned int average;
extern char di,gao;

void NrfDelay(unsigned char n); 	//��ʱ 
unsigned char SpiRead(void);	//Spi�� 
void SpiWrite(unsigned char send);		//Spiд 
void nRF905Init(void);	//905��ʼ�� 
void Config905(void);   //���üĴ���
void TxPacket(unsigned char *TxBuf); //�������ݰ� 
void SetTxMode(void); 	//���÷���״̬ 
void canshu(unsigned char *TxBufTemp);
void Send_data(void);
void zhongxian(unsigned char *TxZxTemp);
void Send_zhongxian(void);
void zhongxian2(unsigned char *TxZTemp);

#endif