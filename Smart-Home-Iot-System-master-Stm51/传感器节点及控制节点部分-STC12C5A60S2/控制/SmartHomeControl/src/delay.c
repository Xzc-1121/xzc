#include <INTRINS.H>

/**
  * @brief  通用延时函数，单位微秒us
  * @param  time：延时微秒数
  * @retval 无
  */
void Delay_us(unsigned int time)
{
	while(time--)
	{
		_nop_();
	}
}

/**
  * @brief  通用延时函数，单位毫秒ms
  * @param  time：延时毫秒数
  * @retval 无
  */
void Delay_ms(unsigned int time)
{
	unsigned char i, j;
	while(time--)
	{
		_nop_();
		i = 11;
		j = 190;
		do
		{
			while(--j);
		} while(--i);
	}
}

/**
  * @brief  通用延时函数，单位秒s
  * @param  time：延时秒数
  * @retval 无
  */
void Delay_s(unsigned int time)
{
	unsigned char i, j, k;
	while(time--)
	{
		i = 43;
		j = 6;
		k = 203;
		do
		{
			do
			{
				while(--k);
			} while(--j);
		} while(--i);
	}
}

/**
  * @brief  专用延时函数，延时5us
  * @param  无
  * @retval 无
  */
void Delay5us()
{
	unsigned char i;
	_nop_();
	_nop_();
	_nop_();
	i = 10;
	while(--i);
}

/**
  * @brief  专用延时函数，延时30us
  * @param  无
  * @retval 无
  */
void Delay30us()
{
	unsigned char i;
	i = 80;
	while(--i);
}

/**
  * @brief  专用延时函数，延时5ms
  * @param  无
  * @retval 无
  */
void Delay5ms()
{
	unsigned char i, j;
	_nop_();
	_nop_();
	i = 54;
	j = 198;
	do
	{
		while(--j);
	} while(--i);
}

/**
  * @brief  专用延时函数，延时20ms
  * @param  无
  * @retval 无
  */
void Delay20ms()
{
	unsigned char i, j;
	_nop_();
	_nop_();
	i = 216;
	j = 36;
	do
	{
		while(--j);
	} while(--i);
}
