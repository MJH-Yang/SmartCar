

#ifndef _DUOJI_H_

#define _DUOJI_H_
#include <hidef.h>      
#include "derivative.h"
#include "mydefine.h"

extern unsigned char angle;         //ƫת�Ƕ�
extern unsigned char turn_flag;   //�ж���ת����ת��һΪ��ת
extern unsigned char judge_line;     //ֱ���������־ 1Ϊֱ����0Ϊ���
extern unsigned int Image_Center[ROW];        //���ɼ���ͼ��������

void duoji_driver (void);  //dtyΪ�����PWMDTY��ֵ

#endif
