/*
****************************************************************************************************
* (c) copyright by
*     Embedded Office GmbH & Co. KG       Tel : (07522) 97 00 08-0
*     Friedrich-Ebert-Str. 20/1           Fax : (07522) 97 00 08-99
*     D-88239 Wangen                      Mail: info@embedded-office.de
*                                         Web : http://www.embedded-office.de
*
* All rights reserved. Confidential and Proprietary. Protected by international copyright laws.
* Knowledge of the source code may not be used to write a similar product.
* This file may only be used in accordance with a license and should not be
* redistributed in any way.
****************************************************************************************************
*/

#include <trcDefines.h>

static inline uint32_t __get_PRIMASK(void)
{
    uint32_t primask;
    __asm volatile ("MRS %0, PRIMASK" : "=r"(primask) :: "memory");
    return primask;
}

static inline void __set_PRIMASK(uint32_t primask)
{
    __asm volatile ("MSR PRIMASK, %0" :: "r"(primask) : "memory");
}