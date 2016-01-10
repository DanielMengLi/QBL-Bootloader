#ifndef __FIREWAREUPDATE_H
#define __FIREWAREUPDATE_H

#include "stm32f4xx_hal.h"

extern void FirewareUpdate_Rst(void);
extern void FirewareUpdate_Erase(void);
extern void FirewareUpdate_Write(uint8_t * Buffer, uint32_t BufferSize);
extern void FirewareUpdate_JumpToApp(void);

#endif
