#ifndef _PIDcontrol_H_
#define _PIDcontrol_H_
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "system.h"

//-----�ⲿ����-----//


//-----��������-----//

//void timer_init(void);  // ��ʱ���жϳ�ʼ��
void Add_pid(int NextPoint);//����ʽPID
//void PIDInit(void);
void PID_Curve(void);
void PID_Line(void);

#endif