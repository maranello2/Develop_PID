/***************************************************************************************************
 * @file periodic_driver.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 05/02/2022
 * @date Last modification 05/02/2022 by jnieto
 * @brief periodic functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup PERIODIC_DRIVER
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "periodic_driver.h"

#include "periodic/periodic_config.h"
#include "periodic/periodic_api.h"
#include <stdio.h>
#include <string.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/
/** Struct detect function callback with periodic_id_t */
typedef union
{
    uint32_t all;
    struct
    {
        uint32_t timers : 16; /** Select Timers ref periodic_timers_t*/
        uint32_t id : 16;     /** Selectr position array of periodic_cllbck_register_t */
    } frame;
} periodic_id_frame_t;

/** Sturcture of dates periodic registered */
typedef struct periodic_cllbck_register_s
{
    periodic_cllbck cllbck; /** Pointer cllbck resgister */
    void *arg;              /** Pointer data send to cllbck register */
    uint8_t enable;         /** Start/Stop callback */
} periodic_cllbck_register_t;

periodic_cllbck_register_t cllbck_every_100_ms[MAX_PERIODIC_CLLBCK] = {0};
periodic_cllbck_register_t cllbck_every_200_ms[MAX_PERIODIC_CLLBCK] = {0};
periodic_cllbck_register_t cllbck_every_500_ms[MAX_PERIODIC_CLLBCK] = {0};
periodic_cllbck_register_t cllbck_every_1000_ms[MAX_PERIODIC_CLLBCK] = {0};

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Callback all functions registered this periodic
 *
 * @param cllbck_every_x_ms \ref periodic_cllbck_register_t
 */
static void periodic_cllbcks_registers(periodic_cllbck_register_t *cllbck_every_x_ms);

/**
 * @brief Add new module all periodic struct
 *
 * @param cllbck_every_x_ms \ref periodic_cllbck_register_t
 * @return position of array save new module registered
 */
static uint8_t periodic_found_free_registers(periodic_cllbck_register_t *cllbck_every_x_ms);

/* Private functions -----------------------------------------------------------------------------*/
static void periodic_cllbcks_registers(periodic_cllbck_register_t *cllbck_every_x_ms)
{
    for (uint8_t i = 0; MAX_PERIODIC_CLLBCK > i; i++)
    {
        if (*cllbck_every_x_ms[i].cllbck && cllbck_every_x_ms[i].enable)
        {
            cllbck_every_x_ms[i].cllbck(cllbck_every_x_ms[i].arg);
        }
    }
}

//--------------------------------------------------------------------------------------------------
static uint8_t periodic_found_free_registers(periodic_cllbck_register_t *cllbck_every_x_ms)
{
    uint8_t id = UINT8_MAX;

    for (uint8_t i = 0; MAX_PERIODIC_CLLBCK > i; i++)
    {
        if (!cllbck_every_x_ms[i].cllbck)
        {
            id = i;
            i += MAX_PERIODIC_CLLBCK;
        }
    }

    return id;
}

/* Public functions ------------------------------------------------------------------------------*/
void periodic_driver_every_100ms(void)
{
    periodic_cllbcks_registers(&cllbck_every_100_ms[0]);
}

//--------------------------------------------------------------------------------------------------
void periodic_driver_every_200ms(void)
{
    periodic_cllbcks_registers(&cllbck_every_200_ms[0]);
}

//--------------------------------------------------------------------------------------------------
void periodic_driver_every_500ms(void)
{
    periodic_cllbcks_registers(&cllbck_every_500_ms[0]);
}

//--------------------------------------------------------------------------------------------------
void periodic_driver_every_1000ms(void)
{
    periodic_cllbcks_registers(&cllbck_every_1000_ms[0]);
}

//--------------------------------------------------------------------------------------------------
periodic_id_t periodic_driver_register(periodic_timers_t timers, periodic_cllbck cllbck, void *arg)
{
    uint8_t id = UINT8_MAX;
    periodic_cllbck_register_t *periodic_cllbck_register;
    periodic_id_frame_t ret = {0};

    switch (timers)
    {
    case (PERIODIC_EVERY_100_MS):
        periodic_cllbck_register = &cllbck_every_100_ms[0];
        ret.frame.timers = PERIODIC_EVERY_100_MS;
        break;
    case (PERIODIC_EVERY_200_MS):
        periodic_cllbck_register = &cllbck_every_200_ms[0];
        ret.frame.timers = PERIODIC_EVERY_200_MS;
        break;
    case (PERIODIC_EVERY_500_MS):
        periodic_cllbck_register = &cllbck_every_500_ms[0];
        ret.frame.timers = PERIODIC_EVERY_500_MS;
        break;
    case (PERIODIC_EVERY_1_SG):
        periodic_cllbck_register = &cllbck_every_1000_ms[0];
        ret.frame.timers = PERIODIC_EVERY_1_SG;
        break;
    }

    id = periodic_found_free_registers(periodic_cllbck_register);

    if (MAX_PERIODIC_CLLBCK > id)
    {
        periodic_cllbck_register[id].arg = arg;
        periodic_cllbck_register[id].cllbck = cllbck;
        periodic_cllbck_register[id].enable = NULL;
        ret.frame.id = id;
    }
    else
    {
        ret.all = NULL;
    }

    return ret.all;
}

//--------------------------------------------------------------------------------------------------
ret_code_t periodic_driver_unregister(periodic_id_t periodic_id)
{
    periodic_id_frame_t id_frame;
    id_frame.all = periodic_id;

    if (PERIODIC_EVERY_1_SG < id_frame.frame.timers || MAX_PERIODIC_CLLBCK < id_frame.frame.id)
    {
        return RET_INT_ERROR;
    }

    switch (id_frame.frame.timers)
    {
    case (PERIODIC_EVERY_100_MS):
        memset(&cllbck_every_100_ms[id_frame.frame.id], NULL, sizeof(periodic_cllbck_register_t));
        break;
    case (PERIODIC_EVERY_200_MS):
        memset(&cllbck_every_200_ms[id_frame.frame.id], NULL, sizeof(periodic_cllbck_register_t));
        break;
    case (PERIODIC_EVERY_500_MS):
        memset(&cllbck_every_500_ms[id_frame.frame.id], NULL, sizeof(periodic_cllbck_register_t));
        break;
    case (PERIODIC_EVERY_1_SG):
        memset(&cllbck_every_1000_ms[id_frame.frame.id], NULL, sizeof(periodic_cllbck_register_t));
        break;
    }

    return RET_SUCCESS;
}

//--------------------------------------------------------------------------------------------------
ret_code_t periodic_driver_enable_function(periodic_id_t periodic_id, uint8_t enable)
{
    periodic_id_frame_t id_frame;
    id_frame.all = periodic_id;

    if (PERIODIC_EVERY_1_SG < id_frame.frame.timers || MAX_PERIODIC_CLLBCK < id_frame.frame.id)
    {
        return RET_INT_ERROR;
    }

    switch (id_frame.frame.timers)
    {
    case (PERIODIC_EVERY_100_MS):
        cllbck_every_100_ms[id_frame.frame.id].enable = enable;
        break;
    case (PERIODIC_EVERY_200_MS):
        cllbck_every_200_ms[id_frame.frame.id].enable = enable;
        break;
    case (PERIODIC_EVERY_500_MS):
        cllbck_every_500_ms[id_frame.frame.id].enable = enable;
        break;
    case (PERIODIC_EVERY_1_SG):
        cllbck_every_1000_ms[id_frame.frame.id].enable = enable;
        break;
    }

    return RET_SUCCESS;
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
