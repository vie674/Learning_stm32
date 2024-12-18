/*
 * mag.h
 *
 *  Created on: Dec 2, 2024
 *      Author: hung
 */

#ifndef INC_MAG_H_
#define INC_MAG_H_


#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_conf.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_spi.h"
#include "stm32f1xx_hal_i2c.h"

#define CONFIG_RESA     0x00
#define CONFIG_RESB		0x01
#define MODE_RES		0x02
#define DATA_OUTH_X		0x03
#define DATA_OUTL_X		0x04
#define DATA_OUTH_Y 	0x05
#define DATA_OUTL_Y		0x06
#define DATA_OUTH_Z		0x07
#define DATA_OUTL_Z		0x08
#define STATUS_REGISTER 0x09
#define IDEN_REGA		0x0A
#define IDEN_REGB		0x0B
#define IDEN_REGC		0x0C
#define HMC5883_ADDW	0x3D
#define HMC5883_ADDR    0x3C
#define S1SAMPLE_AVER   0x00
#define S2SAMPLE_AVER	0x20
#define S4SAMPLE_AVER	0x40
#define S8SAMPLE_AVER	0x60
#define CONS_MEAS_MODE 	0x00
#define SING_MEAS_MODE	0x01

void HMC5883_WriteRegister (uint8_t reg,uint8_t data, I2C_HandleTypeDef *hi2c);
void HMC5883_ReadRegister (uint8_t reg,uint8_t numberOfByte,uint8_t *data,I2C_HandleTypeDef *hi2c);
void HMC5883_ConfigRate (uint8_t SAMPLE_AVER,uint8_t DO_RATE ,I2C_HandleTypeDef *hi2c);
void HMC5883_SetMode (uint8_t MODE,I2C_HandleTypeDef *hi2c);
void HMC5883_ReadAllData (int16_t *x, int16_t *y, int16_t *z,I2C_HandleTypeDef *hi2c);
#endif /* INC_MAG_H_ */
