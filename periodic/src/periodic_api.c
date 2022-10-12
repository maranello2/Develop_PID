/***************************************************************************************************
 * @file periodic_api.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 05/02/2022
 * @date Last modification 05/02/2022 by jnieto
 * @brief periodic functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup PERIODIC_API
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "periodic/periodic_api.h"
#include "periodic/src/periodic_conductor.h"
#include <periodic/src/periodic_driver.h>

#include <stdlib.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t periodic_init(void)
{
    return periodic_conductor_init();
}

//--------------------------------------------------------------------------------------------------
periodic_id_t periodic_register(periodic_timers_t timers, periodic_cllbck cllbck, void *arg)
{

    if (PERIODIC_EVERY_1_SG < timers || !cllbck || !arg)
    {
        return NULL;
    }

    periodic_id_t periodic_id = periodic_driver_register(timers, cllbck, arg);
    return periodic_id;
}

//--------------------------------------------------------------------------------------------------
ret_code_t periodic_unregister(periodic_id_t periodic_id)
{
    if (!periodic_id)
    {
        return NULL;
    }

    return periodic_driver_unregister(periodic_id);
}

//--------------------------------------------------------------------------------------------------
ret_code_t periodic_start(periodic_id_t periodic_id)
{
    if (!periodic_id)
    {
        return NULL;
    }

    return periodic_driver_enable_function(periodic_id, 1);
}

//--------------------------------------------------------------------------------------------------
ret_code_t periodic_stop(periodic_id_t periodic_id)
{
    if (!periodic_id)
    {
        return NULL;
    }

    return periodic_driver_enable_function(periodic_id, 0);
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
