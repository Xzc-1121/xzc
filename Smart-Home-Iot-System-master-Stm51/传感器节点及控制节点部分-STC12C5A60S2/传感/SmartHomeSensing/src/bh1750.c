#include <STC12C5A60S2.H>
#include <delay.h>

// 定义器件在IIC总线中的从地址,根据ALT ADDRESS地址引脚不同修改
//#define SlaveAddress 0x46 //ALT ADDRESS引脚接地时地址为0x46
#define SlaveAddress 0xB8 //ALT ADDRESS引脚接电源时地址为0xB8

sbit SCL = P0^1;            //BH1750光照强度传感器的SCL(IIC总线时钟)引脚接单片机的P01口
sbit SDA = P0^2;            //BH1750光照强度传感器的SDA(IIC总线数据)引脚接单片机的P02口
unsigned char BUF[8];       //接收数据缓存区
extern char Data_All[4][6]; //总数据，包括温度、湿度、光照强度，[0]温度、[1]湿度、[2]光照强度、[3]人体感应

// 起始信号
void BH1750_Start()
{
	SDA = 1;                    //拉高数据线
	SCL = 1;                    //拉高时钟线
	Delay5us();                 //延时
	SDA = 0;                    //产生下降沿
	Delay5us();                 //延时
	SCL = 0;                    //拉低时钟线
}

// 停止信号
void BH1750_Stop()
{
	SDA = 0;                    //拉低数据线
	SCL = 1;                    //拉高时钟线
	Delay5us();                 //延时
	SDA = 1;                    //产生上升沿
	Delay5us();                 //延时
}

// 发送应答信号，入口参数:ack(0:ACK 1:NAK)
void BH1750_SendACK(bit ack)
{
	SDA = ack;                  //写应答信号
	SCL = 1;                    //拉高时钟线
	Delay5us();                 //延时
	SCL = 0;                    //拉低时钟线
	Delay5us();                 //延时
}

// 接收应答信号
bit BH1750_RecvACK()
{
	SCL = 1;                    //拉高时钟线
	Delay5us();                 //延时
	CY = SDA;                   //读应答信号
	SCL = 0;                    //拉低时钟线
	Delay5us();                 //延时
	return CY;
}

// 向IIC总线发送一个字节数据
void BH1750_SendByte(unsigned char dat)
{
	unsigned char i;
	for(i=0; i<8; i++)          //8位计数器
	{
		dat <<= 1;                //移出数据的最高位
		SDA = CY;                 //送数据口
		SCL = 1;                  //拉高时钟线
		Delay5us();               //延时
		SCL = 0;                  //拉低时钟线
		Delay5us();               //延时
	}
	BH1750_RecvACK();
}

// 从IIC总线接收一个字节数据
unsigned char BH1750_RecvByte()
{
	unsigned char i;
	unsigned char dat = 0;
	SDA = 1;                    //使能内部上拉,准备读取数据,
	for(i=0; i<8; i++)          //8位计数器
	{
		dat <<= 1;
		SCL = 1;                  //拉高时钟线
		Delay5us();               //延时
		dat |= SDA;               //读数据               
		SCL = 0;                  //拉低时钟线
		Delay5us();               //延时
	}
	return dat;
}

void Single_Write_BH1750(unsigned char REG_Address)
{
	BH1750_Start();                  //起始信号
	BH1750_SendByte(SlaveAddress);   //发送设备地址+写信号
	BH1750_SendByte(REG_Address);    //内部寄存器地址，
	//BH1750_SendByte(REG_data);       //内部寄存器数据，
	BH1750_Stop();                   //发送停止信号
}

// 单字节读取
unsigned char Single_Read_BH1750(unsigned char REG_Address)
{
	unsigned char REG_data;
	BH1750_Start();                          //起始信号
	BH1750_SendByte(SlaveAddress);           //发送设备地址+写信号
	BH1750_SendByte(REG_Address);            //发送存储单元地址，从0开始	
	BH1750_Start();                          //起始信号
	BH1750_SendByte(SlaveAddress+1);         //发送设备地址+读信号
	REG_data=BH1750_RecvByte();              //读出寄存器数据
	BH1750_SendACK(1);   
	BH1750_Stop();                           //停止信号
	return REG_data; 
}

// 连续读出BH1750内部数据
void Multiple_Read_BH1750()
{
	unsigned char i;	
	BH1750_Start();                          //起始信号
	BH1750_SendByte(SlaveAddress+1);         //发送设备地址+读信号
	for(i=0; i<3; i++)                       //连续读取2个地址数据，存储中BUF
	{
		BUF[i] = BH1750_RecvByte();            //BUF[0]存储0x32地址中的数据
		if(i == 3)
		{
			BH1750_SendACK(1);                   //最后一个数据需要回NOACK
		}
		else
		{		
			BH1750_SendACK(0);                   //回应ACK
		}
	}
	BH1750_Stop();                           //停止信号
	Delay5ms();
}

// 初始化BH1750
void BH1750_Init()
{
	Single_Write_BH1750(0x01);  
}

// 光照强度数据格式化
void Conversion(unsigned int temp_data)
{  
	Data_All[2][0] = temp_data/10000+0x30;   //万
	temp_data = temp_data%10000;
	Data_All[2][1] = temp_data/1000+0x30;    //千
	temp_data = temp_data%1000;
	Data_All[2][2] = temp_data/100+0x30;     //百
	temp_data = temp_data%100;
	Data_All[2][3] = temp_data/10+0x30;      //十
	temp_data = temp_data%10;
	Data_All[2][4] = temp_data+0x30;         //个
	Data_All[2][5] = '\0';
}

// 获取光照强度数据，并格式化
void BH1750_GetLightIntensity()
{
	int dis_data;
	float temp;
	Single_Write_BH1750(0x01);         //power on
  Single_Write_BH1750(0x10);         //H - resolution mode
	Delay_ms(200);
	Multiple_Read_BH1750();            //连续读出数据，存储在BUF中
	dis_data = BUF[0];
	dis_data = (dis_data<<8)+BUF[1];   //合成数据，即光照数据
	temp = (float)dis_data/1.2;
	Conversion(temp);                  //计算数据
}
