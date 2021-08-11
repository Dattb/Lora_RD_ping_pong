/*
 * max44009_sensor.c
 *
 *  Created on: Jul 18, 2021
 *      Author: PC5
 */


#include "max44009_sensor.h"
#include "math.h"

extern I2C_HandleTypeDef hi2c1;

uint32_t RD_I2C_Read_light (){
	
	unsigned char i2c_SHT30_rx_buff1[2] = {0};	// control command
	unsigned char i2c_SHT30_rx_buff2[2] = {0};	// control command

	HAL_I2C_Mem_Read(&hi2c1,MAX44009_I2C_ADDR,0x03,1,(uint8_t *)i2c_SHT30_rx_buff1,2,100);
	HAL_I2C_Mem_Read(&hi2c1,MAX44009_I2C_ADDR,0x04,1,(uint8_t *)i2c_SHT30_rx_buff2,2,100);
	
	return Max44009_calculate_data(*i2c_SHT30_rx_buff1,*i2c_SHT30_rx_buff2);
	
}



uint32_t Max44009_calculate_data (unsigned char reg_hi,unsigned char reg_low) {
	Max44009_data_tdef S_data ;
	S_data.raw_data = reg_hi<<8|reg_low;
	
	return lux_calculate(S_data);
}




uint32_t lux_calculate (Max44009_data_tdef data){
	unsigned int mantissa = data.mantissa_hi<<4|data.mantissa_low;
	return (unsigned long)(pow(2,data.exponent)*0.045*mantissa);
}
