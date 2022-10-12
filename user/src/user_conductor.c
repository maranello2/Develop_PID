/***************************************************************************************************
 * @file user_conductor.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 31/03/2022
 * @date Last modification 02/04/2022 by jnieto
 * @brief USER functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup USER_CONDUCTOR
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "user/user_api.h"
#include "user_conductor.h"
#include "user_driver.h"
#include "user_hdwr.h"
#include "cmsis_os2.h"
#include <def_common.h>
#include <stdlib.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** Definitions for defaultTask */
osThreadAttr_t user_task_attributes =
    {
        .priority = (osPriority_t)osPriorityLow,
        .name = "USER",
        .stack_size = 128 * 2,
};

/* Private values --------------------------------------------------------------------------------*/
/** Struct data */
user_t *obj;

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Run thread
 *
 * @param argument \ref NULL
 */
void user_task(void *argument);

/* Private functions -----------------------------------------------------------------------------*/
void user_task(void *argument)
{
    if (argument)
    {
        user_driver_get_msg(argument);
    }
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t user_conductor_init(user_cfg_t *cfg)
{
    obj = calloc(1, sizeof(user_t));
    ret_code_t ret = (obj) ? RET_SUCCESS : RET_INT_ERROR;

    if (ret == RET_SUCCESS)
    {
        obj->id_thread = osThreadNew(user_task, obj, &user_task_attributes);
        ret = (obj->id_thread) ? RET_SUCCESS : RET_INT_ERROR;
    }

    ret = (RET_SUCCESS == ret) ? user_hdwr_init(obj, cfg) : ret;

    return ret;
}

//--------------------------------------------------------------------------------------------------
user_t *user_conductor_getter_get_obj ()
{
    return obj;
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
