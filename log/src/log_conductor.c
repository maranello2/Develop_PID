/***************************************************************************************************
 * @file LOG_conductor.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 27/02/2022
 * @date Last modification 31/03/2022 by jnieto
 * @brief LOG functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup LOG_CONDUCTOR
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "log_conductor.h"
#include "log_driver.h"
#include "cmsis_os2.h"
#include <def_common.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** Definitions for defaultTask */
osThreadAttr_t log_task_attributes =
    {
        .priority = (osPriority_t)osPriorityLow,
        .name = "LOG",
        .stack_size = 1024,
};

/** ID for thread */
osThreadId_t thread_id;

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Run thread
 *
 * @param argument \ref NULL
 */
void log_task(void *argument);

/* Private functions -----------------------------------------------------------------------------*/
void log_task(void *argument)
{
    while (1)
    {
        osThreadFlagsWait(0x00, osFlagsWaitAny, osWaitForever);
    }
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t log_conductor_init(void)
{
    thread_id = osThreadNew(log_task, NULL, &log_task_attributes);

    char msg[] = "CREATED";

    if (thread_id)
    {
        return log_conductor_new_msg(log_task_attributes.name, LOG_DEBUG, msg);
    }

    return RET_INT_ERROR;
}

//--------------------------------------------------------------------------------------------------
ret_code_t log_conductor_new_msg(const char *name_task, log_level_debug_t level_debug, const char *info)
{

    ret_code_t ret = log_driver_create_new_message(name_task, level_debug, info);

    if (RET_SUCCESS == ret && thread_id)
    {
        osThreadResume(thread_id);
    }

    return ret;
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
