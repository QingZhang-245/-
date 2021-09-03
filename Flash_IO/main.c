#include "inc.h"

extern void NVIC_Configuration(IRQn_Type IRQn,uint32_t Preemption,uint32_t Sub);
extern void UART_Configuration(UART_TypeDef* UARTx);
extern int UART_IsRXFIFONotEmpty(UART_TypeDef* UARTx);

void system_set(void);
void ringBufferPut(RingBufferTypeDef * buf, uint8_t ch);
int32_t ringBufferGet(RingBufferTypeDef * buf);

RingBufferTypeDef ringbuf;
int main(void)
{
    system_set();
    NVIC_Configuration(UART0_IRQn,0,1);
    NVIC_Configuration(UART1_IRQn,1,1);
    UART_Configuration(UART0);
    UART_Configuration(UART1);

    uint32_t tmpSend;
    while(1) 
    {
        if(ringbuf.count >= 1)//ringbufÄÚ»¹ÓÐÊý¾ÝÊ±
        {	
            UART0->OFFSET_0.THR = 0x31;
            tmpSend = ringBufferGet(&ringbuf);
            while ((UART1->MSR & (1<<4)) == 0);//等待从机接收	
            UART1->OFFSET_0.THR = tmpSend;
        }
    }
}


void UART0_IRQHandler(void)
{
    uint8_t ch;
    switch(UART0->OFFSET_8.IIR & 0x0f)
    {
        case ((uint32_t)0x0004):
                    {  
                        UART0->OFFSET_0.THR = 0x46;
                        while(UART_IsRXFIFONotEmpty(UART0))	//FIFO·Ç¿ÕÊ±Êä³öÊý¾Ý
                        {
                            ch = (uint8_t)(UART0->OFFSET_0.RBR & 0xFF);
                            ringBufferPut(&ringbuf, ch); //ÊäÈëringbuf
                        }
                    }
        break;
        case ((uint32_t)0x0002)://发送中断
                    {
                        UART0->OFFSET_0.THR = 0x47;
                        UART0->OFFSET_4.IER &= ~((uint32_t)0x0002);//关闭发送中断
                    }
        break;
        case ((uint32_t)0x000C)://超时未取出，存入buffer
                    {
                        UART0->OFFSET_0.THR = 0x51;
                        while(UART_IsRXFIFONotEmpty(UART0))
                        {
                            ch = (uint8_t)(UART0->OFFSET_0.RBR & 0xFF);
                            ringBufferPut(&ringbuf, ch); //ÊäÈëringbuf
                        }
                    }	
		break;

        default:
        UART0->OFFSET_0.THR = 0x52;
        break;
    }

}

void UART1_IRQHandler(void)
{
    uint8_t ch;
    switch(UART1->OFFSET_8.IIR & 0x0f)
    {
        case ((uint32_t)0x0004):
                    {
                        UART0->OFFSET_0.THR = 0x37;
                        while(UART_IsRXFIFONotEmpty(UART1))	//转给UART0
                        {
                            ch = (uint8_t)(UART1->OFFSET_0.RBR & 0xFF);
                            UART0->OFFSET_0.THR = ch;
                        }
                    }
        break;
        case ((uint32_t)0x000C)://超时未取出，转给UART0
            {
                UART0->OFFSET_0.THR = 0x38;
                while(UART_IsRXFIFONotEmpty(UART1))
                {
                        ch = (uint8_t)(UART1->OFFSET_0.RBR & 0xFF);
                        UART0->OFFSET_0.THR = ch;
                }
            }	
		break;
        default:
        UART0->OFFSET_0.THR = 0x99;
        break;
    }
}


void system_set(void)//门控，软复位，时钟频率设定
{
    SYSCTRL->CG_CTRL1 |= 0X04310003;
    SYSCTRL->SOFT_RST1 |= 0x00380003;
    SYSCTRL->FREQ_SEL |=  0x200F395A;//取PLL时钟192MHZ
}


void ringBufferInit(RingBufferTypeDef * buf)
{
    uint32_t len = sizeof(buf->buffer);
    for(;len>0;len--)
    {
        buf->buffer[sizeof(buf->buffer)-len] = 0;
    }
	buf->get_index = 0;
	buf->put_index = 0;
	buf->count = 0;
}

void ringBufferPut(RingBufferTypeDef * buf, uint8_t ch)	//ÊäÈë
{
	buf->buffer[buf->put_index] = ch;
	buf->put_index = (buf->put_index + 1) & (RING_BUFFER_SIZE - 1);
	buf->count += 1;
	if(buf->put_index == buf->get_index)
	{
		buf->get_index = (buf->get_index + 1) & (RING_BUFFER_SIZE - 1);
	}
}

int32_t ringBufferGet(RingBufferTypeDef * buf)		//Êä³ö
{
	int32_t ch;
	ch = -1;
	if(buf->get_index != buf->put_index)
	{
		ch = buf->buffer[buf->get_index];
		buf->count -= 1;
		buf->get_index = (buf->get_index + 1) & (RING_BUFFER_SIZE - 1);
	}
	return ch;
}


