#include "PIDcontrol.h" 
int iError, iIncpid;
typedef struct PID
{
int SetPoint; //�趨Ŀ�� Desired Value
//long SumError; //����ۼ�
float Proportion; //�������� Proportional Const
float Integral; //���ֳ��� Integral Const
float Derivative; //΢�ֳ��� Derivative Const
int LastError; //Error[-1]
int PrevError; //Error[-2]
} PID;
static PID sPID;
static PID *sptr = &sPID;

//PID������ʼ��
/*void PIDInit(void)
{
//sptr->SumError = 0;
sptr->LastError = 0; //Error[-1]
sptr->PrevError = 0; //Error[-2]
sptr->Proportion = 0; //�������� Proportional Const
sptr->Integral = 0; //���ֳ���Integral Const
sptr->Derivative = 0; //΢�ֳ��� Derivative Const
sptr->SetPoint = 2000;   //Ŀ���ٶ�
}  */

//ֱ����ʼ��PID����
void PID_Line(void)
{
//sptr->SumError = 0;
sptr->LastError = 0; //Error[-1]
sptr->PrevError = 0; //Error[-2]
sptr->Proportion = 0.0055; //�������� Proportional Const
sptr->Integral = 0.005; //���ֳ���Integral Const
sptr->Derivative =0; //΢�ֳ��� Derivative Const
sptr->SetPoint = 1300;   //Ŀ���ٶ�Ϊ6.2m/s,��Ӧ����PWM���Ϊ384��
}

//�����ʼ��PID����
void PID_Curve(void)
{
//sptr->SumError = 0;
sptr->LastError = 0; //Error[-1]
sptr->PrevError = 0; //Error[-2]
sptr->Proportion = 0.003; //�������� Proportional Const
sptr->Integral = 0.003; //���ֳ���Integral Const
sptr->Derivative = 0; //΢�ֳ��� Derivative Const
sptr->SetPoint = 1371;   //Ŀ���ٶ�Ϊ5m/s,��Ӧ����PWM���Ϊ336
}


//nextpoint ʵ���ٶ�
void Add_pid(int NextPoint)
{

//��ǰ���
iError = sptr->SetPoint - NextPoint;
//��������
iIncpid = (int)(sptr->Proportion * iError //E[k]��
- sptr->Integral * sptr->LastError //E[k��1]��
+ sptr->Derivative * sptr->PrevError); //E[k��2]��
//�洢�������´μ���
sptr->PrevError = sptr->LastError;
sptr->LastError = iError;
//��������ֵ

}


