#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "i2cCtrl.h"

struct MemMap bsc;

void bscInit()
{
	// create memory map for gpio control
	gpioInit();

	// set GPIO pin 2 to ALT0 (SDA1) 
	setGpioPinToAlt(2, 0);

	// set GPIO pin 3 to ALT0 (SCL1)
	setGpioPinToAlt(3, 0);

	// create memory map for bsc1 control
	// SDA0 and SCL0 use BSC0. SDA1 and SCL1 use BSC1
	memoryMapping(&bsc,BSC1_BASE); 
}

void wait_i2c_done()
{

	unsigned int status = *(bsc.addr + BSC_S_OFF);
    
	int timeout = 50;
	while ( !(status & BSC_S_DONE) && --timeout)
	{
		usleep(5000);
		status = *(bsc.addr + BSC_S_OFF);
	}

	if (timeout == 0)
	{
		printf("Timeout\n");
	}
}

void i2c_write_byte()
{
	// EEPROM device address 0x50 (use i2cdetect command to find out)
	unsigned int iDevAddr = 0x50;

	// write device address to bit 0 - 6 in A register 
	*(bsc.addr + BSC_A_OFF) = iDevAddr;

	// write [0xAA 0xBB 0xCC 0x DD] to EEPROM at address 0x0000
	*(bsc.addr + BSC_DLEN_OFF) = 6;
	*(bsc.addr + BSC_FIFO_OFF) = 0x00;
	*(bsc.addr + BSC_FIFO_OFF) = 0x00;
	*(bsc.addr + BSC_FIFO_OFF) = 0xAA;
	*(bsc.addr + BSC_FIFO_OFF) = 0xBB;
	*(bsc.addr + BSC_FIFO_OFF) = 0xCC;
	*(bsc.addr + BSC_FIFO_OFF) = 0xDD;

    *(bsc.addr + BSC_S_OFF) = CLEAR_STATUS;
    *(bsc.addr + BSC_C_OFF) = START_WRITE;

	wait_i2c_done();

}

void i2c_read_byte()
{
	unsigned data;
	unsigned int status;
	unsigned len;

	// EEPROM device address 0x50 (use i2cdetect command to find out)
	unsigned int iDevAddr = 0x50;

	*(bsc.addr + BSC_A_OFF) = iDevAddr;
	
	// specify the EEPROM location to read from by writing the location first
	*(bsc.addr + BSC_DLEN_OFF) = 2;
	*(bsc.addr + BSC_FIFO_OFF) = 0x00;
	*(bsc.addr + BSC_FIFO_OFF) = 0x00;

    *(bsc.addr + BSC_S_OFF) = CLEAR_STATUS;
    *(bsc.addr + BSC_C_OFF) = START_WRITE;

	wait_i2c_done();

	// read 4 bytes back
	*(bsc.addr + BSC_DLEN_OFF) = 4;
    *(bsc.addr + BSC_S_OFF) = CLEAR_STATUS;
    *(bsc.addr + BSC_C_OFF) = START_READ;

	wait_i2c_done();

	data = *(bsc.addr + BSC_FIFO_OFF);
	printf("data = %x\n", data);

	data = *(bsc.addr + BSC_FIFO_OFF);
	printf("data = %x\n", data);

	data = *(bsc.addr + BSC_FIFO_OFF);
	printf("data = %x\n", data);

	data = *(bsc.addr + BSC_FIFO_OFF);
	printf("data = %x\n", data);

}


int main()
{

	bscInit();

	i2c_write_byte();
	i2c_read_byte();

	gpioUnMap();
	munmap(bsc.map, BLOCK_SIZE);
    close(bsc.fd);
    
}


