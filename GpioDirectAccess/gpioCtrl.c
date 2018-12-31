#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "gpioCtrl.h"

// declare volatile to turn off optimization for gpio variable
volatile unsigned * gpio;

void init()
{
    int mem_fd;
    void *gpio_map;

    // open /dev/mem device node; I/O file sync'd
    if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC)) < 0)
    {
        char sErr[256];
        perror (sErr);

	printf("Failed to open /dev/mem %s\n", sErr);
	exit (-1);	
    }

    /* create a new mapping in the virtual address space of this process */
    gpio_map = mmap ( NULL,		    // kernel choose addr for mapping
                      BLOCK_SIZE,           // length of the mapping
		      PROT_WRITE|PROT_READ, // memory protection of mapping
		      MAP_SHARED,           // share mapping w other processes
		      mem_fd,
		      GPIO_BASE    	    // file mapping starting address
		    );

    // we don't need fd any more regardless of mmap result
    close(mem_fd); 

    if (gpio_map == MAP_FAILED)
    {
	char sErr[256];
	perror (sErr);
	printf("Failed on mmap %s\n", sErr); 	
	exit (-1);
    }

    gpio = (volatile unsigned *) gpio_map;
	
}

void setPinToInput(unsigned int p_iPinNum)
{
    // point to GPFSELn for this pin (10 GPIO pins per GPFSEL register)
    volatile unsigned * pSel = (gpio + GPSEL_BASE) + (p_iPinNum / 10);

    // compute the bit number in PGFSEL register (3 bits per pin)
    unsigned int iBitNum = (p_iPinNum % 10) * 3;

    // clear the 3 bits to set to input mode (000b)
    *pSel &= ~(7 << iBitNum);
}

void setPinToOutput(unsigned int p_iPinNum)
{
    // point to GPFSELn for this pin (10 GPIO pins per GPFSEL register)
    volatile unsigned * pSel = (gpio + GPSEL_BASE) + (p_iPinNum / 10);

    // compute the bit number in PGFSEL register (3 bits per pin)
    unsigned int iBitNum = (p_iPinNum % 10) * 3;

    // clear the 3 bits then set to output mode
    *pSel &= ~(7 << iBitNum);
    *pSel |= (1 << iBitNum);
}


// set pins operation mode
void setPinOps(unsigned int p_iPinNum, int p_eOpMode)
{
    switch (p_eOpMode)
    {
	case INPUT:  setPinToInput(p_iPinNum);
		 break;

	case OUTPUT: setPinToOutput(p_iPinNum);
		 break;

	default:
		 break;

    };
}

void setPinLevel(unsigned int p_iPinNum, int p_iLevel)
{

    if (p_iLevel == HIGH)
    {
	// to set GPIO pin to high, point to GPSET register and set bit to 1
        volatile unsigned *pSet = (gpio + GPSET_BASE) + p_iPinNum / 32;
        *pSet = 1 << (p_iPinNum % 32);
    }
    else
    {
	// to set GPIO pin to low, point to GPCLR register and set bit to 1
	volatile unsigned * pClr = (gpio + GPCLR_BASE) + p_iPinNum / 32;
	*pClr = 1 << (p_iPinNum % 32);
    }

}

int main()
{
    // test program which toggles GPIO pin 17 and 19 causing LEDs to blink
    init();
    setPinOps(19, OUTPUT);
    setPinOps(17, OUTPUT);

    // TODO: catch kill signal to exit the while-loop
    while (1)
    {
	setPinLevel(17, HIGH);
	setPinLevel(19, LOW);
	sleep(2);
	setPinLevel(17, LOW);
	setPinLevel(19, HIGH);
	sleep(2);
    }

}


