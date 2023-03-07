#include <STC12C5A60S2.H>
#include <delay.h>

sbit HUMAN = P0^3;   //HC-SR505人体红外传感器接单片机的P03口
extern char Data_All[4][6];   //总数据，包括温度、湿度、光照强度，[0]温度、[1]湿度、[2]光照强度、[3]人体感应

/**
  * @brief  获取HC-SR505人体红外传感器的数据，0没人，1有人
  * @param  无
  * @retval 无
  */
void SR505_GetHumanBodyInduction()
{
	if(HUMAN == 0)            //P03收到低电平，则代表没人
	{
		Data_All[3][0] = '0';
	}
	else                      //P03收到高电平，则代表有人
	{
		Data_All[3][0] = '1';
	}
	Data_All[3][1] = '\0';
}