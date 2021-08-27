#ifndef INC_H
#define INC_H
typedef unsigned int          uint32_t;  
typedef unsigned short int    uint16_t;
typedef unsigned char         uint8_t;

/*片上外设基地址  */
#define PERIPH_BASE           ((unsigned int)0x40000000)
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

#define FLASH_R_BASE          (AHBPERIPH_BASE + 0x2000) /*!< Flash registers base address */
#define FLASH_ACR             *(volatile unsigned int*)(FLASH_R_BASE+0x00)
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
#define  PCLK2_Frequency      72000000
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

//---------------------------NVIC-------------------------
#define SCS_BASE            (0xE000E000)
#define NVIC_BASE           (SCS_BASE +  0x0100)
#define SCB_BASE            (SCS_BASE +  0x0D00)  
#define AFIO_BASE             (APB2PERIPH_BASE + 0x0000)
#define EXTI_BASE             (APB2PERIPH_BASE + 0x0400)


#define     __I     volatile const          /*!< defines 'read only' permissions      */
#define     __IO    volatile                  /*!< defines 'read / write' permissions   */
#define     __O     volatile                  /*!< defines 'write only' permissions     */
typedef struct
{
  __I  uint32_t CPUID;                        /*!< Offset: 0x00  CPU ID Base Register                                  */
  __IO uint32_t ICSR;                         /*!< Offset: 0x04  Interrupt Control State Register                      */
  __IO uint32_t VTOR;                         /*!< Offset: 0x08  Vector Table Offset Register                          */
  __IO uint32_t AIRCR;                        /*!< Offset: 0x0C  Application Interrupt / Reset Control Register        */
  __IO uint32_t SCR;                          /*!< Offset: 0x10  System Control Register                               */
  __IO uint32_t CCR;                          /*!< Offset: 0x14  Configuration Control Register                        */
  __IO uint8_t  SHP[12];                      /*!< Offset: 0x18  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  __IO uint32_t SHCSR;                        /*!< Offset: 0x24  System Handler Control and State Register             */
  __IO uint32_t CFSR;                         /*!< Offset: 0x28  Configurable Fault Status Register                    */
  __IO uint32_t HFSR;                         /*!< Offset: 0x2C  Hard Fault Status Register                            */
  __IO uint32_t DFSR;                         /*!< Offset: 0x30  Debug Fault Status Register                           */
  __IO uint32_t MMFAR;                        /*!< Offset: 0x34  Mem Manage Address Register                           */
  __IO uint32_t BFAR;                         /*!< Offset: 0x38  Bus Fault Address Register                            */
  __IO uint32_t AFSR;                         /*!< Offset: 0x3C  Auxiliary Fault Status Register                       */
  __I  uint32_t PFR[2];                       /*!< Offset: 0x40  Processor Feature Register                            */
  __I  uint32_t DFR;                          /*!< Offset: 0x48  Debug Feature Register                                */
  __I  uint32_t ADR;                          /*!< Offset: 0x4C  Auxiliary Feature Register                            */
  __I  uint32_t MMFR[4];                      /*!< Offset: 0x50  Memory Model Feature Register                         */
  __I  uint32_t ISAR[5];                      /*!< Offset: 0x60  ISA Feature Register                                  */
} SCB_Type; 
typedef struct
{
  __IO uint32_t ISER[8];                      /*!< Offset: 0x000  Interrupt Set Enable Register           */
       uint32_t RESERVED0[24];                                   
  __IO uint32_t ICER[8];                      /*!< Offset: 0x080  Interrupt Clear Enable Register         */
       uint32_t RSERVED1[24];                                    
  __IO uint32_t ISPR[8];                      /*!< Offset: 0x100  Interrupt Set Pending Register          */
       uint32_t RESERVED2[24];                                   
  __IO uint32_t ICPR[8];                      /*!< Offset: 0x180  Interrupt Clear Pending Register        */
       uint32_t RESERVED3[24];                                   
  __IO uint32_t IABR[8];                      /*!< Offset: 0x200  Interrupt Active bit Register           */
       uint32_t RESERVED4[56];                                   
  __IO uint8_t  IP[240];                      /*!< Offset: 0x300  Interrupt Priority Register (8Bit wide) */
       uint32_t RESERVED5[644];                                  
  __O  uint32_t STIR;                         /*!< Offset: 0xE00  Software Trigger Interrupt Register     */
}  NVIC_Type;    

typedef struct
{
  __IO uint32_t EVCR;
  __IO uint32_t MAPR;
  __IO uint32_t EXTICR[4];
  uint32_t RESERVED0;
  __IO uint32_t MAPR2;  
} AFIO_TypeDef;

typedef struct
{
  __IO uint32_t IMR;
  __IO uint32_t EMR;
  __IO uint32_t RTSR;
  __IO uint32_t FTSR;
  __IO uint32_t SWIER;
  __IO uint32_t PR;
} EXTI_TypeDef;

#define NVIC                ((NVIC_Type *)          NVIC_BASE) 
#define SCB                 ((SCB_Type *)           SCB_BASE)
#define AFIO                ((AFIO_TypeDef *) AFIO_BASE)

#define GPIO_PortSourceGPIOC       ((uint8_t)0x02)
#define GPIO_PinSource13           ((uint8_t)0x0D)
#define EXTI                ((EXTI_TypeDef *) EXTI_BASE)













#endif

