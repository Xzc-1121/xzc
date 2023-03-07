#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK精英STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5	


#define LED PCout(13)// PE5	

#define AIN1 PBout(13)// PE5	
#define AIN2 PBout(12)// PE5	
#define BIN1 PBout(1)// PE5	
#define BIN2 PBout(0)// PE5	

#define SR04 PAout(0)





void LED_Init(void);//初始化


void TB6612_GPIO_Init(void);
void Forward(void);
void Backward(void);
void Rightward(void);
void Leftward(void);
void SR04_GPIO_Init(void);//超声波PA0

		 				    
#endif
