#include "inc.h"
extern void Usart_Init();
extern void USART_SendData(uint16_t Data);
void Delay(unsigned int nCount);
void Led_Init();
void Key_Init();

int main(void)
{
	char ch;
	//Led_Init();
	//Usart_Init();
	Key_Init();//GPIO 配置

	//打开AFIO时钟
	RCC_APB2ENR |= (1<<0);

	//NVIC 中断配置
	//设置中断优先级组划分（1位抢占优先级3位子优先级）
	SCB->AIRCR = ((uint32_t)0x05FA0000) | ((uint32_t)0x600);
	uint32_t tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;
	tmppriority = (0x700 - ((SCB->AIRCR) & (uint32_t)0x700))>> 0x08;
    tmppre = (0x4 - tmppriority);
    tmpsub = tmpsub >> tmppriority;

	//配置抢占优先级1
    tmppriority = (uint32_t)(1) << tmppre;

	//配置子优先级1
    tmppriority |=  ((1) & tmpsub);

    tmppriority = tmppriority << 0x04;
    NVIC->IP[6] = tmppriority;//配置优先级
    //Enable the Selected IRQ Channels -------------------------------------
    NVIC->ISER[6 >> 0x05] =				//使能中断
    (uint32_t)0x01 << (6 & (uint8_t)0x1F);
	
	//选择exti的输入信号源
	uint32_t tmp = 0x00;
	tmp = ((uint32_t)0x0F) << (0x04 * (((uint8_t)0x00) & (uint8_t)0x03));
	AFIO->EXTICR[((uint8_t)0x00) >> 0x02] &= ~tmp;
	AFIO->EXTICR[((uint8_t)0x00) >> 0x02] |= (((uint32_t)((uint8_t)0x00)) << (0x04 * (((uint8_t)0x00) & (uint8_t)0x03)));

	//输入线，中断模式，上升沿模式，使能中断

	tmp = (uint32_t)EXTI_BASE;
	//Clear EXTI line configuration 
    EXTI->IMR &= ~((uint32_t)0x00001);		//清除中断请求
    EXTI->EMR &= ~((uint32_t)0x00001);		//清除事件请求
    tmp += 0x00;
    *(__IO uint32_t *) tmp |= ((uint32_t)0x00001);	//使能中断请求
    // Clear Rising Falling edge configuration 
    EXTI->RTSR &= ~((uint32_t)0x00001);		//清除上升沿触发
    EXTI->FTSR &= ~((uint32_t)0x00001);		//清除下降沿触发
    // Select the trigger for the selected external interrupts 
	tmp = (uint32_t)EXTI_BASE;	
	tmp += 0x08;

	*(__IO uint32_t *) tmp |= ((uint32_t)0x00001);		//使能上升沿触发

	LED_Green_ON;

	return 0;
}


void Delay(unsigned int nCount)
{
	uint32_t i = 0xFFFFFF;
	for(; nCount != 0; nCount--)
	{
		for(;i != 0;i--);
	}
}

void Led_Init()
{
	// 开启GPIOB 端口时钟
	RCC_APB2ENR |= (1<<3);
	//清空控制PB0的端口位
	GPIOB_CRL &= ~( 0x0F<< (4*0));	
	// 配置PB0为通用推挽输出，速度为10M
	GPIOB_CRL |= (1<<4*0);

	//清空控制PB1的端口位
	GPIOB_CRL &= ~( 0x0F<< (4*1));	
	// 配置PB1为通用推挽输出，速度为10M
	GPIOB_CRL |= (1<<4*1);

	//清空控制PB5的端口位
	GPIOB_CRL &= ~( 0x0F<< (4*5));
	// 配置PB1为通用推挽输出，速度为10M
	GPIOB_CRL |= (1<<4*5);
	LED_OFF;
}

void Key_Init()//PA0  浮空输入,
{
	//打开APB2上GPIOA的时钟
	RCC_APB2ENR |= (1<<2);

	//清空控制PA0位
	GPIOA_CRL &= ~(0x0F<<(4*0));
	//配置浮空输入0100
	GPIOA_CRL |= (1<<2);
}