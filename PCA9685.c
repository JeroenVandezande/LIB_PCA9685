#include "PCA9685.h"

#include <stdio.h>
#include <math.h>

#define BASE_ADDRESS 0b10000000
#define CHIPCLK 25000000

struct __attribute__((__packed__)) pca9685datareg {
	uint8_t registeraddress;
	uint16_t start;
	uint16_t stop;
};

struct __attribute__((__packed__)) pca9685setupreg {
	uint8_t registeraddress;
	uint8_t registerdata;
};

int PCA9685_Init(struct PCA9685_t* instance, uint8_t address, uint16_t pwmfrequency, enum PCA9685_OutputMode_t outputMode, bool invertOutputs)
{
	instance->I2CAddress = BASE_ADDRESS | (address << 1); //shift one bit to the left for R/W bit
    struct pca9685setupreg rd;
    rd.registeraddress = 0xFE; //prescaler
    rd.registerdata = round(CHIPCLK / (4096 * pwmfrequency));
	instance->i2cWriteDataMethod(instance->I2CAddress, &rd, 2);
	rd.registeraddress = 0x01; //MODE2
	rd.registerdata = invertOutputs ? 1 << 4 : 0; //set output invert bit
	rd.registerdata |= (outputMode == PCA9685_OutputMode_TotemPole) ? 1 << 2 : 0; //set output drive bit
	instance->i2cWriteDataMethod(instance->I2CAddress, &rd, 2);
	return 0;
}

void PCA9685_WritePWM(struct PCA9685_t* instance, uint8_t channel,uint16_t pwm)
{
	struct pca9685datareg outdata;
	uint16_t start = channel * 256;
	uint16_t stop = start + pwm;
	if (stop > 4095)
	{
		start = start - (stop - 4096);
		stop = 4095;
	}
	outdata.start = start;
	outdata.stop = stop;
	if (pwm == 0)
	{
		outdata.start = 0;
		outdata.stop = 0b0001000000000000;
	}
	if (pwm > 4094)
	{
		outdata.start = 0b0001000000000000;
		outdata.stop = 0;
	}
	outdata.registeraddress = 6 + (4 * channel);
	instance->i2cWriteDataMethod(instance->I2CAddress, &outdata, 5);
}