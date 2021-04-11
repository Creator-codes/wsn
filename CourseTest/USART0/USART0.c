//BY QIUJIE TECH.INC.

#include <ioCC2530.h>
#include <string.h>
#include "exboard.h"


//��������
void Delay(uint);
void initUARTSEND(void);
void UartTX_Send_String(char *Data,int len);

char Txdata[25];
/****************************************************************
    ��ʱ����											
****************************************************************/
void Delay(uint n)
{
	uint i;
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
}
/****************************************************************
   ���ڳ�ʼ������				
****************************************************************/
void initUARTSEND(void)
{

    CLKCONCMD &= ~0x40;                          //����ϵͳʱ��ԴΪ32MHZ����
    while(CLKCONSTA & 0x40);                     //�ȴ������ȶ�
    CLKCONCMD &= ~0x47;                          //����ϵͳ��ʱ��Ƶ��Ϊ32MHZ


    PERCFG = 0x00;				//USART 0ʹ��λ��1 P0_2,P0_3��
    P0SEL = 0x3C;				//P0_2,P0_3,P0_4,P0_5��������


    U0CSR |= 0x80;				//UART��ʽ
    U0GCR |=9;				
    U0BAUD |= 59;				//��������Ϊ19200
    UTX0IF = 0;                                 //UART0 TX�жϱ�־��ʼ��λ0
}
/****************************************************************
���ڷ����ַ�������			
****************************************************************/
void UartTX_Send_String(char *Data,int len)
{
  int j;
  for(j=0;j<len;j++)
  {
    U0DBUF = *Data++;
    while(UTX0IF == 0);
    UTX0IF = 0;
  }
}
/****************************************************************
������						
****************************************************************/
void main(void)
{	
	uchar i;
       	
	initUARTSEND();
	
        strcpy(Txdata,"HELLO ");       //���ַ���HELLO����Txdata;
	while(1)
	{
           UartTX_Send_String(Txdata,sizeof("HELLO ")); //���ڷ�������
           Delay(5000);
	}
}