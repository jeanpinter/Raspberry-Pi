#ifndef __I2C_CTRL_H__
#define __I2C_CTRL_H__

#include "../bcm2837.h"
#include "../GPIO/gpioCtrl.h"

#define BSC_C_OFF     0x00     // Control register offset
#define BSC_S_OFF     0x01     // Status register offset
#define BSC_DLEN_OFF  0x02     // Data Len register offset
#define BSC_A_OFF     0x03     // Address register offset
#define BSC_FIFO_OFF  0x04     // FIFO register offset
#define BSC_DIV_OFF   0x05
#define BSC_DEL_OFF   0x06
#define BSC_T_OFF     0x07     // TOUT register offset

#define BSC_C_I2CEN    1 << 15 // I2C enable - bit 15
#define BSC_C_INTR     1 << 10 // interrupt for read - bit 10
#define BSC_C_INTT     1 << 9  // interrupt for write - bit 9
#define BSC_C_INTD     1 << 8  // interrupt for done - bit 8
#define BSC_C_ST       1 << 7  // transfer start - bit 7
#define BSC_C_CLEAR    1 << 4  // clear status register
#define BSC_C_READ     1       // read access

#define BSC_S_CLKT     1 << 9
#define BSC_S_ERR      1 << 8
#define BSC_S_DONE     1 << 1

#define START_READ     BSC_C_I2CEN | BSC_C_ST | BSC_C_CLEAR | BSC_C_READ
#define START_WRITE    BSC_C_I2CEN | BSC_C_ST

#define CLEAR_STATUS   BSC_S_CLKT | BSC_S_ERR | BSC_S_DONE


#endif


