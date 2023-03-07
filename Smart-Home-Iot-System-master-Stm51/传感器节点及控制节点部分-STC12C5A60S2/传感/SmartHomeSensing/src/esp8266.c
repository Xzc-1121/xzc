#include <string.h>
#include <delay.h>
#include <uart.h>

extern char Data_All[4][6];   //总数据，包括温度、湿度、光照强度，[0]温度、[1]湿度、[2]光照强度、[3]人体感应

/**
  * @brief  ESP8266初始化函数
  * @param  无
  * @retval 无
  */
void ESP8266_Init()
{
	//设置波特率为9600
	//Uart1_SendString("AT+UART=9600,8,1,0,0\r\n");
	//Delay_s(2);
	
	//设置为STA+AP模式，即可作为客户端，也可作为服务端
	//Uart1_SendString("AT+CWMODE=3\r\n");
	//Delay_s(2);
	
	//连接WiFi
	//Uart1_SendString("AT+CWJAP=\"xiumu\",\"123456xiumu\"\r\n");
	//Delay_s(2);
	
	//设置时域和SNTP服务器
	Uart1_SendString("AT+CIPSNTPCFG=1,8,\"ntp1.aliyun.com\"\r\n");
	Delay_s(2);
	
	//配置MQTT用户属性
	Uart1_SendString("AT+MQTTUSERCFG=0,1,\"NULL\",\"ESP8266&hbwva3ZqZy3\",\"E3FE6E3EDE52D12C34FBE4944F2EF3EF2EB1C457\",0,0,\"\"\r\n");
	Delay_s(2);
	
	//配置MQTT客户端ID
	Uart1_SendString("AT+MQTTCLIENTID=0,\"02020|securemode=3\\,signmethod=hmacsha1|\"\r\n");
	Delay_s(2);
	
	//连接MQTT Broker
	Uart1_SendString("AT+MQTTCONN=0,\"hbwva3ZqZy3.iot-as-mqtt.cn-shanghai.aliyuncs.com\",1883,1\r\n");
	Delay_s(2);
}

/**
  * @brief  //ESP8266向云服务器发送总数据，包括温度、湿度、光照强度
  * @param  无
  * @retval 无
  */
void ESP8266_SendDataAll()
{
	char str[250] = "AT+MQTTPUB=0,\"/sys/hbwva3ZqZy3/ESP8266/thing/event/property/post\",\"{\\\"method\\\":\\\"thing.event.property.post\\\"\\,\\\"params\\\":{\\\"Temperature\\\":";
	strcat(str, Data_All[0]); //温度
	strcat(str, "\\,\\\"Humidity\\\":");
	strcat(str, Data_All[1]); //湿度
	strcat(str, "\\,\\\"LightIntensity\\\":");
	strcat(str, Data_All[2]); //光照强度
	strcat(str, "\\,\\\"HumanBodyInduction\\\":");
	strcat(str, Data_All[3]); //人体感应
	strcat(str, "}}\",1,0\r\n");
	Uart1_SendString(str);
	Delay_s(1);
}
