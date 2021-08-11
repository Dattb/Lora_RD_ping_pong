/*
 * sht30_sensor.h
 *
 *  Created on: Jul 18, 2021
 *      Author: PC5
 */
#include "main.h"

#define MAX44009_I2C_ADDR			(0x4a<<1)

typedef struct{
	union{
		uint16_t raw_data;
		struct{
			uint16_t mantissa_low		:4; // 4 bit lowest
			uint16_t not_use				:4; 
			uint16_t mantissa_hi		:4; 
			uint16_t exponent				:4; // 4 bit hightest
		};
	};
}Max44009_data_tdef;


uint32_t RD_I2C_Read_light();
uint32_t lux_calculate (Max44009_data_tdef data);
uint32_t Max44009_calculate_data(unsigned char reg_hi,unsigned char reg_low);

