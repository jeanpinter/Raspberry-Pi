This program reads and writes to AT24C256 EEPROM through I2C bus controlled by Broadcom Serial Controller (BSC) on BCM2837 SoC. It follows the following steps.

   1. Use mmap system call to map GPIO physical address to virtual address

   2. Set GPIO2 (SDA1) and GPIO3 (SCL1) to ALT0

   3. Use mmap system call to map BSC1 physical address to virtual address

   4. Write to the EEPROM at device address 0x50
      a. write 0x50 to BSC A register
      b. write length of data to BSC DLEN register. DLEN includes 2 bytes of EEPROM address to write data to. DLEN is 6 in this program)
      c. write EEPROM address (2 bytes) and data (0xAA 0xBB 0xCC 0xDD in this program) to BSC FIFO register 
      d. clear BSC S register
      e. start the write

   5. Read back from EEPROM
      a. write 0x50 to BSC A register
      b. write 2 bytes of EEPROM address to BSC FIFO
      c. clear BSC S register
      d. start the write
      e. set BSC DLEN register to number of bytes to read
	  f. clear BSC S register
      h. start the read
      g. get data from BSC FIFO register


To compile
	gcc -o i2c i2cCtrl.c ../GPIO/gpioCtrl.c ../bcm2837.c

TO run
    sudo su -
    ./i2c

Future improvement
    1. Write a general purpose program for i2c read/write
	
