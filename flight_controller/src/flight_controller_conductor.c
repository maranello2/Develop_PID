/***************************************************************************************************
 * @file flight_controller_conductor.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 14/02/2022
 * @date Last modification 11/04/2021 by jnieto
 * @brief FLIGHT_CONTROLLER functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup FLIGHT_CONTROLLER_CONDUCTOR
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "flight_controller_conductor.h"
#include "cmsis_os2.h"
#include <stdlib.h>
#include <def_common.h>
#include <stdio.h>
#include "flight_controller_hdwr.h"
#include "flight_controller_driver.h"
#include "stdint.h"

/* Defines ---------------------------------------------------------------------------------------*/
#define CONVERT_TICK_SYS_TO_MS 100

/* Typedefs --------------------------------------------------------------------------------------*/
/** Definitions for defaultTask */
osThreadAttr_t flight_controller_task_attributes =
    {
        .priority = (osPriority_t)osPriorityNormal,
        .stack_size = 1024,
};

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Run thread
 *
 * @param arg \ref flight_controller_cfg_t
 */
static void fligth_controller_thread(void *arg);

/**
 * @brief Get the diff time object
 *
 * @param obj flight_controller_t
 * @return uint32_t diff actual tick with last tick
 */
static uint32_t get_diff_time(flight_controller_t *obj);

/**
 * @brief Update actual tick of the system
 *
 * @param obj
 * @return uint32_t
 */
static uint32_t update_tick(flight_controller_t *obj);

/* Private functions -----------------------------------------------------------------------------*/
static uint32_t get_diff_time(flight_controller_t *obj)
{
    uint32_t ret;
    uint32_t actual_time = osKernelGetTickCount(); // ms

    ret = (actual_time > obj->time.last_time) ? obj->time.last_time - actual_time : (obj->time.last_time - UINT32_MAX) + actual_time;

    // Every tick is 100ms
    return (ret * CONVERT_TICK_SYS_TO_MS);
}

//--------------------------------------------------------------------------------------------------
static uint32_t update_tick(flight_controller_t *obj)
{
    return osKernelGetTickCount();
}

//--------------------------------------------------------------------------------------------------
static void fligth_controller_thread(void *arg)
{
    if (!arg)
    {
        return;
    }

    flight_controller_t *fligth_ctrl_thread = (flight_controller_t *)arg;

    flight_controller_driver_start_periodic(fligth_ctrl_thread);
    flight_controller_hdwr_start(fligth_ctrl_thread);
    fligth_ctrl_thread->mutex_flag_thread = false;

    while (1)
    {
        osThreadFlagsWait(0x00, osFlagsWaitAny, osWaitForever);

        fligth_ctrl_thread->time.diff_time = get_diff_time(fligth_ctrl_thread); // ms

        // Update ADC
        flight_controller_hdwr_check_adc(fligth_ctrl_thread);
        // calculate PD
        flight_controller_driver_update_dac(fligth_ctrl_thread);

        // Update values
        fligth_ctrl_thread->mutex_flag_thread = false;
        fligth_ctrl_thread->time.last_time = update_tick(fligth_ctrl_thread);
    }
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t flight_controller_conductor_init(flight_controller_cfg_t *cfg)
{
    ret_code_t ret = RET_INT_ERROR;

    flight_controller_t *flight_controller = calloc(1, sizeof(flight_controller_t));
    ret = (flight_controller) ? RET_SUCCESS : RET_INT_ERROR;

    if (RET_SUCCESS == ret)
    {
        flight_controller->cfg = cfg;

        ret = flight_controller_driver_init(flight_controller);
    }

    ret = (RET_SUCCESS == ret) ? flight_controller_hdwr_init(flight_controller) : ret;

    if (RET_SUCCESS == ret)
    {
        flight_controller_task_attributes.name = cfg->name ? cfg->name : "unknown";

        flight_controller->thread_id =
            (RET_SUCCESS == ret) ? osThreadNew(fligth_controller_thread, flight_controller,
                                               &flight_controller_task_attributes)
                                 : NULL;
        ret = (flight_controller->thread_id != NULL) ? RET_SUCCESS : RET_INT_ERROR;
    }

    ret = (RET_SUCCESS == ret) ? flight_controller_driver_log_init(flight_controller) : ret;

    return ret;
}

//--------------------------------------------------------------------------------------------------
void flight_controller_conductor_resume_thread(flight_controller_t *arg)
{
    if (arg && arg->thread_id && arg->mutex_flag_thread == false)
    {
        flight_controller_t *obj = (flight_controller_t *)arg;
        obj->mutex_flag_thread = true;
        osThreadResume(obj->thread_id);
    }
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
