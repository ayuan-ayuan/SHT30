/**
  ******************************************************************************
  * @file           : sht30_config.c
  * 
  ******************************************************************************
  * @attention
  *
  * 函数具体实现SHT30温湿度测量
  ******************************************************************************
  */

#include "sht30_config.h"


float gTemperature,gHumidity;
uint8_t gCommandName[2] = {0x2C,0x06};//指令是触发SHT30进行温湿度测试。
uint8_t gReadBufName[7] = {0};//用来存储STH30模块测试的温湿度数据。

/*
自定义变量：
uint8_t gCommandName[2] = {0x2C,0x06};//指令是触发SHT30进行温湿度测试。
uint8_t gReadBufName[7] = {0};//用来存储STH30模块测试的温湿度数据。

调用HAL_I2C_Master_Transmit()函数，使用I2C总线发送命令给SHT30传感器。具体参数如下：
&hi2c3：指定使用的I2C总线句柄。
0x88：指定SHT30传感器的写入地址。
command：指定要发送的命令数据。
2：指定发送的字节数。
0xFFFF：指定传输超时时间。

		HAL_I2C_Master_Receive(&hi2c3,0x89,read_buf,6,0xFFFF);
调用HAL_I2C_Master_Receive()函数，从SHT30传感器接收数据。具体参数如下：
&hi2c3：指定使用的I2C总线句柄。
0x89：指定SHT30传感器的读取地址。
read_buf：指定接收数据的缓冲区。
6：指定要接收的字节数。
0xFFFF：指定传输超时时间。

temperature_name = 175*(( (read_buf[0] << 8) + read_buf[1] ) / 65535.0)-45;
temperature_name = roundf(temperature_name * 10) / 10.0f;
humidity_name = 100*( (read_buf[3] << 8) + read_buf[4] ) / 65535.0;
humidity_name = roundf(humidity_name * 10) / 10.0f;
temperature_name变量通过将读取的数据进行位移操作，并除以65535.0后乘以175，再减去45，得到实际的温度值。
humidity_name变量通过将读取的数据进行位移操作，并除以65535.0后乘以100，得到实际的湿度值。
最后，通过roundf()函数对温度和湿度进行四舍五入，保留一位小数，将其转换为实际的温度和湿度值，存储在temperature_name和humidity_name变量中。
*/

/*
函数名称：SystemTemperature_Config
函数功能：读取SHT30传感器的温度
参数说明：command-读取指令，read_buf-读取数据缓存
返 回 值：浮点型温度值
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
函数名称：Systemhumidity_Config
函数功能：读取SHT30传感器的湿度
参数说明：command-读取指令，read_buf-读取数据缓存
返 回 值：浮点型湿度值
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
