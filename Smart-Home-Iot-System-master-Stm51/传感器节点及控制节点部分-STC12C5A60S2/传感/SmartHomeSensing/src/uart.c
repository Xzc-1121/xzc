#include <STC12C5A60S2.H>

/**
  * @brief  串口1初始化函数，9600bps@11.0592MHz
  * @param  无
  * @retval 无
  */
void Uart1_Init()
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//独立波特率发生器时钟1T模式
	BRT = 0xDC;		  //设置独立波特率发生器重载值
	AUXR |= 0x01;   //串口1使用独立波特率发生器为波特率发生器
	AUXR |= 0x10;		//启动独立波特率发生器
	EA = 1;         //开总中断
	ES = 1;         //开串口1中断
}

/**
  * @brief  串口1发送一个字符数据
  * @param  ch：1个字符
  * @retval 无
  */
void Uart1_SendChar(unsigned char ch)
{
	TI = 0;
	SBUF = ch;
	while(!TI);
	TI = 0;
}

/**
  * @brief  串口1发送一段字符串数据
  * @param  str：1段字符串
  * @retval 无
  */
void Uart1_SendString(unsigned char *str)
{
	while(*str != '\0')
	{
		Uart1_SendChar(*str);
		str++;
	}
}

/**
  * @brief  串口1中断函数模板
  * @param  无
  * @retval 无
  */
/*
void Uart1_Interrupt() interrupt 4
{
	if(TI) //发送中断
	{
		TI = 0;
		//在此写处理程序
	}
	if(RI) //接收中断
	{
		RI = 0;
		//在此写处理程序
	}
}
*/
