#ifndef INC_H
#define INC_H
#ifndef uint32_t
#define uint32_t              unsigned int
#endif
typedef unsigned short        int uint16_t;
typedef unsigned              char uint8_t;
/*片上外设基地址  */
#define PERIPH_BASE           ((unsigned int)0x40000000)
/*APB1 总线基地址 */
#define APB1PERIPH_BASE       PERIPH_BASE
/*APB2 总线基地址 */
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
/* AHB总线基地址 */
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000)
//---------------------------时钟-------------------------
#define RCC_BASE              (AHBPERIPH_BASE + 0x1000)
#define RCC_CR			      *(volatile unsigned int*)(RCC_BASE+0x00)//volatile
#define RCC_CFGR		      *(volatile unsigned int*)(RCC_BASE+0x04)
#define RCC_CIR		          *(volatile unsigned int*)(RCC_BASE+0x08)
#define RCC_APB2ENR		      *(volatile unsigned int*)(RCC_BASE+0x18)
#define RCC_APB1ENR		      *(volatile unsigned int*)(RCC_BASE+0x1C)

//--------------------------Flash----------------------------
#define FLASH_R_BASE          (AHBPERIPH_BASE + 0x2000) /*!< Flash registers base address */
#define FLASH_ACR             *(volatile unsigned int*)(FLASH_R_BASE+0x00)
#define FLASH_KEYR            *(volatile unsigned int*)(FLASH_R_BASE+0x04)
#define FLASH_OPTKEYR         *(volatile unsigned int*)(FLASH_R_BASE+0x08)
#define FLASH_SR              *(volatile unsigned int*)(FLASH_R_BASE+0x0C)
#define FLASH_CR              *(volatile unsigned int*)(FLASH_R_BASE+0x10)
#define FLASH_AR              *(volatile unsigned int*)(FLASH_R_BASE+0x14)
#define FLASH_OBR             *(volatile unsigned int*)(FLASH_R_BASE+0x1C)
#define FLASH_WRPR            *(volatile unsigned int*)(FLASH_R_BASE+0x20)

#define FLASH_KEY1             ((uint32_t)0x45670123)
#define FLASH_KEY2             ((uint32_t)0xCDEF89AB)
//写入起始地址与最终地址
#define WRITE_START_ADDR       ((uint32_t)0x0800A000)
#define WRITE_END_ADDR         ((uint32_t)0x0800F000)
//每页的大小 2k
#define FLASH_PAGE_SIZE        ((uint16_t)0x800)	//2048

//---------------------------串口---------------------------
#define USART1_BASE           (APB2PERIPH_BASE + 0x3800)
#define USART1_SR             *(volatile uint16_t *)(USART1_BASE + 0x00)
#define USART1_DR             *(volatile uint16_t *)(USART1_BASE + 0x04)
#define USART1_BRR            *(volatile uint16_t *)(USART1_BASE + 0x08)
#define USART1_CR1            *(volatile uint16_t *)(USART1_BASE + 0x0C)
#define USART1_CR2            *(volatile uint16_t *)(USART1_BASE + 0x10)
#define USART1_CR3            *(volatile uint16_t *)(USART1_BASE + 0x14)

#define  BAUDRATE             115200  //波特率设置
#define  STOP       00        //停止位，00——1个，01——0.5个 10——2个 11——1.5个
#define  M           0        //字长设置  0：一个起始位，8个数据位，n个停止位；1：一个起始位，9个数据位，n个停止位。
#define  PCE         0        //0：禁止校验控制；1：使能校验控制。
#define  PS          0        //0：偶校验；1：奇校验。
#define  TE          1        //0：禁止发送；1：使能发送。
#define  RE          1        //0：禁止接收；1：使能接收，并开始搜寻RX引脚上的起始位。
#define  CTSE        0        //0：禁止CTS硬件流控制；1：CTS模式使能
#define  RTSE        0        //0：禁止RTS硬件流控制；1：RTS中断使能

//#define HSE
#ifdef HSE
    #define  PCLK2_Frequency      72000000
#else 
    #define  PCLK2_Frequency      64000000
#endif//HSE
//-------------------------GPIO----------------------------------
/*GPIOA外设基地址*/
#define GPIOA_BASE			(APB2PERIPH_BASE + 0x0800)
/* GPIOB寄存器地址,强制转换成指针 */
#define GPIOA_CRL			*(volatile unsigned int*)(GPIOA_BASE+0x00)
#define GPIOA_CRH			*(volatile unsigned int*)(GPIOA_BASE+0x04)
#define GPIOA_IDR			*(volatile unsigned int*)(GPIOA_BASE+0x08)
#define GPIOA_ODR			*(volatile unsigned int*)(GPIOA_BASE+0x0C)
#define GPIOA_BSRR	  		*(volatile unsigned int*)(GPIOA_BASE+0x10)
#define GPIOA_BRR			*(volatile unsigned int*)(GPIOA_BASE+0x14)
#define GPIOA_LCKR			*(volatile unsigned int*)(GPIOA_BASE+0x18)

/*GPIOB外设基地址*/
#define GPIOB_BASE          (APB2PERIPH_BASE + 0x0C00)
/* GPIOB寄存器地址,强制转换成指针 */
#define GPIOB_CRL			*(volatile unsigned int*)(GPIOB_BASE+0x00)
#define GPIOB_CRH			*(volatile unsigned int*)(GPIOB_BASE+0x04)
#define GPIOB_IDR			*(volatile unsigned int*)(GPIOB_BASE+0x08)
#define GPIOB_ODR			*(volatile unsigned int*)(GPIOB_BASE+0x0C)
#define GPIOB_BSRR	  		*(volatile unsigned int*)(GPIOB_BASE+0x10)
#define GPIOB_BRR			*(volatile unsigned int*)(GPIOB_BASE+0x14)
#define GPIOB_LCKR			*(volatile unsigned int*)(GPIOB_BASE+0x18)


#define LED_Green_ON        GPIOB_ODR &= ~(1<<0)//绿灯亮
#define LED_Green_OFF       GPIOB_ODR |=  (1<<0)//绿灯灭

#define LED_Red_ON          GPIOB_ODR &=  ~(1<<5)//红灯亮
#define LED_Red_OFF         GPIOB_ODR |=  (1<<5)//红灯灭

#define LED_Blue_ON         GPIOB_ODR &= ~(1<<1)//蓝灯亮
#define LED_Blue_OFF        GPIOB_ODR |=  (1<<1)//蓝灯灭

#define LED_OFF             GPIOB_ODR |=  (1<<0);\
                            GPIOB_ODR |=  (1<<5);\
                            GPIOB_ODR |=  (1<<1)
//----------------------------TIM7--------------------------
#define TIM6_BASE           (APB1PERIPH_BASE + 0x1000)
#define TIM6_CR1            *(volatile unsigned int*)(TIM6_BASE + 0x00)
#define TIM6_CR2            *(volatile unsigned int*)(TIM6_BASE + 0x04)
#define TIM6_DIER           *(volatile unsigned int*)(TIM6_BASE + 0x0C)
#define TIM6_SR             *(volatile unsigned int*)(TIM6_BASE + 0x10)
#define TIM6_EGR            *(volatile unsigned int*)(TIM6_BASE + 0x14)
#define TIM6_CNT            *(volatile unsigned int*)(TIM6_BASE + 0x24)
#define TIM6_PSC            *(volatile unsigned int*)(TIM6_BASE + 0x28)
#define TIM6_ARR            *(volatile unsigned int*)(TIM6_BASE + 0x2C)

//-----------------------xModem------------------------------
#define SOH                 (uint16_t)0x01       //包头
#define EOT                 (uint16_t)0x04       //发送结束（发送端）
#define ACK                 (uint16_t)0x06       //接收无误（接收端）
#define NAK                 (uint16_t)0x15       //请求发送/请求重发（接收端）
#define CAN                 (uint16_t)0x18       //无条件结束（接收端）

#define IF                  0   //调试信息：1开启0关闭





#endif	//INC_H