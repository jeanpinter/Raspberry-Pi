#ifndef _BCM_H
#define _BCM_H


#define BCM2837B0_BASE   0x3F000000
#define GPIO_BASE        BCM2837B0_BASE + 0x00200000
#define BSC0_BASE        BCM2837B0_BASE + 0x00205000
#define BSC1_BASE        BCM2837B0_BASE + 0x00804000 
#define BLOCK_SIZE       4*1024

struct MemMap
{
    // declare volatile to turn off optimization
	volatile unsigned *addr;
    void *map;
    int fd;
};

void memoryMapping(struct MemMap *p_oMap, unsigned int p_oPhyAddr);

#endif
