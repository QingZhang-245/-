#include "inc.h"

void Usart_Init()
{
  uint32_t tmpreg = 0x00, apbclock = 0x00;
  uint32_t integerdivider = 0x00;
  uint32_t fractionaldivider = 0x00;
  //GPIOA的地址就是RCC_APB2ENR地址的第3位，usart是第14位
  //使能GPIOA时钟
  RCC_APB2ENR |= (1<<2);
  //打开USART1时钟
  RCC_APB2ENR |= (1<<14);

  //清空控制PA9和PA10的端口位
  GPIOA_CRH &= ~( 0x0F<< (4*1));
  GPIOA_CRH &= ~( 0x0F<< (4*2));

  //设置PA9推挽复用模式，50MHz    1011
  GPIOA_CRH |= (11<<1*4);
  //设置PA10浮空输入模式  0100
  GPIOA_CRH |= (4<<2*4);

  //设置停止位长度
  USART1_CR2 &= 0xCFFF;  //清零STOP位
  USART1_CR2 &= ~(STOP<<12);

  //清零CR1
  USART1_CR1 &= 0xE9F3;  
  //定义帧长度
  USART1_CR1 |= (M<<12);
  //使能校验位
  USART1_CR1 &= ~(PCE<<10);
  //设置校验位
  //USART1_CR1 |= (PS<<9);
  //设置模式
  USART1_CR1 |= (TE<<3);
  USART1_CR1 |= (RE<<2);
  //硬件控制流
  USART1_CR3 &= 0xFCFF;
  USART1_CR3 &= ~(CTSE<<9);
  USART1_CR3 &= ~(RTSE<<9);

  //设置波特率
  apbclock = PCLK2_Frequency;
  integerdivider = ((25*apbclock)/(4*BAUDRATE));
  tmpreg = (integerdivider / 100) << 4;
  fractionaldivider = integerdivider - (100 * (tmpreg >> 4));
  tmpreg |= ((((fractionaldivider * 16) + 50) / 100)) & ((uint8_t)0x0F);
  USART1_BRR = (uint16_t)tmpreg;

  //UE使能
  USART1_CR1 |= (1<<13);
}
/*******************发送一个字节**************************/
void USART_SendData(uint16_t Data)
{
  USART1_DR = ((uint16_t)Data & (uint16_t)0xFF);
  while ((USART1_SR & (1<<7)) == 0);
}

/*****************发送字符串**********************/
void USART_SendString(char *str)
{
	unsigned int k=0;
  do 
  {
      USART_SendData(*(str + k));
      k++;
  } while(*(str + k)!='\0');
  
  while((USART1_SR & (1<<6)) == 0);
}
void USART_SendHalfWord(uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	temp_h = ((uint16_t)(ch)&0XFF00)>>8;
	temp_l = (uint16_t)(ch)&0XFF;
	
	USART_SendData(temp_h);	
	USART_SendData(temp_l);	
}


/*
//重定向后能使用printf函数
int fputc(int ch, FILE *f)
{
		//发送一个字节到串口
		USART_SendData((uint8_t) ch);
		
		// 等待发送完毕 
    uint32_t status = 0;
		while (status == 0)
    {
      status = USART1_SR & (1<<7);
    }
	
		return (ch);
}

///重定向后能使用getchar函数
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