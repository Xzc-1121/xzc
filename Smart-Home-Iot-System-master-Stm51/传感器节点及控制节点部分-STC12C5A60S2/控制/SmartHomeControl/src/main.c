#include <STC12C5A60S2.H>
#include <delay.h>
#include <uart.h>
#include <string.h>

int Index; //字符串有效字符的索引
char Message[250]; //串口接收的字符串
char MainLampSwitch='0', FanSwitch='0', AlarmSwitch='0'; //主灯开关、风扇开关、警报器开关，0关、1开

void StringInit(); //串口接收的字符串初始化

void main()
{
	Uart1_Init(); //串口1初始化
	StringInit(); //串口接收的字符串初始化
	P0M1 &= ~(1<<2), P0M0 |= (1<<2); //设置单片机P02口为强推挽输出模式
	while(1)
	{
		
	}
}

// 串口接收的字符串初始化
void StringInit()
{
	int i;
	Index = 0;
	for(i=0; i<sizeof(Message); i++)
	{
		Message[i] = '\0';
	}
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
		int currentIndex = Index; //当前索引
		RI = 0; //接收中断标志位置0
		//拼接字符串，若开头为'+'，则索引加一继续拼接字符串；否则继续将字符放至索引0处
		Message[Index] = SBUF;
		if(Message[0] == '+')
			Index++;
		else
			Index=0;
		//当字符串是以'+'开头的指令，且拼接完最后一个字符时
		if(currentIndex>0 && Message[currentIndex-1]=='\r' && Message[currentIndex]=='\n')
		{
			const char *info = "+MQTTSUBRECV"; //从云服务器发来的控制指令是以"+MQTTSUBRECV"开头的
			//若是以"+MQTTSUBRECV"开头的控制指令，则进行开关参数的提取，并进行相应控制
			if(strncmp(Message,info,12) == 0)
			{
				int i;
				char *s = NULL;
				const char *lamp = "\"MainLampSwitch\":";
				const char *fan = "\"FanSwitch\":";
				const char *alarm = "\"AlarmSwitch\":";
				//提取开关参数
				for(i=130; Message[i+18]!='\r'; i++)
				{
					char *s = &Message[i];
					if(strncmp(s,lamp,17) == 0)
					{
						MainLampSwitch = Message[i+17];
					}
					if(strncmp(s,fan,12) == 0)
					{
						FanSwitch = Message[i+12];
					}
					if(strncmp(s,alarm,14) == 0)
					{
						AlarmSwitch = Message[i+14];
					}
				}
				//控制主灯开关
				if(MainLampSwitch == '1')
				{
					P00 = 0;
				}
				else if(MainLampSwitch == '0')
				{
					P00 = 1;
				}
				//控制风扇开关
				if(FanSwitch == '1')
				{
					P02 = 0;
				}
				else if(FanSwitch == '0')
				{
					P02 = 1;
				}
				//控制报警器开关
				if(AlarmSwitch == '1')
				{
					P04 = 0;
				}
				else if(AlarmSwitch == '0')
				{
					P04 = 1;
				}
			}
			//清空字符串，初始化
			StringInit();
		}
	}
}