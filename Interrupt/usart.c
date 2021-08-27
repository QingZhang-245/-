#include "inc.h"
void Usart_Init()
{
  uint32_t tmpreg = 0x00, apbclock = 0x00;
  uint32_t integerdivider = 0x00;
  uint32_t fractionaldivider = 0x00;
  //GPIOA�ĵ�ַ����RCC_APB2ENR��ַ�ĵ�3λ��usart�ǵ�14λ
  //ʹ��GPIOAʱ��
  RCC_APB2ENR |= (1<<2);
  //��USART1ʱ��
  RCC_APB2ENR |= (1<<14);

  //��տ���PA9��PA10�Ķ˿�λ
  GPIOA_CRH &= ~( 0x0F<< (4*1));
  GPIOA_CRH &= ~( 0x0F<< (4*2));

  //����PA9���츴��ģʽ��50MHz    1011
  GPIOA_CRH |= (11<<1*4);
  //����PA10��������ģʽ  0100
  GPIOA_CRH |= (4<<2*4);

  //����ֹͣλ����
  USART1_CR2 &= 0xCFFF;  //����STOPλ
  USART1_CR2 &= ~(STOP<<12);

  //����CR1
  USART1_CR1 &= 0xE9F3;  
  //����֡����
  USART1_CR1 &= ~(M<<12);
  //ʹ��У��λ
  USART1_CR1 &= ~(PCE<<10);
  //����У��λ
  //USART1_CR1 |= (PS<<9);
  //����ģʽ
  USART1_CR1 |= (TE<<3);
  USART1_CR1 |= (RE<<2);
  //Ӳ��������
  USART1_CR3 &= 0xFCFF;
  USART1_CR3 &= ~(CTSE<<9);
  USART1_CR3 &= ~(RTSE<<9);

  //���ò�����
  apbclock = PCLK2_Frequency;
  integerdivider = ((25*apbclock)/(4*BAUDRATE));
  tmpreg = (integerdivider / 100) << 4;
  fractionaldivider = integerdivider - (100 * (tmpreg >> 4));
  tmpreg |= ((((fractionaldivider * 16) + 50) / 100)) & ((uint8_t)0x0F);
  USART1_BRR = (uint16_t)tmpreg;
/*
  USART1_BRR  = 0x0000; 
	USART1_BRR  = 0x271;
*/
  //UEʹ��
  USART1_CR1 |= (1<<13);
}

void USART_SendData(uint16_t Data)
{
  USART1_DR = (Data & (uint16_t)0x01FF);
}


int putchar(int c)
{
  while ((USART1_SR & (1<<7)) != 0)
  {
    USART1_DR = (uint8_t)(c & (uint16_t)0x01FF);
    if (c == '\n') putchar('\r');
    return c;
  }
}





/*
//�ض������ʹ��printf����
int fputc(int ch, FILE *f)
{
		//*����һ���ֽڵ�����
		USART_SendData((uint8_t) ch);
		
		// �ȴ�������� 
    uint32_t status = 0;
		while (status == 0)
    {
      status = USART1_SR & (1<<7);
    }
	
		return (ch);
}

///�ض������ʹ��getchar����
int fgetc(FILE *f)
{
    int data;
    uint32_t status = 0;
		while (status == 0)
    {
      status = USART1_SR & (1<<5);
    }
    data = (uint16_t)(USART1_DR & (uint16_t)0x01FF);
		return data;
}
*/