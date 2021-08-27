#include "inc.h"
typedef void (*Handler)(void);
extern void SysClock();
extern void USART_SendData(uint16_t Data);
extern int main(void);
extern  uint32_t _estack;        //引用链接脚本中地址
extern  uint32_t __text_end__;
extern  uint32_t __data_start__;
extern  uint32_t __data_end__;
extern  uint32_t __bss_start__;
extern  uint32_t __bss_end__;

void Reset_Handler(void);
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void WWDG_IRQHandler(void);
void PVD_IRQHandler(void);
void TAMPER_IRQHandler(void);
void RTC_IRQHandler(void);
void FLASH_IRQHandler(void);
void RCC_IRQHandler(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);

typedef struct{                //定义空间结构体
	void* estack;
	Handler vector[256];
} Vectors;


const Vectors cortex_vectors = {    //初始化结构体，赋予指针地址与内容
	&_estack,
	{
		Reset_Handler,
		NMI_Handler,
		HardFault_Handler,
		MemManage_Handler,
		BusFault_Handler,
		UsageFault_Handler,
		0,
		0,
		0,
		0,
		SVC_Handler,
		DebugMon_Handler,
		0,
		PendSV_Handler,
		SysTick_Handler,
		WWDG_IRQHandler,
		PVD_IRQHandler,
		TAMPER_IRQHandler,
		RTC_IRQHandler,
		FLASH_IRQHandler,
		RCC_IRQHandler,
		EXTI0_IRQHandler,
		EXTI1_IRQHandler,
	}
};


void Reset_Handler(void)            //复位函数
{
    uint32_t *flash, *ram;
	flash = &__text_end__;
	ram = &__data_start__;
	if(flash != ram)       //ram实际地址不是连在flash后面时，复制数据
		{
			for(;ram < &__data_end__;)
			{
				*ram = *flash;
				flash ++;
				ram ++;
			}
		}
	for(ram = &__bss_start__; ram < &__bss_end__; ram ++)
		{
			*ram = 0;    //进入bss段指向的地址中清零
		}
  	SysClock();       //初始化系统时钟
	main();           //进入main函数
}


__attribute__((weak)) void NMI_Handler()
{

}
__attribute__((weak)) void HardFault_Handler()
{

}

__attribute__((weak)) void MemManage_Handler()
{

}

__attribute__((weak)) void BusFault_Handler()
{

}
__attribute__((weak)) void UsageFault_Handler()
{

}

__attribute__((weak)) void SVC_Handler()
{
	
}
__attribute__((weak)) void DebugMon_Handler()
{
	
}

__attribute__((weak)) void PendSV_Handler()
{
	
}
__attribute__((weak)) void SysTick_Handler() 
{
	
}
__attribute__((weak)) void WWDG_IRQHandler()
{
	
}
__attribute__((weak)) void PVD_IRQHandler()
{
	
}
__attribute__((weak)) void TAMPER_IRQHandler()
{
	
}
__attribute__((weak)) void RTC_IRQHandler()
{
	
}
__attribute__((weak)) void FLASH_IRQHandler()
{
	
}
__attribute__((weak)) void RCC_IRQHandler()
{
	
}

int EXTI_GetITStatus(uint32_t EXTI_Line)
{
	int bitstatus = 0;
	uint32_t enablestatus = 0;

	enablestatus =  EXTI->IMR & EXTI_Line;
	if (((EXTI->PR & EXTI_Line) != (uint32_t)(0)) && (enablestatus != (uint32_t)(0)))
		{
		bitstatus = 1;
		}
	else
		{
		bitstatus = 0;
		}
	return bitstatus;
}


void EXTI0_IRQHandler(void)
{
	
	if(EXTI_GetITStatus((uint32_t)0x00001) != 0) 
	{
		USART_SendData((uint16_t)0x54);
		LED_OFF;
		EXTI->PR = (uint32_t)0x00001;   
	}  
}

__attribute__((weak)) void EXTI1_IRQHandler()
{
	
}