 #include <ioCC2530.h>
 #include "exboard.h"


void main()
{
 //KEY1  KEY2 ����
  
  P0SEL &= ~0X02;//0000 0010
  P0INP |= 0x02; //���� 00000010  
  P0IEN |= 0x02;   //P0��1����Ϊ�жϷ�ʽ 1 �ж�ʹ�� P2IEN |=0X01
  P2IEN |=0X01;
  PICTL |= 0X02;   //�½��ش���0000 0010  PICTL |=OX01

  EA = 1;
   IEN1 |= 0X20;  // P0����Ϊ�жϷ�ʽʹ��;0010 0000  IEN2 |=0X02
   IEN2 |=0X02;
  P0IFG |= 0x00;   //��ʼ���жϱ�־λ P2IFG |=0X00
  P2IFG |=0X00;

 // P1SEL &= ~0xc0; //����led
 // P1DIR|=0xC0;
 P1SEL &=~0x13;
 P1DIR |=0x13;
 
  led1=1;
  led2=0;
   while(1)
   {


   }

}
#pragma vector = P0INT_VECTOR   //�˿�P0���жϴ�����
 __interrupt void P0_ISR(void)
 {
    if(P0IFG>0)            //�����ж� P2IFG
   {
       led1=!led1;
       led2=!led2;

       P0IFG = 0;          //���P0_0�жϱ�־
       P0IF = 0;           //���P0�жϱ�־


    }

 }
#pragma vector = P2INT_VECTOR    //�˿�P2���жϴ�����
 __interrupt void P2_ISR(void)
 {
    if(P2IFG>0)            //�����ж� P2IFG
   {
       led1=!led1;
       led2=!led2;

       P2IFG = 0;          //���P0_0�жϱ�־
       P2IF = 0;           //���P0�жϱ�־


    }

 }