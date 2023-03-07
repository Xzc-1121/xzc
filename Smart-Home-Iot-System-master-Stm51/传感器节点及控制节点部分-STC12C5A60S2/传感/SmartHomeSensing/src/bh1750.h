#ifndef __BH1750_H__
#define __BH1750_H__

extern void BH1750_Start();
extern void BH1750_Stop();
extern void BH1750_SendACK(bit ack);
extern bit BH1750_RecvACK();
extern void BH1750_SendByte(unsigned char dat);
extern unsigned char BH1750_RecvByte();
extern void Single_Write_BH1750(unsigned char REG_Address);
extern unsigned char Single_Read_BH1750(unsigned char REG_Address);
extern void Multiple_Read_BH1750();
extern void BH1750_Init();
extern void Conversion(unsigned int temp_data);
extern void BH1750_GetLightIntensity();

#endif
