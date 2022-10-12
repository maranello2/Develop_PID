/***************************************************************************************************
 * @file periodic_conductor.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 05/02/2022
 * @date Last modification 05/02/2022 by jnieto
 * @brief periodic functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup PERIODIC_CONDUCTOR
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "periodic_conductor.h"
#include "periodic_driver.h"

#include "cmsis_os2.h"
#include <stdlib.h>
#include <def_common.h>
#include <stdio.h>
#include "log/log_api.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** Definitions for defaultTask */
osThreadAttr_t periodic_task_attributes =
    {
        .priority = (osPriority_t)osPriorityNormal,
        .name = "PERIODIC",
        .stack_size = 512,
};

/* Private values --------------------------------------------------------------------------------*/
uint32_t tick = 0x00;

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Run thread
 *
 * @param argument \ref NULL
 */
void periodic_task(void *argument);

/* Private functions -----------------------------------------------------------------------------*/
void periodic_task(void *argument)
{
    while (1)
    {
        osThreadFlagsWait(0x00, osFlagsWaitAny, 100);

        tick += 100;

        // Task every 100 ms
        periodic_driver_every_100ms();

        // Task every 200 ms
        if (!(tick % 200))
        {
            periodic_driver_every_200ms();
        }

        // Task every 500 ms
        if (!(tick % 500))
        {
            periodic_driver_every_500ms();
        }

        // Task every 1000 ms
        if (!(tick % 1000))
        {
            periodic_driver_every_1000ms();
        }
    }
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t periodic_conductor_init(void)
{
    if (osThreadNew(periodic_task, NULL, &periodic_task_attributes))
    {

        char msg[] = "CREATED";

        return (log_new_msg(periodic_task_attributes.name, LOG_DEBUG, msg));
    }

    return RET_INT_ERROR;
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
