#ifndef _MYDEFINE_H_
#define _MYDEFINE_H_
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#define LineDisable TIE_C0I=0; 
#define Linenable  TIE_C0I=1;
#define ROW        40                 //��������ͷ���ɼ��Ķ�ά��������
#define COLUMN     80                //��������ͷ���ɼ��Ķ�ά��������
#define ROW_START  10                 //��������ͷ��ά�����п�ʼ��ֵ
#define ROW_MAX    220                //��������ͷ���ɼ��Ķ�ά���������ֵ
#define THRESHOLD  155              //ͼ����ֵ���������ɼ�ͼ������ֵ��С��ʵ�����������OV7620���ɼ�������ֵ��СΪ0--255��
#define oddField   PORTE_PE7
#define error1  5
#define error2  7
#define middle 20  //ȡ��20�е��е� 
#define farLine 11     //ȡ��11�еĵ� 

#endif