
#ifndef _SCI_H_
#define _SCI_H_
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "mydefine.h"
extern unsigned char ImageBuffer[ROW][COLUMN];       //���ɼ���ͼ���ά����
extern unsigned char Image_Data[ROW][COLUMN];       //���ɼ���ͼ���ά����
extern unsigned int Image_Center[ROW];

extern unsigned char left_turn[3];   //�ж���ת����ת��һΪ��ת
extern unsigned char angle;        //ת�ĽǶ�
extern unsigned char judge_line;     //�ж�ֱ�����������1Ϊֱ��
extern unsigned char big_curve_c;    //�������־

extern unsigned char data_receive;
extern unsigned char data_temp[4];
void SCI_Init(void);
void SCI_Init1(void);
void SCI_Write(unsigned char SendChar);
void Process_Data(void);  //���Ͳɼ�����ԭʼͼ������
void Process_Erzhi(void);//���Ͷ�ֵ����������ȥ��������
void Process_zx(void);   //������������
void Process_canshu(void);  //���͸�������

#endif