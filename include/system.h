#ifndef _SYSTEM_H_
#define _SYSTEM_H_
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
void PLL_Init(void);
void CCD_Init(void);
//void ECT_Init(void);
void IO_Init(void);
void PWM_Init(void);
void delays(unsigned int m);
void Rampinterrupt_init(void);
//void PID_init(void);  // PID������ʼ��
/*
//-----PID�����ṹ��-----//
typedef struct {
  //int SetPWMDTY;    //�趨��PWMռ�ձ�  
  //int CurrentError; //��ǰ���Error[0]
  int LastError;      //��һ���Error[-1]
  int PrevError;      //ǰһ���Error[-2]
  int LastUk;         //��һ������
  int Proportion;     //��������Proportion Const
  int Integral;       //���ֳ���Integral Const
  int Derivative;     //΢�ֳ���Derivative Const
}PID;

static PID sPID;
static PID *pid = &sPID;
*/
 

#endif

