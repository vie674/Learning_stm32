/*
 * imu.c
 *
 *  Created on: Nov 22, 2024
 *      Author: hung
 */
#include "imu.h"

void IMU9250_WriteRegiter(uint8_t reg,uint8_t data,SPI_HandleTypeDef *hspi)
{
	uint8_t temp = reg&(~0x80);
	HAL_GPIO_WritePin(IMU9250_SPI_CS_PORT, IMU9250_SPI_CS_PIN, 0);
	HAL_SPI_Transmit(hspi, &temp, 1, 200);
	HAL_SPI_Transmit(hspi,&data,1,200);
	HAL_GPIO_WritePin(IMU9250_SPI_CS_PORT, IMU9250_SPI_CS_PIN, 1);
}
uint8_t IMU9250_ReadRegiter(uint8_t reg,SPI_HandleTypeDef *hspi)
{
	uint8_t temp = reg|0x80;
	uint8_t data=0;
	HAL_GPIO_WritePin(IMU9250_SPI_CS_PORT, IMU9250_SPI_CS_PIN, 0);
	HAL_SPI_Transmit(hspi, &temp, 1, 200);
	HAL_SPI_Receive(hspi, &data, 1, 200);
	HAL_GPIO_WritePin(IMU9250_SPI_CS_PORT, IMU9250_SPI_CS_PIN, 1);
	return data;
}
int16_t IMU9250_ReadGyroRaw(char name,SPI_HandleTypeDef *hspi)
{
	int16_t data=0;
	uint8_t dataL=0,dataH=0;
	if (name =='X')
	{
		dataH=IMU9250_ReadRegiter(GYRO_XOUT_H, hspi);
		dataL=IMU9250_ReadRegiter(GYRO_XOUT_L, hspi);
		data= (int16_t)(dataH<<8)|dataL;
	}
	else if(name=='Y')
	{
		dataH=IMU9250_ReadRegiter(GYRO_YOUT_H, hspi);
		dataL=IMU9250_ReadRegiter(GYRO_YOUT_L, hspi);
		data= (int16_t)(dataH<<8)|dataL;
	}
	else if (name =='Z')
	{
		dataH=IMU9250_ReadRegiter(GYRO_ZOUT_H, hspi);
		dataL=IMU9250_ReadRegiter(GYRO_ZOUT_L, hspi);
		data= (int16_t)(dataH<<8)|dataL;
	}
	else
	{
		return IM_NOT_OK ;
	}
	return data;
}
int16_t IMU9250_ReadAccerRaw(char name,SPI_HandleTypeDef *hspi)
{
	int16_t data=0;
	uint8_t dataL=0,dataH=0;
	if (name =='X')
	{
		dataH=IMU9250_ReadRegiter(ACCEL_XOUT_H, hspi);
		dataL=IMU9250_ReadRegiter(ACCEL_XOUT_L, hspi);
		data= (int16_t)(dataH<<8)|dataL;
	}
	else if(name=='Y')
	{
		dataH=IMU9250_ReadRegiter(ACCEL_YOUT_H, hspi);
		dataL=IMU9250_ReadRegiter(ACCEL_YOUT_L, hspi);
		data= (int16_t)(dataH<<8)|dataL;
	}
	else if (name =='Z')
	{
		dataH=IMU9250_ReadRegiter(ACCEL_ZOUT_H, hspi);
		dataL=IMU9250_ReadRegiter(ACCEL_ZOUT_L, hspi);
		data= (int16_t)(dataH<<8)|dataL;
	}
	else
	{
		return IM_NOT_OK;
	}
	return data;
}
void IMU9250_SetGyroOffset (int16_t OffsetX,int16_t OffsetY,int16_t OffsetZ,SPI_HandleTypeDef *hspi)
{
	uint8_t OffsetXL,OffsetXH,OffsetYL,OffsetYH,OffsetZL,OffsetZH;

	OffsetXL = OffsetX&(0xFF);
	OffsetXH = (OffsetX>>8)&0xFF;

	OffsetYL = OffsetY&(0xFF);
	OffsetYH = (OffsetY>>8)&0xFF;

	OffsetZL = OffsetZ&(0xFF);
	OffsetZH = (OffsetZ>>8)&0xFF;

	IMU9250_WriteRegiter(XG_OFFSET_H, OffsetXH, hspi);
	IMU9250_WriteRegiter(XG_OFFSET_L, OffsetXL, hspi);
	IMU9250_WriteRegiter(YG_OFFSET_H, OffsetYH, hspi);
	IMU9250_WriteRegiter(YG_OFFSET_L, OffsetYL, hspi);
	IMU9250_WriteRegiter(ZG_OFFSET_H, OffsetZH, hspi);
	IMU9250_WriteRegiter(ZG_OFFSET_L, OffsetZL, hspi);
}
void IMU9250_SetAccerOffset (int16_t OffsetX,int16_t OffsetY,int16_t OffsetZ,SPI_HandleTypeDef *hspi)
{
	uint8_t OffsetXL,OffsetXH,OffsetYL,OffsetYH,OffsetZL,OffsetZH;

	OffsetXL = OffsetX&(0xFF);
	OffsetXH = (OffsetX>>8)&0xFF;

	OffsetYL = OffsetY&(0xFF);
	OffsetYH = (OffsetY>>8)&0xFF;

	OffsetZL = OffsetZ&(0xFF);
	OffsetZH = (OffsetZ>>8)&0xFF;

	IMU9250_WriteRegiter(XA_OFFSET_H, OffsetXH, hspi);
	IMU9250_WriteRegiter(XA_OFFSET_L, OffsetXL, hspi);
	IMU9250_WriteRegiter(YA_OFFSET_H, OffsetYH, hspi);
	IMU9250_WriteRegiter(YA_OFFSET_L, OffsetYL, hspi);
	IMU9250_WriteRegiter(ZA_OFFSET_H, OffsetZH, hspi);
	IMU9250_WriteRegiter(ZA_OFFSET_L, OffsetZL, hspi);
}
void IMU9250_SetScaleGyro (uint8_t GyroValue ,SPI_HandleTypeDef *hspi)
{
	IMU9250_WriteRegiter(GYRO_CONFIG, GyroValue, hspi);
}
void IMU9250_SetScaleAccer (uint8_t AccerValue ,SPI_HandleTypeDef *hspi)
{
	IMU9250_WriteRegiter(ACCEL_CONFIG,AccerValue, hspi);
}
void IMU9250_SetDLPFGyro (uint8_t GyroLPFValue ,SPI_HandleTypeDef *hspi)
{
	IMU9250_WriteRegiter(CONFIG, GyroLPFValue, hspi);
}
void IMU9250_SetDLPFAccer (uint8_t AccerLPFValue ,SPI_HandleTypeDef *hspi)
{
	IMU9250_WriteRegiter(ACCEL_CONFIG2,AccerLPFValue,hspi);
}
void IMU9250_CalculateGyroOffset(int16_t *offsetX, int16_t *offsetY, int16_t *offsetZ, SPI_HandleTypeDef *hspi)
{
    int64_t sumX = 0, sumY = 0, sumZ = 0;
    int16_t rawX, rawY, rawZ;
    int samples = 100;

    for (int i = 0; i < samples; i++) {
        rawX = IMU9250_ReadGyroRaw('X', hspi);
        rawY = IMU9250_ReadGyroRaw('Y', hspi);
        rawZ = IMU9250_ReadGyroRaw('Z', hspi);

        sumX += rawX;
        sumY += rawY;
        sumZ += rawZ;

        HAL_Delay(10);
    }

    *offsetX = sumX / samples;
    *offsetY = sumY / samples;
    *offsetZ = sumZ / samples;
}
void IMU9250_CalculateAccerOffset(int16_t *offsetX, int16_t *offsetY, int16_t *offsetZ, SPI_HandleTypeDef *hspi)
{
    int64_t sumX = 0, sumY = 0, sumZ = 0;
    int16_t rawX, rawY, rawZ;
    int samples = 100;

    for (int i = 0; i < samples; i++) {
        rawX = IMU9250_ReadAccerRaw('X', hspi);
        rawY = IMU9250_ReadAcceraw('Y', hspi);
        rawZ = IMU9250_ReadAccerRaw('Z', hspi);

        sumX += rawX;
        sumY += rawY;
        sumZ += rawZ;

        HAL_Delay(10);
    }

    *offsetX = sumX / samples;
    *offsetY = sumY / samples;
    *offsetZ = sumZ / samples;
}

void IMU9250_UpdateAngles(int16_t *offsetX, int16_t *offsetY, int16_t *offsetZ,float *angleX,float *angleY,float *angleZ ,float deltaTime,SPI_HandleTypeDef *hspi)
{
    int16_t rawX, rawY, rawZ;
    float angularVelocityX, angularVelocityY, angularVelocityZ;

    rawX = IMU9250_ReadGyroRaw('X', hspi);
    rawY = IMU9250_ReadGyroRaw('Y', hspi);
    rawZ = IMU9250_ReadGyroRaw('Z', hspi);

    angularVelocityX = (rawX - *offsetX) / 130.0f;
    angularVelocityY = (rawY - *offsetY) / 130.0f;
    angularVelocityZ = (rawZ - *offsetZ) / 130.0f;

    *angleX += angularVelocityX * deltaTime;
    *angleY += angularVelocityY * deltaTime;
    *angleZ += angularVelocityZ * deltaTime;
}
void AK8963_WriteRegister (uint8_t reg,uint8_t data,SPI_HandleTypeDef *hspi)
{
	//Write I2C address of AK8963 to I2C_SLV_ADD
	IMU9250_WriteRegiter(I2C_SLV0_ADDR, AK8963_ADR, hspi);

	//Put the register address where begin to write
	IMU9250_WriteRegiter(I2C_SLV0_REG, reg, hspi);

	//Put the data to write to AK8963 module
	IMU9250_WriteRegiter(I2C_SLV0_DO, data, hspi);

	//Enable reading data from A8963 and store in the first e EXT_SENS_DATA register
	//Choose number of byte to read
	IMU9250_WriteRegiter(I2C_SLV0_CTRL, I2C_ENABLE|0, hspi);
}

void AK8963_ReadRegister (uint8_t reg,uint8_t numberOfByte,uint8_t* data,SPI_HandleTypeDef *hspi)
{
	uint8_t i;
	//Write I2C address of AK8963 to I2C_SLV_ADD
	IMU9250_WriteRegiter(I2C_SLV0_ADDR, AK8963_ADR|0x80, hspi);

	//Put the register address where begin to write
	IMU9250_WriteRegiter(I2C_SLV0_REG, reg, hspi);

	//Enable reading data from A8963 and store in the first e EXT_SENS_DATA register
	//Choose number of byte to read
	IMU9250_WriteRegiter(I2C_SLV0_CTRL, I2C_ENABLE|numberOfByte, hspi);

	HAL_Delay(100);
	//Read Data
	for (i=0;i<numberOfByte;i++)
	{
	data[i] = IMU9250_ReadRegiter(EXT_SENS_DATA_00+i, hspi);
	}
}

void IMU9250_InitI2CMaster(SPI_HandleTypeDef *hspi)
{
	//Turn on I2C Master
	IMU9250_WriteRegiter(USER_CTRL, 0x30, hspi);

	//Choose clock for I2C in I2C control
	IMU9250_WriteRegiter(I2C_MST_CTRL, 0x0D, hspi);
}
void AK8963_TurnOnFuseMode (SPI_HandleTypeDef *hspi)
{
	AK8963_WriteRegister( AK8963_CNTL1, 0x0F,hspi);
}
void AK8963_Powerdown (SPI_HandleTypeDef *hspi)
{
	AK8963_WriteRegister( AK8963_CNTL1, 0x00,hspi);
}
void AK8963_ConsMeasure1 (SPI_HandleTypeDef *hspi)
{
	AK8963_WriteRegister(AK8963_CNTL1, 0x02,hspi);
}
void AK8963_ConsMeasure2 (SPI_HandleTypeDef *hspi)
{
	AK8963_WriteRegister(AK8963_CNTL1, 0x06,hspi);
}
void AK8963_Init (SPI_HandleTypeDef *hspi)
{
	AK8963_Powerdown(hspi);
	HAL_Delay(100);
}
void AK8963_Read_ASA (uint8_t* data ,SPI_HandleTypeDef *hspi)
{
	AK8963_TurnOnFuseMode(hspi);
	HAL_Delay(100);
	AK8963_ReadRegister(AK8963_ASAX, 3,data, hspi);
}
int16_t AK8963_Read_MagSensor (uint8_t name,uint8_t* Mag_data, SPI_HandleTypeDef *hspi)
{
	int16_t data16=0;
	uint8_t dataL=0,dataH=0;
	AK8963_ConsMeasure1(hspi);
	AK8963_ReadRegister(AK8963_HXH,6,Mag_data,hspi);
	if (name =='X')
	{
		dataL=Mag_data[0];
		dataH=Mag_data[1];
		data16= (int16_t)(dataH<<8)|dataL;
	}
	else if(name=='Y')
	{
		dataL=Mag_data[2];
		dataH=Mag_data[3];
		data16= (int16_t)(dataH<<8)|dataL;
	}
	else if (name =='Z')
	{
		dataL=Mag_data[4];
		dataH=Mag_data[5];
		data16= (int16_t)(dataH<<8)|dataL;
	}
	else
	{
		return IM_NOT_OK;
	}
	return data16;
}
