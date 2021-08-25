#include"inc.h"

//按照系统初始化来配置的，HSE外部72M时钟
void SysClock()
{
  volatile uint32_t StartUpCounter = 0, HSEStatus = 0;

  // Set HSION bit
  RCC_CR |= (uint32_t)0x00000001;
  // Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits 
  RCC_CFGR &= (uint32_t)0xF0FF0000;
  // Reset HSEON, CSSON and PLLON bits
  RCC_CR &= (uint32_t)0xFEF6FFFF;//1111  1110  1111  0110  1111  1111  1111  1111
  // Reset HSEBYP bit 
  RCC_CR &= (uint32_t)0xFFFBFFFF;//1111  1111  1111  1011  1111  1111  1111  1111
  // Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits 
  RCC_CFGR &= (uint32_t)0xFF80FFFF;//1111 1111 1000 0000 1111  1111  1111 1111
  // Disable all interrupts and clear pending bits
  RCC_CIR = 0x009F0000;

  /* Reset HSEON bit */
  RCC_CR &= ((uint32_t)0xFFFEFFFF);
  /* Reset HSEBYP bit */
  RCC_CR &= ((uint32_t)0xFFFBFFFF);
  // 使能 HSE
  RCC_CR |= (1<<16);  //0x0001 0000
  //Led_Init();
  //LED_OFF;
  do
  {
    HSEStatus = (RCC_CR & (1<<17));  //0x0002 0000
    StartUpCounter++;  
  } while((HSEStatus == 0) && (StartUpCounter !=((uint32_t)0xFFFF)));

  if(HSEStatus != 0)
  {
    FLASH_ACR |= ((uint8_t)0x10);//使能FLASH预存取缓存区
    FLASH_ACR &= (uint32_t)((uint32_t)~((uint8_t)0x03));
    FLASH_ACR |= (uint32_t)((uint8_t)0x02); 

    //PLLXTPRE不分频
    RCC_CFGR &= ~(1<<17);

    // HCLK = SYSCLK
    RCC_CFGR &= (uint32_t)(0xFFFFFF0F);
    RCC_CFGR |= (uint32_t)(0x00000000);
    // PCLK2 = HCLK 
    RCC_CFGR &= (uint32_t)(0xFFFFc7FF);
    RCC_CFGR |= (uint32_t)(0x00000000);
    // PCLK1 = HCLK 
    RCC_CFGR &= (uint32_t)(0xFFFFF8FF);
    RCC_CFGR |= (uint32_t)(0x00000400);//100 0000 0000

    //关闭锁相环
    RCC_CR &= ~(1<<24); 
    //PLLXTPRE  PLLSRC  PLLMUL清零
    RCC_CFGR &= ((uint32_t)0xFFC0FFFF);//1111  1111  1100  0000  1111  1111  1111  1111
    //PLLXTPRE不分频
    RCC_CFGR &= ~(1<<17);
    //PLLSRC选择外部HSE
    RCC_CFGR |= (1<<16);
    //设置倍频
    RCC_CFGR |= (uint32_t)(0x001C0000);//0111 00  0000  0000  0000  0000
    //LED_Blue_ON;
    // 使能锁相环
    RCC_CR |= (1<<24);
    //等待PLL就绪
    StartUpCounter = 0;
    HSEStatus = 0;
    do
    {
      HSEStatus = (RCC_CR & (1<<25));
      StartUpCounter++;
    } while((HSEStatus == 0) && (StartUpCounter !=((uint32_t)0xFF)));

    //SW系统时钟选择PLL
    RCC_CFGR &= (uint32_t)(0xFFFFFFFC);
    RCC_CFGR |= (uint32_t)(0x00000002);
    //等待系统接入PLL
    StartUpCounter = 0;
    HSEStatus = 0;
    do
    {
      HSEStatus = (RCC_CFGR & (uint32_t)0x0000000C);
      StartUpCounter++;
    } while((HSEStatus != (uint32_t)0x06) && (StartUpCounter !=((uint32_t)0xF)));
    //LED_Green_ON;
  }
  else
  { // If HSE fails to start-up, the application will have wrong clock configuration. User can add here some code to deal with this error 
      //LED_Red_ON;
      //LED_Blue_ON;
      //LED_Green_ON;
  }
}


/*
//使用内部时钟HSI，第三版,不可用
void SysClock()
{
  uint32_t StartUpCounter = 0, HSEStatus = 0;
  // Set HSION bit 
  RCC_CR |= (uint32_t)0x00000001;
  // Reset HSEON, CSSON and PLLON bits 
  RCC_CR &= (uint32_t)0xFEF6FFFF;
  // Reset HSEBYP bit 
  //RCC_CR &= (uint32_t)0xFFFBFFFF;
  // Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits 
  RCC_CFGR &= (uint32_t)0xFF80FFFF;

  // 使能 HSI
  RCC_CR |= ((uint32_t)0x00000001);  
  do
  {
    HSEStatus = (RCC_CR & ((uint32_t)0x00000002)); 
    StartUpCounter++;  
  } while((HSEStatus == 0) && (StartUpCounter !=((uint16_t)0x0500)));

  if(HSEStatus != 0)
  {
    FLASH_ACR |= ((uint8_t)0x10);
    FLASH_ACR &= (uint32_t)((uint32_t)~((uint8_t)0x03));
    FLASH_ACR |= (uint32_t)((uint8_t)0x02); 

    //AHB 分频1
    //RCC_CFGR &= ((uint32_t)0xFFFFFF0F);
    RCC_CFGR |= ((uint32_t)0x00000000);
    //APB2 1分频
    //RCC_CFGR &= ((uint32_t)0xFFFFC7FF);
    RCC_CFGR |= ((uint32_t)0x00000000);
    //APB1 2分频
    //RCC_CFGR &= ((uint32_t)0xFFFFF8FF);
    RCC_CFGR |= ((uint32_t)0x00000400);
    
    RCC_CFGR &= ((uint32_t)0xFFC0FFFF);
    RCC_CFGR |= (((uint32_t)0x00000000) | ((uint32_t)0x00380000));
    //使能PLL
    RCC_CR |= (1<<24);
    //等待PLL就绪
    while((RCC_CR & (1<<25) == 0))
      {
      }

    RCC_CFGR &= ((uint32_t)0xFFFFFFFC);
    RCC_CFGR |= ((uint32_t)0x00000002);

    //系统选择PLL位
    while ((RCC_CFGR & (uint32_t)0x0000000C) != (uint32_t)0x08)
        {
        }
    //设置GPIOA8
    RCC_APB2ENR |= (1<<2);
    //清空控制PA8的端口位
    GPIOA_CRH &= ~( 0x0F<< (4*0));	
    // 配置PA8为复用推挽输出，速度为50M 1011
    GPIOA_CRH |= (0x0B<<4*0);

    //MCO 系统时钟
    //RCC_CFGR |= ((uint8_t)0x06);

    *(uint8_t *)CFGR_BYTE4_ADDRESS = ((uint8_t)0x05);
  }
}*/