#include "inc.h"



static inline uint32_t kfifo_count(kfifo_t *fifo)
{
    return fifo->in - fifo->out;
}

static inline void kfifo_empty(kfifo_t *fifo)
{
    fifo->in = fifo->out = 0;
}


uint32_t kfifo_put(kfifo_t *fifo, const uint8_t *buffer, uint32_t len)//输入
{
    uint32_t l,i = 0;
    len = min(len, fifo->size - fifo->in + fifo->out);//对比输入长度和内部剩余空间谁更小

    /* first put the data starting from fifo->in to buffer end */    //从in到end输入数据
    l = min(len, fifo->size - (fifo->in & (fifo->size - 1)));   //可输入的长度与len对比
    //memcpy(fifo->buffer + (fifo->in & (fifo->size - 1)), buffer, l);    //从入口输入数据
    for(i=0;i<l;i++)
    {
        *(fifo->buffer + (fifo->in & (fifo->size - 1)) + i ) = *(buffer + i);
    }

    /* then put the rest (if any) at the beginning of the buffer */     //将其他数据输入到buffer开头
    //memcpy(fifo->buffer, buffer + l, len - l);
    for(i=0;i<(len-l);i++)
    {
        *(fifo->buffer + i) = *(buffer + l + i);
    }

    fifo->in += len;
    return len;
}

uint32_t kfifo_get(kfifo_t *fifo, uint8_t *buffer, uint32_t len)//输出
{
    uint32_t l,i = 0;
    len = min(len, fifo->in - fifo->out);   //输出数据大小和内含数据大小对比

    /* first get the data from fifo->out until the end of the buffer */
    l = min(len, fifo->size - (fifo->out & (fifo->size - 1)));
    //memcpy(buffer, fifo->buffer + (fifo->out & (fifo->size - 1)), l);
    for(i=0;i<l;i++)
    {
        *(buffer + i) = *(fifo->buffer + (fifo->out & (fifo->size - 1)) + i );
    }

    /* then get the rest (if any) from the beginning of the buffer */
    //memcpy(buffer + l, fifo->buffer, len - l);
    for(i=0;i<(len-l);i++)
    {
        *(buffer + l + i) = *(fifo->buffer + i);
    }

    fifo->out += len;

//    if (fifo->in == fifo->out)
//        fifo->in = fifo->out = 0;
    return len;
}