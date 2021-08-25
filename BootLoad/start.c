#include "inc.h"
typedef void (*Handler)(void);
void Reset_Handler(void);
extern void SysClock();
extern int main(void);
extern  uint32_t _estack;        //引用链接脚本中地址
extern  uint32_t __text_end__;
extern  uint32_t __data_start__;
extern  uint32_t __data_end__;
extern  uint32_t __bss_start__;
extern  uint32_t __bss_end__;


typedef struct{                //定义空间结构体
	void* estack;
	Handler vector[256];
} Vectors;


const Vectors cortex_vectors = {    //初始化结构体，赋予指针地址与内容
	&_estack,
	{[0] = Reset_Handler}
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
