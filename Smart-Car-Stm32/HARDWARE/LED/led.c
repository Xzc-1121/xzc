#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK 精英STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   
/**
************************************************************
* @file         
* @brief        
* @author    xiaoming
* @date       2022.2.12
* @version  软件V1.4 硬件V1.4
* @note     关于GPIO的初始函数
*
*
*
***********************************************************/

/**
* @brief 初始LED 引脚PC13
* @param 
* @return 
*/
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOC, ENABLE);	 //使能PC13端口时钟
	

	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	    		 //PC13 端口配置, 推挽输出
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOC,GPIO_Pin_13); 						 //PC13 输出高 
}
/**
* @brief 初始TB6612的 AIN1 AIN2 BIN1 BIN2
* @brief 连接AIN1--PB13 AIN2-PB12
						 BIN1--PB1  BIN2--PB0
* @param 
* @return 
*/
void TB6612_GPIO_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_12|GPIO_Pin_1|GPIO_Pin_0;	    		 //LED1-->PE.5 端口配置, 推挽输出
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_12|GPIO_Pin_1|GPIO_Pin_0); 						 //PE.5 输出高 
}
/**
* @brief 超声波SR04Trig GPIO初始化 
* @param 
* @return 
*/
void SR04_GPIO_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	    		 //PA0端口配置, 推挽输出
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOA,GPIO_Pin_0);
}
/**
* @brief 向前无延时
* @param 
* @return 
*/
void Forward(void)
{
		AIN1 =1;
		AIN2 =0;
		BIN1 =1;
		BIN2 =0;
		TIM_SetCompare1(TIM1,1500);	 
	  TIM_SetCompare4(TIM1,1500);

}	
/**
* @brief 向后无延时
* @param 
* @return 
*/
void Backward(void)
{
		AIN1 =0;
		AIN2 =1;
		BIN1 =0;
		BIN2 =1;
		TIM_SetCompare1(TIM1,1500);	 
	  TIM_SetCompare4(TIM1,1500);

}	
/**
* @brief 向右无延时
* @param 
* @return 
*/
void Rightward(void)
{
		AIN1 =1;
		AIN2 =0;
		BIN1 =0;
		BIN2 =1;
		TIM_SetCompare1(TIM1,1500);	 
	  TIM_SetCompare4(TIM1,1500);

}	
/**
* @brief 向左无延时
* @param 
* @return 
*/
void Leftward(void)
{
		AIN1 =0;
		AIN2 =1;
		BIN1 =1;
		BIN2 =0;
		TIM_SetCompare1(TIM1,1500);	 
	  TIM_SetCompare4(TIM1,1500);

}	

  
