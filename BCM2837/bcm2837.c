#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "bcm2837.h"


void memoryMapping(struct MemMap *p_oMap, unsigned int p_oPhyAddr)
{

	// open /dev/mem device node; I/O file sync'd
	if ((p_oMap->fd = open("/dev/mem", O_RDWR|O_SYNC)) < 0)
    {
		char sErr[256];
		perror (sErr);

		printf("Failed to open /dev/mem %s\n", sErr);
		exit (-1);	
	}

	/* create a new mapping in the virtual address space */
	p_oMap->map = mmap ( NULL,		 	       // let kernel choose addr for mapping
					     BLOCK_SIZE,           // length of the mapping
					     PROT_WRITE|PROT_READ, // memory protection of mapping
					     MAP_SHARED,           // share mapping w other processes
					     p_oMap->fd,
					     p_oPhyAddr				// file mapping starting address
				  	   );

	// we don't need fd any more regardless of mmap result
	close(p_oMap->fd); 

	if (p_oMap->map == MAP_FAILED)
    {
		char sErr[256];
		perror (sErr);
		printf("Failed on mmap %s\n", sErr); 	
		exit (-1);
	}

	p_oMap->addr = (volatile unsigned *) p_oMap->map;
	


}

