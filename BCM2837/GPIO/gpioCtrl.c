#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "gpioCtrl.h"

const int GPSEL_BASE = 0;
const int GPSET_BASE = 7;
const int GPCLR_BASE = 10;

struct MemMap gpio;

// TODO: implement munmap

void gpioInit()
{
	memoryMapping(&gpio, GPIO_BASE);
}

void setGpioPinToInput(unsigned int p_iPinNum)
{
	// point to GPFSELn for this pin (10 GPIO pins per GPFSEL register)
	volatile unsigned * pSel = (gpio.addr + GPSEL_BASE) + (p_iPinNum / 10);

	// compute the bit number in PGFSEL register (3 bits perpin)
	unsigned int iBitNum = (p_iPinNum % 10) * 3;

	// clear the 3 bits to set to input mode (000b)
	*pSel &= ~(7 << iBitNum);
}

void setGpioPinToOutput(unsigned int p_iPinNum)
{
	// point to GPFSELn for this pin (10 GPIO pins per GPFSEL register)
	volatile unsigned * pSel = (gpio.addr + GPSEL_BASE) + (p_iPinNum / 10);
	
	// compute the bit number in PGFSEL register (3 bits per pin)
	unsigned int iBitNum = (p_iPinNum % 10) * 3;

	// clear the 3 bits by setting them to input mode (000b)
	*pSel &= ~(7 << iBitNum);

	// set 3-bit field to 1 for output mode
	*pSel |= (1 << iBitNum);
}

// set pins to alternate functions
void setGpioPinToAlt(unsigned int p_iPinNum, unsigned int p_iAltNum)
{
	
	// point to GPFSELn register for this pin (10 GPIO pins per GPFSEL register)
	volatile unsigned * pSel = (gpio.addr + GPSEL_BASE) + (p_iPinNum / 10);

	// compute the bit number in PGFSEL register (3 bits per pin)
	unsigned int iBitNum = (p_iPinNum % 10) * 3;

	// clear the 3 bits by setting them to input mode (000b)
	*pSel &= ~(7 << iBitNum);
	
	// for ALT 0-3, set to 4-7; for ALT 4, set to 3; for ALT 5, set to 2
	unsigned int pinVal = p_iAltNum <=3 ? p_iAltNum + 4 : (p_iAltNum == 4 ? 3 : 2);

	unsigned int iSelVal = (pinVal << iBitNum);

	*pSel |= iSelVal;

}


// set pins operation mode
void setGpioPinOps(unsigned int p_iPinNum, int p_eOpMode, unsigned int p_iAltNum)
{
	switch (p_eOpMode)
	{
		case GPIO_INPUT:  setGpioPinToInput(p_iPinNum);
			 break;

		case GPIO_OUTPUT: setGpioPinToOutput(p_iPinNum);
			 break;

		case GPIO_ALT: setGpioPinToAlt(p_iPinNum,p_iAltNum);
			 break; 

		default:
			 break;

	};
}

void setGpioPinLevel(unsigned int p_iPinNum, int p_iLevel)
{

	if (p_iLevel == GPIO_HIGH)
	{
		volatile unsigned *pSet = (gpio.addr + GPSET_BASE) + p_iPinNum / 32;
		*pSet = 1 << (p_iPinNum % 32);
	}
	else
	{
		
		volatile unsigned * pClr = (gpio.addr + GPCLR_BASE) + p_iPinNum / 32;
		*pClr = 1 << (p_iPinNum % 32);
	}

}

void gpioUnMap()
{
	munmap(gpio.map, BLOCK_SIZE);
	close(gpio.fd);
}

