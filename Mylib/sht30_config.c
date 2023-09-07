/**
  ******************************************************************************
  * @file           : sht30_config.c
  * 
  ******************************************************************************
  * @attention
  *
  * ��������ʵ��SHT30��ʪ�Ȳ���
  ******************************************************************************
  */

#include "sht30_config.h"


float gTemperature,gHumidity;
uint8_t gCommandName[2] = {0x2C,0x06};//ָ���Ǵ���SHT30������ʪ�Ȳ��ԡ�
uint8_t gReadBufName[7] = {0};//�����洢STH30ģ����Ե���ʪ�����ݡ�

/*
�Զ��������
uint8_t gCommandName[2] = {0x2C,0x06};//ָ���Ǵ���SHT30������ʪ�Ȳ��ԡ�
uint8_t gReadBufName[7] = {0};//�����洢STH30ģ����Ե���ʪ�����ݡ�

����HAL_I2C_Master_Transmit()������ʹ��I2C���߷��������SHT30������������������£�
&hi2c3��ָ��ʹ�õ�I2C���߾����
0x88��ָ��SHT30��������д���ַ��
command��ָ��Ҫ���͵��������ݡ�
2��ָ�����͵��ֽ�����
0xFFFF��ָ�����䳬ʱʱ�䡣

		HAL_I2C_Master_Receive(&hi2c3,0x89,read_buf,6,0xFFFF);
����HAL_I2C_Master_Receive()��������SHT30�������������ݡ�����������£�
&hi2c3��ָ��ʹ�õ�I2C���߾����
0x89��ָ��SHT30�������Ķ�ȡ��ַ��
read_buf��ָ���������ݵĻ�������
6��ָ��Ҫ���յ��ֽ�����
0xFFFF��ָ�����䳬ʱʱ�䡣

temperature_name = 175*(( (read_buf[0] << 8) + read_buf[1] ) / 65535.0)-45;
temperature_name = roundf(temperature_name * 10) / 10.0f;
humidity_name = 100*( (read_buf[3] << 8) + read_buf[4] ) / 65535.0;
humidity_name = roundf(humidity_name * 10) / 10.0f;
temperature_name����ͨ������ȡ�����ݽ���λ�Ʋ�����������65535.0�����175���ټ�ȥ45���õ�ʵ�ʵ��¶�ֵ��
humidity_name����ͨ������ȡ�����ݽ���λ�Ʋ�����������65535.0�����100���õ�ʵ�ʵ�ʪ��ֵ��
���ͨ��roundf()�������¶Ⱥ�ʪ�Ƚ����������룬����һλС��������ת��Ϊʵ�ʵ��¶Ⱥ�ʪ��ֵ���洢��temperature_name��humidity_name�����С�
*/

/*
�������ƣ�SystemTemperature_Config
�������ܣ���ȡSHT30���������¶�
����˵����command-��ȡָ�read_buf-��ȡ���ݻ���
�� �� ֵ���������¶�ֵ
*/
float SystemTemperature_Config(uint8_t command[],uint8_t read_buf[])
{
	float temperature_name;
		HAL_I2C_Master_Transmit(&hi2c3,0x88,command,2,0xFFFF);
		HAL_I2C_Master_Receive(&hi2c3,0x89,read_buf,6,0xFFFF);
		temperature_name = 175*(( (read_buf[0] << 8) + read_buf[1] ) / 65535.0)-45;
		temperature_name = roundf(temperature_name * 10) / 10.0f;
	return temperature_name;
}

/*
�������ƣ�Systemhumidity_Config
�������ܣ���ȡSHT30��������ʪ��
����˵����command-��ȡָ�read_buf-��ȡ���ݻ���
�� �� ֵ��������ʪ��ֵ
*/
float  Systemhumidity_Config(uint8_t command[],uint8_t read_buf[])
{
		float humidity_name;
		HAL_I2C_Master_Transmit(&hi2c3,0x88,command,2,0xFFFF);
		HAL_I2C_Master_Receive(&hi2c3,0x89,read_buf,6,0xFFFF);
		humidity_name = 100*( (read_buf[3] << 8) + read_buf[4] ) / 65535.0;
		humidity_name = roundf(humidity_name* 10) / 10.0f;
	return humidity_name;
}
