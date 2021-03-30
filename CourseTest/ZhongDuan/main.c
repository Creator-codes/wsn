#include "ioCC2530.H"
#include "exboard.h"

void main(void)
{
  P0SEL &= ~0x02;
  P0INP |= 0x02;  //����  0000 0010
  P0IEN |= 0x02;  //P01 ����Ϊ�жϷ�ʽ 1  �ж�ʹ��
  PICTL |= 0x02;  //�½��ش���
  
  EA=1;
  IEN1 |= 0x20;  //P0����Ϊ�жϷ�ʽ
  P0IFG |=0x00; //��ʼ���жϱ�־λ
  
  P1SEL &= ~0x13;
  P1DIR |= 0x13;

  led1=1;
  led2=0;
  
  while(1)
  {
  }
}

#pragma vector = P0INT_VECTOR
__interrupt void P0_ISR(void)
{
  if(P0IFG>0)
  {
    led1=!led1;
    led2=!led2;
    P0IFG=0;
    P0IF=0;
  }
}
