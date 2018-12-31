#ifndef __GPIO_CTRL_H__
#define __GPIO_CTRL_H__

#define BCM2837B0_BASE 0x3F000000
#define GPIO_BASE      BCM2837B0_BASE + 0x00200000
const int BLOCK_SIZE = 4 * 1024;

const int GPSEL_BASE = 0;
const int GPSET_BASE = 7;
const int GPCLR_BASE = 10;

enum OpMode
{
	INPUT,
	OUTPUT,
};

enum Level
{
	LOW,
	HIGH
};


#endif


