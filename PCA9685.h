#ifndef LIB_PCA9685_LIBRARY_H
#define LIB_PCA9685_LIBRARY_H

#include <stdint.h>
#include <stdbool.h>
#include "LL_i2c.h"

enum PCA9685_OutputMode_t
{
	PCA9685_OutputMode_OpenDrain,
	PCA9685_OutputMode_TotemPole
};

struct PCA9685_t
{
	//PUBLIC INSTANCE MEMBERS
	uint8_t I2CAddress;
	//points to a function to handle the I2C writes
	I2CMaster_WriteMethod_t i2cWriteDataMethod;
};

int PCA9685_Init(struct PCA9685_t* instance, uint8_t address, uint16_t pwmfrequency, enum PCA9685_OutputMode_t outputMode, bool invertOutputs);
void PCA9685_WritePWM(struct PCA9685_t* instance, uint8_t channel,uint16_t pwm);

#endif //LIB_PCA9685_LIBRARY_H
