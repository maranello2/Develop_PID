/***************************************************************************************************
 * @file heartbeat_api.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 11/11/2021
 * @date Last modification 17/11/2021 by jnieto
 * @brief HeartBeat
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup HEARTBEAT_API
    @{

*/

/* Includes --------------------------------------------------------------------------------------*/
#include <heartbeat/heartbeat_api.h>
#include "cmsis_os2.h"
#include <stdlib.h>
#include <stdio.h>
#include <periodic/periodic_api.h>

#include "hdwr/adc_api.h"
#include "log/log_api.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/
/** data of heartbeat */
typedef struct heartbeat_s
{
    gpio_out_t gpio; /**< Fixed the GPIO of LED */
} heartbeat_t;

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Run periodic of heartbeat thread
 *
 * @param argument \ref heartbeat_t
 */
void heartbeat_periodic(void *arg);

volatile uint16_t i_adc = 0x00;
/* Private functions -----------------------------------------------------------------------------*/
void heartbeat_periodic(void *arg)
{
    heartbeat_t *heartbeat = (heartbeat_t *)arg;

    gpio_toggle(heartbeat->gpio);
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t heartbeat_init(heartbeat_cfg_t *cfg)
{
    ret_code_t ret = RET_INT_ERROR;
    periodic_id_t periodic_id = NULL;

    if (!cfg)
        return ret;

    heartbeat_t *heartbeat = (heartbeat_t *)calloc(1, sizeof(heartbeat_t));

    if (heartbeat)
    {
        heartbeat->gpio = cfg->gpio;

        periodic_id = periodic_register((periodic_timers_t)cfg->delay_ms,
                                        heartbeat_periodic,
                                        heartbeat);
    }

    if (periodic_id)
    {
        ret = periodic_start(periodic_id);
    }

    if (RET_SUCCESS == ret)
    {
        char msg[] = "CREATED";
        return (log_new_msg(cfg->name, LOG_DEBUG, msg));
    }

    return ret;
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
