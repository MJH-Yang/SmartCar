/*
TXEN------PORTK_PK0;  TRX_CE------PORTK_PK1 ;  PWR ------PORTK_PK2;	
MISO------PORTK_PK3;  MOSI------PORTK_PK4;    SCK ------PORTK_PK5;
CSN ------PORTK_PK7;  AM  ------PORTE_PE2;    DR  ------PORTE_PE3;
CD  ------PORTE_PE4;  AM,DR,MISO,CD Ϊ���룬����Ϊ���
*/
#include "nrf905.h"
//----------------------------------------------------------------------------------------------------------------
#define BYTE_BIT0	0x01
#define BYTE_BIT1	0x02
#define BYTE_BIT2	0x04
#define BYTE_BIT3	0x08
#define BYTE_BIT4	0x10
#define BYTE_BIT5	0x20
#define BYTE_BIT6	0x40
#define BYTE_BIT7	0x80
//----------------------------------------------------------------------------------------------------------------
unsigned  char DATA_BUF;
#define DATA7	((DATA_BUF&BYTE_BIT7) != 0)
#define DATA0   ((DATA_BUF&BYTE_BIT0) != 0)
#define	flag    (DATA_BUF&BYTE_BIT7)
#define	flag1	(DATA_BUF&BYTE_BIT0)
//***************�������ݻ�����***********************
#define TxRxBuf_Len 32
unsigned char TxRxBuf[TxRxBuf_Len]={0};
unsigned char Tx_temp[32] = {0};
//���ÿڶ���//
#define 	TXEN    	     PORTK_PK0;
#define 	TRX_CE         PORTK_PK1;
#define	  PWR            PORTK_PK2;
#define 	MISO           PORTK_PK3;
#define 	MOSI           PORTK_PK4;
#define 	SCK            PORTK_PK5;
#define 	CSN            PORTK_PK7;
/////////////////////////////////////////////////////
#define 	AM             PORTE_PE2;
#define 	DR             PORTE_PE3;
#define 	CD             PORTE_PE4;
//----------------------------------------------------����--------------------------------------------------

//#define LED               PORTB
//#define LED_dir           DDRB
//#define KEY1              PTIH_PTIH3
//#define KEY2              PTIH_PTIH2
//#define KEY1_dir          DDRH_DDRH3
//#define KEY2_dir          DDRH_DDRH2

//unsigned char data=0x01;
//unsigned char mode=1;

//---------------------nrf905����ָ��-------------------------------------------
#define WC		0x00
#define RC		0x10
#define WTP		0x20
#define RTP		0x21
#define WTA		0x22
#define RTA		0x23
#define RRP		0x24

//--------------------NRF905�Ĵ�������------------------------------------------------
unsigned char RFConf[11]={
  0x00,                             //��������//
  0x4c,                             //CH_NO,����Ƶ����430MHZ
  0x0c,                             //�������Ϊ10db,���ط����ڵ�Ϊ����ģʽ
  0x44,                             //��ַ������ã�Ϊ4�ֽ�
  0x20,0x20,                        //���շ�����Ч���ݳ���Ϊ32�ֽ�
  0xCC,0xCC,0xCC,0xCC,              //���յ�ַ
  0x58                              //CRC����8λCRCУ�飬�ⲿʱ���źŲ�ʹ�ܣ�16M����
};
const unsigned char TxAddress[4]={0xcc,0xcc,0xcc,0xcc};
//----------------��ʱ--------------------------------
void NrfDelay(unsigned char n)
{
	unsigned int i;
	while(n--)
	for(i=0;i<80;i++);
}

//---------------------------------------------------SPI������-----------------------------------------------------
unsigned char SpiRead(void)
{
	unsigned char j;
	for (j=0;j<8;j++)
	{
    DATA_BUF= (DATA_BUF<<1);
  	PORTK |= BYTE_BIT5;   //	SCK=1;
		if (PORTK&BYTE_BIT3)	//��ȡ���λ����������ĩβ��ͨ������λ��������ֽ�
		{
			DATA_BUF|=BYTE_BIT0;
		}
		else
		{
			DATA_BUF&=~BYTE_BIT0;
		}
		PORTK &= ~BYTE_BIT5;   //SCK=0;	
	 }
	 return DATA_BUF;
}

//-------------------------------------------------SPIд����----------------------------------------------------------
void SpiWrite(unsigned char send)
{
	unsigned char i;
	DATA_BUF=send;
	for (i=0;i<8;i++)
	{
		if (DATA7)	//���Ƿ������λ
		{
		    PORTK |= BYTE_BIT4;    //	MOSI=1;
		}
		else
		{
	      PORTK &= ~BYTE_BIT4;	//	MOSI=0;
		}
	  PORTK |= BYTE_BIT5;   //	SCK=1;
		DATA_BUF=DATA_BUF<<1;
	  PORTK &= ~BYTE_BIT5;  //	SCK=0;
	}
}

//------------------------------------------------------��ʼ��nRF905---------------------------------------------
void nRF905Init(void)
{
  PORTK |= BYTE_BIT7;    //  CSN=1;						// Spi 	disable
	PORTK &= ~BYTE_BIT5;   //SCK=0;						// Spi clock line init low
	PORTE &= ~BYTE_BIT3;   //DR=0;						// Init DR for input
	PORTE &= ~BYTE_BIT2;   //AM=0;						// Init AM for input
	PORTE &= ~BYTE_BIT4;   //CD=0;						// Init CD for input
	PORTK |= BYTE_BIT2;    //PWR=1;					// nRF905 power on
	PORTK &= ~BYTE_BIT1;   //TRX_CE=0;					// Set nRF905 in standby mode
	PORTK &= ~BYTE_BIT0;   //TXEN=0;					// set radio in Rx mode
}

//--------------------��ʼ���Ĵ���-----------------------------------------------
void Config905(void)
{
	uchar i;
	PORTK &= ~BYTE_BIT7;     //CSN=0;						// Spi enable for write a spi command
	//SpiWrite(WC);				// Write config commandд����������
	for (i=0;i<11;i++)	    // Write configration words  д��������
	{
	   SpiWrite(RFConf[i]);
	}
	PORTK |= BYTE_BIT7;     //CSN=1;					// Disable Spi
}

//-----------------------------------------------------�������ݴ��---------------------------------------------------
void TxPacket(unsigned char *TxBuf)
{
	unsigned char i;
	//Config905();
	PORTK &= ~BYTE_BIT7;      //CSN=0;
	SpiWrite(WTP);			    	// Write payload command
	for (i=0;i<32;i++)
	{
		SpiWrite(TxBuf[i]);		// Write 32 bytes Tx data
	}                         // Spi enable for write a spi command
	PORTK |= BYTE_BIT7;      //CSN=1;
	NrfDelay(1);					    	// Spi disable
	PORTK &= ~BYTE_BIT7;     //CSN=0;						// Spi enable for write a spi command
	SpiWrite(WTA);			   	// Write address command
	for (i=0;i<4;i++)		   	// Write 4 bytes address
	{
		SpiWrite(TxAddress[i]);
	}
	PORTK |= BYTE_BIT7;     //CSN=1;						// Spi disable
	PORTK |= BYTE_BIT1;     //TRX_CE=1;					// Set TRX_CE high,start Tx data transmission
	NrfDelay(1);				 
	//while(PORTE_PE3 !=1);
	PORTK &= ~BYTE_BIT1;    //TRX_CE=0;					// Set TRX_CE low
}

//--------------------------���÷���״̬---------------------------------------------
void SetTxMode(void)
{
	PORTK &= ~BYTE_BIT1;   //TRX_CE=0;
	PORTK |= BYTE_BIT0;   //TXEN=1;
	NrfDelay(1); 					// delay for mode change(>=650us)
}

/********************************************************************
                            ������������
���ܣ����������͵�������
���ݣ�                            
*/
void canshu(unsigned char *TxBufTemp) 
{
    TxBufTemp[0] = 0xFF;
    TxBufTemp[1] = big_curve_c;
    TxBufTemp[2] = judge_line;
    TxBufTemp[3] = (char)square;
    TxBufTemp[4] = (char)base;
    TxBufTemp[5] = slow_speed_flag;
    TxBufTemp[6] = left_flag;
    TxBufTemp[7] = right_flag;
    TxBufTemp[8] = turn_flag;
    TxBufTemp[9] = far_temp;
    TxBufTemp[10] = mid_temp;
    TxBufTemp[11] = angle;
    TxBufTemp[12] = di;
    TxBufTemp[13] = gao;
    TxBufTemp[14] = 0xAA;
}

/********************************************************************
                             ������ز���
*********************************************************************
���ܣ������ͨ�����߷��͵�������λ��
���ݣ����͸���������*/
void Send_data()
{
   canshu(TxRxBuf);
   SetTxMode();
   NrfDelay(100);
   TxPacket(TxRxBuf); 
}
/********************************************************************
                              ���������鷢�͵�������
*********************************************************************
���ܣ������������͵���������
*/
void zhongxian(unsigned char *TxZxTemp)
{
   char i;
   TxZxTemp[0] = 0xBB;
   TxZxTemp[31] = 0xCC;
   for(i=29; i>=1; i--)
    TxZxTemp[i] = (char)Image_Center[i]; 
   TxZxTemp[30] = (char)average;
}

void zhongxian2(unsigned char *TxZTemp)
{
  char i;
  TxZTemp[0] = 0xDD;
  for(i=1; i<11; i++)
    TxZTemp[i] = (char)Image_Center[i];
  TxZTemp[11] = 0xAA;
}

/******************************************************************
                       ������������
*******************************************************************
���ܣ������������鵽��λ��*/
void Send_zhongxian(void)
{
  zhongxian(Tx_temp);
  SetTxMode();
  //NrfDelay(100);
  //NrfDelay(100);
  //NrfDelay(100);
  //NrfDelay(100);
  //NrfDelay(100);
  //NrfDelay(100);
  //NrfDelay(100);
  //
  //NrfDelay(100);
  //NrfDelay(100);
  //NrfDelay(100);
  //NrfDelay(100);
  
  TxPacket(Tx_temp);
  //zhongxian2(TxRxBuf);
  //NrfDelay(100);
  //TxPacket(TxRxBuf);
}


















