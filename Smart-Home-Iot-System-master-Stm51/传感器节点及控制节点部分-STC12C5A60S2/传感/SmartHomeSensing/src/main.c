#include <STC12C5A60S2.H>
#include <delay.h>
#include <uart.h>
#include <dht11.h>
#include <bh1750.h>
#include <sr505.h>
#include <esp8266.h>

char Data_All[4][6];   //总数据，包括温度、湿度、光照强度，[0]温度、[1]湿度、[2]光照强度、[3]人体感应

void SendAllData();    //输出温度_湿度_光照强度，测试用

// 主函数
void main()
{
	Delay_s(1);       //延时1秒，等待系统稳定
	Uart1_Init();     //串口1初始化
	BH1750_Init();    //BH1750初始化
	ESP8266_Init();   //ESP8266初始化
	Delay_s(1);       //延时1秒，等待系统稳定
	while(1)
	{
		while(DHT11_GetTemperatureAndHumidity()) //获取温度和湿度
		{
			Delay_s(1);
		}
		BH1750_GetLightIntensity(); //获取光照强度
		SR505_GetHumanBodyInduction(); //获取人体感应(是否有人)
		ESP8266_SendDataAll(); //ESP8266向云服务器发送总数据，包括温度、湿度、光照强度、人体感应
		Delay_s(1);
	}
}

// 输出温度_湿度_光照强度，测试用
void SendAllData()
{
	Uart1_SendString(Data_All[0]);
	Uart1_SendString("_");
	Uart1_SendString(Data_All[1]);
	Uart1_SendString("_");
	Uart1_SendString(Data_All[2]);
	Uart1_SendString("_");
	Uart1_SendString(Data_All[3]);
	Uart1_SendString(" ");
}

// 串口1中断函数
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