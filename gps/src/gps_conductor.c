/***************************************************************************************************
 * @file GPS_conductor.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 15/03/2022
 * @date Last modification 15/03/2022 by jnieto
 * @brief gps functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup GPS_CONDUCTOR
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include <def_common.h>
#include <stdlib.h>
#include <string.h>
#include <cmsis_os2.h>

#include "gps_conductor.h"
#include "gps_driver.h"
#include "gps_hdwr.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** Definitions for defaultTask */
osThreadAttr_t gps_task_attributes =
    {
        .priority = (osPriority_t)osPriorityNormal,
        .name = "GPS",
        .stack_size = 512,
};

/** Struct register callback */
typedef struct
{
    gps_cllbck cllbck; /**< ptr function callback */
    void *arg;         /**< arg send callback */
} gps_cllbck_reg_t;

gps_cllbck_reg_t gps_cllbck_reg[MAX_SUBSCRIBE_GPS];

/* Private values --------------------------------------------------------------------------------*/
gps_t *gps;

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Run thread
 *
 * @param argument \ref NULL
 */
void gps_task(void *argument);

/* Private functions -----------------------------------------------------------------------------*/
void gps_task(void *argument)
{
    if (argument)
    {
        gps_driver_get_msg(argument);
    }
}

/* Public functions ------------------------------------------------------------------------------*/
gps_id_t gps_conductor_init(gps_cfg_t *cfg)
{
    ret_code_t ret = RET_INT_ERROR;

    gps = calloc(1, sizeof(gps_t));
    if (gps)
    {
        gps->name = gps_task_attributes.name;
        gps->id_thread = osThreadNew(gps_task, gps, &gps_task_attributes);
        ret = (gps->id_thread) ? RET_SUCCESS : RET_INT_ERROR;
    }

    ret = (RET_SUCCESS == ret) ? gps_hdwr_init(cfg, gps) : ret;

    ret = (RET_SUCCESS == ret) ? gps_driver_log_init(gps) : ret;

    return ((RET_SUCCESS == ret) ? (gps_id_t)gps : NULL);
}

//--------------------------------------------------------------------------------------------------
gps_t *gps_getter_instace()
{
    return gps;
}

//--------------------------------------------------------------------------------------------------
ret_code_t gps_conductor_subscribe(gps_id_t id, gps_cllbck cllbck, void *arg, type_subscribe_gps_t type_subscribe_gps)
{
    if (!gps_cllbck_reg[type_subscribe_gps].cllbck && !gps_cllbck_reg[type_subscribe_gps].arg)
    {
        gps_cllbck_reg[type_subscribe_gps].cllbck = cllbck;
        gps_cllbck_reg[type_subscribe_gps].arg = arg;
        return RET_SUCCESS;
    }

    return RET_INT_ERROR;
}

//--------------------------------------------------------------------------------------------------
void gps_conductor_notify_new_data(type_subscribe_gps_t type_subscribe_gps)
{
    if (type_subscribe_gps < MAX_SUBSCRIBE_GPS && gps_cllbck_reg[type_subscribe_gps].cllbck && gps_cllbck_reg[type_subscribe_gps].arg)
    {
        gps_cllbck_reg[type_subscribe_gps].cllbck(gps_cllbck_reg[type_subscribe_gps].arg);
    }
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
