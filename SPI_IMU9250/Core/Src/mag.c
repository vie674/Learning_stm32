/*
 * mag.c
 *
 *  Created on: Dec 2, 2024
 *      Author: hung
 */
#include "mag.h"
void HMC5883_WriteRegister (uint8_t reg,uint8_t data, I2C_HandleTypeDef *hi2c)
{
	HAL_I2C_Mem_Write(hi2c, HMC5883_ADDW, reg, 1, &data, 1, 100);
}
void HMC5883_ReadRegister (uint8_t reg,uint8_t numberOfByte,uint8_t *data,I2C_HandleTypeDef *hi2c)
{
	HAL_I2C_Mem_Read(hi2c, HMC5883_ADDR, reg, 1, data, numberOfByte, 100);
}
void HMC5883_ConfigRate (uint8_t SAMPLE_AVER,uint8_t DO_RATE ,I2C_HandleTypeDef *hi2c)
{
	//default is 15Hz and 1 sample aver
	HMC5883_WriteRegister(CONFIG_RESA,SAMPLE_AVER|DO_RATE, hi2c);
}
	//Config register B keep default;
void HMC5883_SetMode (uint8_t MODE,I2C_HandleTypeDef *hi2c)
{
	//defautl is single measure mode
	HMC5883_WriteRegister(MODE_RES, MODE, hi2c);
}
void HMC5883_ReadAllData (int16_t *x, int16_t *y, int16_t *z,I2C_HandleTypeDef *hi2c)
{
	uint8_t data[6];
	uint8_t reg = DATA_OUTH_X;

	HMC5883_ReadRegister(reg, 6,data, hi2c);

	// Combine MSB and LSB for each axis
	*x = (int16_t)((data[0] << 8) | data[1]);
	*z = (int16_t)((data[2] << 8) | data[3]);
	*y = (int16_t)((data[4] << 8) | data[5]);
}
