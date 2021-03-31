#include <ioCC2530.h>
#include "exboard.h"

uint counter=0;	//ͳ��t1�������
uint counter1=0;//ͳ��t3�������
               //��ʼ����������
void Init_T1(void)
{
  P1SEL &= ~0x03;
  P1DIR = 0x03; 	
   	

    CLKCONCMD &= ~0x7f;                //��������Ϊ32MHZ
    while(CLKCONSTA & 0x40);           //�ȴ������ȶ�


    EA = 1;                           //���ж�
    T1IE = 1;                         //��T1����ж�
    T1CTL =0x05;                     //��������8��Ƶ��������ģʽ

    led1=1;
    led2=0;
}

/***************************
//������
***************************/
void main()
{
	Init_T1();
        T3IE = 1;
        T3CTL=0x7C;               //T3��������8��Ƶ��������ģʽ
        
       	while(1)   	         //��ѯ���
	{

	}
}
#pragma vector = T1_VECTOR
 __interrupt void T1_ISR(void)
 {
 	IRCON = 0x00;			  //���жϱ�־,Ҳ����Ӳ���Զ����
        if(counter<300)
           counter++;	                 //300���ж�LED��˸һ�֣�ԼΪ5��ʱ�䣩
        else
        {
         counter = 0;                    //��������
         led1 = !led1;	           //��˸��־��ת
        }
 }
#pragma vector = T3_VECTOR
 __interrupt void T3_ISR(void)
 {
 	IRCON = 0x00;			  //���жϱ�־,Ҳ����Ӳ���Զ����
        if(counter1<300)
           counter1++;	                 //300���ж�LED��˸һ�֣�ԼΪ5��ʱ�䣩
        else
        {
         counter1 = 0;                    //��������
         led2 = !led2;	           //��˸��־��ת
        }
 }
