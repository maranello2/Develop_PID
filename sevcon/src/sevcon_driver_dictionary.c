/***************************************************************************************************
 * @file sevcon_driver_dictionay.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 06/03/2022
 * @date Last modification 06/03/2022 by jnieto
 * @brief SEVCON functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup SEVCON_DRIVER_DICTIONARY
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "sevcon_driver_dictionary.h"

#include <hdwr/can_api.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/
static dictionary_canopen_t dictionary_canopen[] =
    {
        [VELOCITY] = {OD_READ, 0x606C, 0x00},
        [MOTOR_TEMPERATURE_1] = {OD_READ, 0x4600, 0x03},
        [ERROR_SEVCON] = {OD_READ, 0x5320, 0x00},
        [MAX_DICTIONARY] = {0xFF, 0xFFFF, 0xFFFF}

};

/* Private functions declaration -----------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
uint16_t sevcon_dictionary_found_id(uint16_t idx, uint16_t subidx)
{
    uint16_t ret = MAX_DICTIONARY;

    for (uint16_t i = 0; i <= MAX_DICTIONARY; i++)
    {
        if (dictionary_canopen[i].index == idx && dictionary_canopen[i].subindex == subidx)
        {
            ret = i;
            i = MAX_DICTIONARY;
        }
    }

    return ret;
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
