
#ifndef _CCD_H_
#define _CCD_H_
#include <hidef.h>      
#include "derivative.h"
#include "mydefine.h"
#include "system.h"

void CCD_Init(void); 
void erzhiAll(void);	//��ֵ��
void quzao(void);	//ȥ��
unsigned int mid(unsigned int n1, unsigned int n2);		//ȡ����ֵ
void center();	//��������ȡ
void SeachCenter(void);//��������

#endif