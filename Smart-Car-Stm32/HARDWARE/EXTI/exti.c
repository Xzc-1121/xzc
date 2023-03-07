#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"

/**
************************************************************
* @file         
* @brief        
* @author    xiaoming
* @date       2022.2.12
* @version  软件V1.4 硬件V1.4
* @note   按键的外部中断初始化
*
*
*
***********************************************************/

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK精英STM32开发板
//外部中断 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   
//外部中断0服务程序
void EXTIX_Init(void)
{
 
   	EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	按键端口初始化

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟



   //GPIOA.12	  中断线以及中断初始化配置 下降沿触发 KEY2
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource12);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line12;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


   //GPIOA.7	  中断线以及中断初始化配置 上升沿触发 KEY1
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7); 

  	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键KEY1所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

}
/**
* @brief 按键KEY1 PA7 中断处理函数
* @param 
* @return 
*/
void EXTI9_5_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY1==1)	 //按键KEY1 PA7
	{
		if(Mode == 4) Mode =1;
		else Mode = Mode +1;
		LED=!LED;

	}		 
	EXTI_ClearITPendingBit(EXTI_Line7);  //清除LINE4上的中断标志位  
}

/**
* @brief 按键KEY2 PA12 中断处理函数
* @param 
* @return 
*/
void EXTI15_10_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(KEY2==0)	 //按键KEY2
	{
		Mode = 0;
		LED=!LED;
	}		 
	EXTI_ClearITPendingBit(EXTI_Line12);  //清除LINE4上的中断标志位  
}

