/*******************************************************************************
 * @file  imu.h
 * @brief This file contain macro for imu.c
 *  Created on: Nov 22, 2024
 *      Author: Do Quoc Viet
 *
 *******************************************************************************/

#ifndef __IMU_H_
#define __IMU_H_
// Include
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_conf.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_spi.h"
#include "stm32f1xx_hal_i2c.h"
//True - False
#define IM_OK              1
#define IM_NOT_OK         -1
#define LPF_GYRO250Hz     0x00
#define LPF_GYRO184Hz     0x01
#define LPF_GYRO92Hz      0x02
#define LPF_GYRO41Hz      0x03
#define LPF_GYRO20Hz      0x04
#define LPF_GYRO10Hz      0x05
#define LPF_GYRO5Hz       0x06
#define LPF_GYRO3600Hz    0x07
#define SCALE250DPS       0x00
#define SCALE500DPS 	  0x08
#define SCALE1000DPS 	  0x10
#define SCALE2000DPS 	  0x18
#define LPF_ACCER218Hz    0x01
#define LPF_ACCER99Hz     0x02
#define LPF_ACCER44Hz   0x03
#define LPF_ACCER21Hz   0x04
#define LPF_ACCER10Hz   0x05
#define LPF_ACCER5Hz   0x06
#define SCALE2G		 	  0x00
#define SCALE4G			  0x08
#define SCALE8G			  0x10
#define SCALE16G	 	  0x18
//Macro of Register map of the MPU9250
#define SELF_TEST_X_GYRO  0x00
#define SELF_TEST_Y_GYRO  0x02
#define SELF_TEST_Z_GYRO  0x03
#define SELF_TEST_X_ACCEL 0x0D
#define SELF_TEST_Y_ACCEL 0x0E
#define SELF_TEST_Z_ACCEL 0x0F
#define XG_OFFSET_H       0x13
#define XG_OFFSET_L       0x14
#define YG_OFFSET_H       0x15
#define YG_OFFSET_L       0x16
#define ZG_OFFSET_H       0x17
#define ZG_OFFSET_L       0x18
#define SMPLRT_DIV        0x19
#define CONFIG            0x1A
#define GYRO_CONFIG       0x1B
#define ACCEL_CONFIG      0x1C
#define ACCEL_CONFIG2     0x1D
#define LP_ACCEL_ODR      0x1E
#define WOM_THR           0x1F
#define FIFO_EN           0x23
#define I2C_MST_CTRL      0x24
#define I2C_SLV0_ADDR     0x25
#define I2C_SLV0_REG      0x26
#define I2C_SLV0_CTRL     0x27
#define I2C_SLV1_ADDR     0x28
#define I2C_SLV1_REG      0x29
#define I2C_SLV1_CTRL     0x2A
#define I2C_SLV2_ADDR     0x2B
#define I2C_SLV2_REG      0x2C
#define I2C_SLV2_CTRL     0x2D
#define I2C_SLV3_ADDR     0x2E
#define I2C_SLV3_REG      0x2F
#define I2C_SLV3_CTRL     0x30
#define I2C_SLV4_ADDR     0x31
#define I2C_SLV4_REG      0x32
#define I2C_SLV4_DO       0x33
#define I2C_SLV4_CTRL     0x34
#define I2C_SLV4_DI       0x35
#define I2C_MST_STATUS    0x36
#define INT_PIN_CFG       0x37
#define INT_ENABLE        0x38
#define INT_STATUS        0x3A
#define ACCEL_XOUT_H      0x3B
#define ACCEL_XOUT_L      0x3C
#define ACCEL_YOUT_H      0x3D
#define ACCEL_YOUT_L      0x3E
#define ACCEL_ZOUT_H      0x3F
#define ACCEL_ZOUT_L      0x40
#define TEMP_OUT_H        0x41
#define TEMP_OUT_L        0x42
#define GYRO_XOUT_H       0x43
#define GYRO_XOUT_L       0x44
#define GYRO_YOUT_H       0x45
#define GYRO_YOUT_L       0x46
#define GYRO_ZOUT_H       0x47
#define GYRO_ZOUT_L       0x48
#define EXT_SENS_DATA_00  0x49
#define EXT_SENS_DATA_01  0x4A
#define EXT_SENS_DATA_02  0x4B
#define EXT_SENS_DATA_03  0x4C
#define EXT_SENS_DATA_04  0x4D
#define EXT_SENS_DATA_05  0x4E
#define EXT_SENS_DATA_06  0x4F
#define EXT_SENS_DATA_07  0x50
#define EXT_SENS_DATA_08  0x51
#define EXT_SENS_DATA_09  0x52
#define EXT_SENS_DATA_10  0x53
#define EXT_SENS_DATA_11  0x54
#define EXT_SENS_DATA_12  0x55
#define EXT_SENS_DATA_13  0x56
#define EXT_SENS_DATA_14  0x57
#define EXT_SENS_DATA_15  0x58
#define EXT_SENS_DATA_16  0x59
#define EXT_SENS_DATA_17  0x5A
#define EXT_SENS_DATA_18  0x5B
#define EXT_SENS_DATA_19  0x5C
#define EXT_SENS_DATA_20  0x5D
#define EXT_SENS_DATA_21  0x5E
#define EXT_SENS_DATA_22  0x5F
#define EXT_SENS_DATA_23  0x60
#define I2C_SLV0_DO       0x63
#define I2C_SLV1_DO       0x64
#define I2C_SLV2_DO       0x65
#define I2C_SLV3_DO       0x66
#define I2C_MST_DELAY_CTRL 0x67
#define SIGNAL_PATH_RESET 0x68
#define MOT_DETECT_CTRL   0x69
#define USER_CTRL         0x6A
#define PWR_MGMT_1        0x6B
#define PWR_MGMT_2        0x6C
#define FIFO_COUNTH       0x72
#define FIFO_COUNTL       0x73
#define FIFO_R_W          0x74
#define WHO_AM_I          0x75
#define XA_OFFSET_H       0x77
#define XA_OFFSET_L       0x78
#define YA_OFFSET_H       0x7A
#define YA_OFFSET_L       0x7B
#define ZA_OFFSET_H       0x7D
#define ZA_OFFSET_L       0x7E
//Macro of AK8962
#define AK8963_WIA		   0x00
#define AK8963_INFO 	   0x01
#define AK8963_ST1 		   0x02
#define AK8963_HXL		   0x03
#define AK8963_HXH		   0x04
#define AK8963_HYL		   0x05
#define AK8963_HYH		   0x06
#define AK8963_HZL 		   0x07
#define AK8963_HZH         0x08
#define AK8963_ST2 		   0x09
#define AK8963_CNTL1 	   0x0A
#define AK8963_CNTL2	   0x0B
#define AK8963_ASTC		   0x0C
#define AK8963_TS1		   0x0D
#define AK8963_TS2		   0x0E
#define AK8963_I2CDIS	   0x0F
#define AK8963_ASAX	       0x10
#define AK8963_ASAY	       0x11
#define AK8963_ASAZ		   0x12
#define AK8963_ADR 		   0x48
#define I2C_ENABLE		   0x80
#define READ_ENABLE		   0x80
//Macro of SPI
#define IMU9250_SPI_CS_PIN     GPIO_PIN_4
#define IMU9250_SPI_CS_PORT    GPIOA
//Declaration of function
void     IMU9250_WriteRegiter(uint8_t reg,uint8_t data,SPI_HandleTypeDef *hspi);
uint8_t  IMU9250_ReadRegiter(uint8_t reg,SPI_HandleTypeDef *hspi);
int16_t  IMU9250_ReadGyroRaw(char name,SPI_HandleTypeDef *hspi);
int16_t  IMU9250_ReadAccerRaw(char name,SPI_HandleTypeDef *hspi);
void     IMU9250_SetGyroOffset (int16_t OffsetX,int16_t OffsetY,int16_t OffsetZ,SPI_HandleTypeDef *hspi);
void     IMU9250_SetScaleGyro (uint8_t GyroValue ,SPI_HandleTypeDef *hspi);
void     IMU9250_SetScaleAccer (uint8_t AccerValue ,SPI_HandleTypeDef *hspi);
void     IMU9250_SetDLPFGyro (uint8_t GyroLPFValue ,SPI_HandleTypeDef *hspi);
void     IMU9250_SetDLPFAccer (uint8_t AccerLPFValue ,SPI_HandleTypeDef *hspi);
void     IMU9250_UpdateAngles(int16_t *offsetX, int16_t *offsetY, int16_t *offsetZ,float *angleX,float *angleY,float *angleZ ,float deltaTime,SPI_HandleTypeDef *hspi);
void     IMU9250_CalculateGyroOffset(int16_t *offsetX, int16_t *offsetY, int16_t *offsetZ, SPI_HandleTypeDef *hspi);
void     IMU9250_InitI2CMaster(SPI_HandleTypeDef *hspi);
void     AK8963_TurnOnFuseMode (SPI_HandleTypeDef *hspi);
void     AK8963_Powerdown (SPI_HandleTypeDef *hspi);
void     AK8963_ConsMeasure1 (SPI_HandleTypeDef *hspi);
void     AK8963_ConsMeasure2 (SPI_HandleTypeDef *hspi);
void     AK8963_Init (SPI_HandleTypeDef *hspi);
void     AK8963_ReadRegister (uint8_t reg,uint8_t numberOfByte,uint8_t* data,SPI_HandleTypeDef *hspi);
void     AK8963_Read_ASA (uint8_t* data ,SPI_HandleTypeDef *hspi);
int16_t  AK8963_Read_MagSensor (uint8_t name,uint8_t* Mag_data, SPI_HandleTypeDef *hspi);
#endif /*IMU_H_ */
