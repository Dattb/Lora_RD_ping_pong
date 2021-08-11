/*
 * sht30_sensor.h
 *
 *  Created on: Jul 18, 2021
 *      Author: PC5
 */
#include "main.h"
#ifndef SRC_RANG_DONG_SHT30_SENSOR_H_
#define SRC_RANG_DONG_SHT30_SENSOR_H_

#define SHT30_I2C_ADDR			0x88

typedef struct {
	unsigned char temp_hi;
	unsigned char temp_low;
	unsigned char crc_temp;
	unsigned char hum_hi;
	unsigned char hum_low;
	unsigned char crc_hum;
}sht30_i2c_receive_data_tdef;

typedef struct {
	float tempurature;
	float humitidy;
}sht30_data_tdef;

sht30_i2c_receive_data_tdef sht30_read_i2c_data();
unsigned char RD_sht30_crc_check (unsigned char data0,unsigned char data1);
sht30_data_tdef RD_sht30_caculate_data (sht30_i2c_receive_data_tdef raw_data );
#endif /* SRC_RANG_DONG_SHT30_SENSOR_H_ */
