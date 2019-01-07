#ifndef __GPIO_CTRL_H__
#define __GPIO_CTRL_H__

#include "../bcm2837.h"

enum OpMode
{
	GPIO_INPUT,
	GPIO_OUTPUT,
    GPIO_ALT,
};

enum Level
{
	GPIO_LOW,
	GPIO_HIGH
};

struct gpioMemMap
{
	volatile unsigned *addr;


};

void gpioInit();
void setGpioPinOps(unsigned int p_iPinNum, int p_eOpMode, unsigned int p_iAltNum);
void setGpioPinLevel(unsigned int p_iPinNum, int p_iLevel);
void setGpioPinToAlt(unsigned int p_iPinNum, unsigned int p_iAltNum);
void gpioUnMap();

#endif


