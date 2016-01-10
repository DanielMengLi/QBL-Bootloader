/*!
 * \file FirewareUpdate.h
 * \author no1wudi
 */

#include "FirewareUpdate.h"

/*!
 * @ingroup fireware_update
 * @{
 */


#define APP_START_ADDRESS   0x08008000  ///< 用户程序起始地址

static uint32_t UpdateAddressPtr = APP_START_ADDRESS;   ///< 指向正在更新的地址


void FirewareUpdate_Rst(void)
{
    UpdateAddressPtr = APP_START_ADDRESS;
}


void FirewareUpdate_Erase(void)
{
    uint32_t Err;
    FLASH_EraseInitTypeDef Erase;

    HAL_FLASH_Unlock();
    
    Erase.Banks = FLASH_BANK_1;
    Erase.NbSectors = 9;
    Erase.Sector = FLASH_SECTOR_2;
    Erase.TypeErase = FLASH_TYPEERASE_SECTORS;
    Erase.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    HAL_FLASHEx_Erase(&Erase, &Err);

    HAL_FLASH_Lock();
}

void FirewareUpdate_Write(uint8_t * Buffer, uint32_t BufferSize)
{
    HAL_FLASH_Unlock();

    for(uint32_t cnt = 0; cnt < BufferSize; cnt++)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, UpdateAddressPtr++, Buffer[cnt]);
    } 

    HAL_FLASH_Lock();
}



void FirewareUpdate_JumpToApp(void)
{
    uint32_t MSP;
    typedef  void (*pFunction)(void);
    void (*Jump)(void);
    MSP = *(uint32_t *)APP_START_ADDRESS;   //获取用户代码的堆栈指针
    __set_MSP(MSP);                         //设置用户代码的主堆栈指针
    SCB->VTOR = APP_START_ADDRESS;          //设置用户代码中断向量表的位置
    Jump = (pFunction)(APP_START_ADDRESS + 5);  //设置要跳转到用户程序的入口地址，地址最低位要为1，所以加上5，网上加上4的说法是错误的，
                                                //最低位为0表示试图切入ARM状态，会导致Hard Fault
    Jump();                                 //跳转
}

/*!
 * @}
 */
