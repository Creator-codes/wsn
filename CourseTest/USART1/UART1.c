//BY QIUJIE TECH.INC

#include <iocc2530.h>
#include <string.h>
#include "exboard.h"

void initUART0(void);
void InitialAD(void);
void UartTX_Send_String(uchar *Data,int len);

uchar str1[20]="What is your name? ";
uchar str2[7]="hello ";
uchar Recdata[20];
uchar RXTXflag = 1;
uchar temp;
uint  datanumber = 0;
uint  stringlen;
/****************************************************************
��ʼ������0����					
****************************************************************/
void initUART0(void)
{
    P1SEL &= 0x03;
    P1DIR |= 0x03;
  
    CLKCONCMD &= ~0x40;                         //����ϵͳʱ��ԴΪ32MHZ����
    while(CLKCONSTA & 0x40);                    //�ȴ������ȶ�
    CLKCONCMD &= ~0x47;                         //����ϵͳ��ʱ��Ƶ��Ϊ32MHZ

    PERCFG = 0x00;				//λ��1 P0��
    P0SEL = 0x3c;				//P0��������
    P2DIR &= ~0XC0;                             //P0������ΪUART0
    U0CSR |= 0x80;				//��������ΪUART��ʽ
    U0GCR |= 9;				
    U0BAUD |= 59;				//��������Ϊ19200
    UTX0IF = 1;                                 //UART0 TX�жϱ�־��ʼ��λ1
    U0CSR |= 0X40;				//�������
    IEN0 |= 0x84;				//�����жϣ������ж�
}
/****************************************************************
���ڷ����ַ�������				
****************************************************************/
void UartTX_Send_String(uchar *Data,int len)
{
  uint j;
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
	P1DIR = 0x03; 				//P1����LED
	initUART0();

	UartTX_Send_String(str1,20);	
	while(1)
	{
          if(RXTXflag == 1)			     //����״̬
          {

            if( temp != 0 )
            {
                if((temp!='#')&&(datanumber<20))     //������������Ϊ�����ַ�������ܽ���20���ַ�
                {
                 Recdata[datanumber++] = temp;
                 if (temp == '1')
                 {
                   // LED_1 on
                   LED_1 = 0;
                 } else if (temp == '2')
                 {
                   // LED_2 on
                   LED_2 = 0;
                 } else if (temp == '3')
                 {
                   // LED_1 off
                   LED_1 = 1;
                 } else if (temp == '4')
                 {
                   // LED_2 off
                   LED_2 = 1;
                 }
                }
                else
                {
                  RXTXflag = 3;                      //���뷢��״̬
                }

              temp  = 0;
            }
          }
          if(RXTXflag == 3)			//����״̬
          {
            		        //����״ָ̬ʾ
            U0CSR &= ~0x40;			//��������
            UartTX_Send_String(str2,6);
            UartTX_Send_String(Recdata,datanumber);
            U0CSR |= 0x40;			//�������
            RXTXflag = 1;		        //�ָ�������״̬
            datanumber = 0;			//ָ���0
            		
          }
	}
}
/****************************************************************
���ڽ���һ���ַ�:һ�������ݴӴ��ڴ���CC2530,������жϣ������յ������ݸ�ֵ������temp.
****************************************************************/
#pragma vector = URX0_VECTOR
 __interrupt void UART0_ISR(void)
 {
 	URX0IF = 0;				//���жϱ�־
	temp = U0DBUF;
 }