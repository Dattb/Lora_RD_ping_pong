/*
 * sht30_sensor.c
 *
 *  Created on: Jul 18, 2021
 *      Author: PC5
 */

//#include "main.h"
#include "sht30_sensor.h"


extern I2C_HandleTypeDef hi2c1;


//
//

sht30_i2c_receive_data_tdef sht30_read_i2c_data(){

	 unsigned char I2C_Rx_data_buff[7] = {0};
	 unsigned char I2C_Tx_data_buff[2] = {0x2C,0x0D};

	  HAL_I2C_Master_Transmit(&hi2c1, SHT30_I2C_ADDR, (unsigned char *)I2C_Tx_data_buff, 2, 100);
	  //HAL_I2C_Mem_Write(&hi2c1, SHT30_I2C_ADDR, 0, 0, (uint8_t *)I2C_Tx_data_buff, 4, 100);
	  HAL_Delay(13);
	  //HAL_I2C_Master_Transmit(&hi2c2, SHT30_I2C_ADDR, (uint8_t *)I2C_Tx_data_buff, 3, 1000);
	  HAL_I2C_Master_Receive(&hi2c1, SHT30_I2C_ADDR, (unsigned char *)I2C_Rx_data_buff, 7, 100);
	  sht30_i2c_receive_data_tdef *point;
	  point = (sht30_i2c_receive_data_tdef *) I2C_Rx_data_buff;
	  return *point;

}


unsigned char RD_sht30_crc_check (unsigned char data0,unsigned char data1)
{
	unsigned char data[2];
	data[0] =data0;
	data[1] =data1;
	unsigned char nbrOfBytes = 2;
	unsigned char bit;        // bit mask
	unsigned char  crc = 0xFF; // calculated checksum
	unsigned char byteCtr;    // byte counter

	// calculates 8-Bit checksum with given polynomial
	for(byteCtr = 0; byteCtr < nbrOfBytes; byteCtr++) {
		crc ^= (data[byteCtr]);
		for(bit = 8; bit > 0; --bit) {
			if(crc & 0x80) {
				crc = (crc << 1) ^ (0x131);
			}
			else {
				crc = (crc << 1);
			}
		}
	}

	return crc;
}



sht30_data_tdef RD_sht30_caculate_data (sht30_i2c_receive_data_tdef raw_data ){
	sht30_data_tdef real_data = {0};
	if(raw_data.crc_temp == RD_sht30_crc_check(raw_data.temp_hi,raw_data.temp_low)&&\
	   raw_data.crc_hum == RD_sht30_crc_check(raw_data.hum_hi,raw_data.hum_low)	){
		unsigned int temp_raw = raw_data.temp_hi<<8|raw_data.temp_low;
		unsigned int hum_raw = raw_data.hum_hi<<8|raw_data.hum_low;
		real_data.tempurature = (float)temp_raw/65535*175-45; // cong thuc tinh cua hang
		real_data.humitidy = (float)hum_raw/65535*100;		  // cong thuc tinh cua hang
	}
	return real_data;
}
