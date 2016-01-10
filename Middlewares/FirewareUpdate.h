/*!
 * \file FirewareUpdate.h
 * \author no1wudi
 */

#ifndef __FIREWAREUPDATE_H
#define __FIREWAREUPDATE_H

#include "stm32f4xx_hal.h"

/*!
 * @defgroup fireware_update Fireware Update
 * @{
 */

/*!
 * \brief FirewareUpdate_Rst    重置Flash写指针到用户代码起始点
 */

extern void FirewareUpdate_Rst(void);

/*!
 * \brief FirewareUpdate_Erase  擦除用户代码区域
 */

extern void FirewareUpdate_Erase(void);

/*!
 * \brief FirewareUpdate_Write  将代码写入到用户Flash区
 * \param Buffer        等待被写入的数据块
 * \param BufferSize    等待被写入的数据大小，单位为byte
 */

extern void FirewareUpdate_Write(uint8_t * Buffer, uint32_t BufferSize);

/*!
 * \brief FirewareUpdate_JumpToApp  跳转执行用户程序
 */

extern void FirewareUpdate_JumpToApp(void);

/*!
 * @}
 */


#endif
