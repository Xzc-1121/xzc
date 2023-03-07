#include <STC12C5A60S2.H>
#include <delay.h>

sbit DATA = P0^0;                      //DHT11温湿度传感器接单片机的P00口
unsigned char Data_TH[5];              //温湿度未格式化数据，包括温湿度、校验值，[0]湿度整数、[1]湿度小数、[2]温度整数、[3]温度小数、[4]校验值
extern char Data_All[4][6];            //总数据，包括温度、湿度、光照强度，[0]温度、[1]湿度、[2]光照强度、[3]人体感应

/**
  * @brief  获取DHT11温湿度传感器的数据
  * @param  无
  * @retval 0：成功，-1、-2、-3、-4：失败
  */
char DHT11_GetData()
{
	int i, j;                   //for循环变量
	int t;                      //超时判断
	unsigned char data_char;    //一次读取的一个字符
	
	DATA = 0;                   //主机发开始信号，拉低总线
	Delay20ms();                //主机拉低总线至少18ms
	DATA = 1;                   //主机拉高总线20~40us
	Delay30us();
	
	t = 80;                     //设置超时等待时间
	while(DATA && t--);         //等待DHT11拉低总线
	if(t == 0)                  //超时
	{
		DATA = 1;
		return -1;                //通信错误退出，返回错误信号：-1
	}
	
	//等80us响应信号
	t = 250;                    //设置超时等待时间
	while(!DATA && t--);        //等待DHT11拉高总线
	if(t == 0)                  //超时
	{
		DATA = 1;
		return -2;                //通信错误退出，返回错误信号：-2
	}

	//等80us响应信号
	t = 250;                    //设置超时等待时间
	while(DATA && t--);         //等待DHT11拉低总线
	if(t == 0)                  //超时
	{
		DATA = 1;
		return -3;                //通信错误退出，返回错误信号：-3
	}
	
	//读取DHT11的数据
	for(i=0; i<5; i++)          //共5次读取，分别读取：湿度整数、湿度小数、温度整数、温度小数、校验值
	{
		for(j=0; j<8; j++)        //1次8个位，即1次1个字符
		{
			//等待50us开始时隙
			t = 150;                //设置超时等待时间
			while(!DATA && t--);    //等待DHT11拉高总线
			if(t == 0)              //超时
			{
				DATA = 1;
				return -4;            //通信错误退出，返回错误信号：-4
			}
			t = 0;                  //记录时间清零
			while(DATA && ++t);     //等待并记录高电平持续时间
			data_char <<= 1;
			if(t > 30)              //高电平持续时间较长(70us)
				data_char += 1;       //传输值为1
		}
		Data_TH[i] = data_char;   //将数据存至Data_TH数组中
	}
	
	Delay30us();                //等待DHT11拉低50us
	Delay30us();
	DATA = 1;                   //结束，拉高总线
	return 0;                   //返回成功信号
}

/**
  * @brief  进行数据校验
  * @param  无
  * @retval 0：正确，-1：错误
  */
char DHT11_Check()
{
	int i;                      //for循环变量
	unsigned int check=0;       //校验和
	
	//累加
	for(i=0; i<4; i++)
		check += Data_TH[i];
	
	//比对
	if((unsigned char)check != Data_TH[4])
		return -1;                //返回错误信号：-1
	else
		return 0;                 //返回正确信号：0
}

/**
  * @brief  获取温度和湿度数据，并格式化
  * @param  无
  * @retval 0：无错误，-1、-2：有错误
  */
char DHT11_GetTemperatureAndHumidity()
{
	if(DHT11_GetData() != 0) //有错误
	{
		return -1;
	}
	if(DHT11_Check() != 0) //有错误
	{
		return -2;
	}
	//无错误，格式化数据
	Data_All[0][0] = Data_TH[2]/10+'0';   //温度十位数
	Data_All[0][1] = Data_TH[2]%10+'0';   //温度个位数
	Data_All[0][2] = '\0';
	Data_All[1][0] = Data_TH[0]/10+'0';   //湿度十位数
	Data_All[1][1] = Data_TH[0]%10+'0';   //湿度个位数
	Data_All[1][2] = '\0';
	return 0;
}