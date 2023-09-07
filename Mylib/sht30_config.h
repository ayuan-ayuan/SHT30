#ifndef __SHT30_CONFIG_H_
#define __SHT30_CONFIG_H_

#include "math.h"
#include "i2c.h"
#include "math.h"

extern float gTemperature,gHumidity;
extern uint8_t gCommandName[2];
extern uint8_t gReadBufName[7];

float SystemTemperature_Config(uint8_t command[],uint8_t read_buf[]);//ʵ��SHT30�¶ȵĲ��Ժͽ��չ���
float Systemhumidity_Config(uint8_t command[],uint8_t read_buf[]);	//ʵ��SHT30ʪ�ȵĲ��Ժͽ��չ���
#endif
