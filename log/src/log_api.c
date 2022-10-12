/***************************************************************************************************
 * @file log_api.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 27/02/2022
 * @date Last modification 27/02/2022 by jnieto
 * @brief LOG functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup LOG_API
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "log/log_api.h"
#include <log/src/log_conductor.h>
#include <def_common.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t log_init()
{
    return log_conductor_init();
}

//--------------------------------------------------------------------------------------------------
ret_code_t log_new_msg(const char *name_task, log_level_debug_t level_debug, const char *info)
{
    ret_code_t ret = RET_INT_ERROR;

    if (!name_task || LOG_MAX_LEVEL < level_debug || !info)
    {
        return ret;
    }

    return log_conductor_new_msg(name_task, level_debug, info);
}

//--------------------------------------------------------------------------------------------------
char *itoa(int i, char b[])
{
    char const digit[] = "0123456789";
    char *p = b;

    if (0 > i)
    {
        *p++ = '-';
        i *= -1;
    }

    int shifter = i;

    do
    { // Move to where representation ends
        ++p;
        shifter = shifter / 10;
    } while (shifter);

    *p = '\0';

    // Move back, inserting digits as u go
    do
    {
        *--p = digit[i % 10];
        i = i / 10;
    } while (i);

    return b;
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
