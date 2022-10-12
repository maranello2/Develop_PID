/***************************************************************************************************
 * @file user_api.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 31/03/2022
 * @date Last modification 31/03/2022 by jnieto
 * @brief USER functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup USER_API
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "user/user_api.h"
#include "user_conductor.h"

#include <def_common.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t user_init(user_cfg_t *cfg)
{
    if (cfg)
    {
        return (user_conductor_init(cfg));
    }

    return NULL;
}

ret_code_t user_init_api (void *obj, user_api_t *api)
{
    if (!obj ) return RET_INT_ERROR;

    ret_code_t ret = RET_SUCCESS;
    user_t *obj_lv = user_conductor_getter_get_obj ();

    obj_lv->api = *api;
    obj_lv->ptr_data_api = obj;

    return ret;
}

//--------------------------------------------------------------------------------------------------
float user_get_ratio_front_axle(void)
{
    user_t *obj = user_conductor_getter_get_obj ();
    return obj->ratio_front_axle;
}

//--------------------------------------------------------------------------------------------------
float user_get_ratio_rear_axle(void)
{
    user_t *obj = user_conductor_getter_get_obj ();
    return obj->ratio_rear_axle;
}

//--------------------------------------------------------------------------------------------------
float user_get_max_front_slip(void)
{
    user_t *obj = user_conductor_getter_get_obj ();
    return obj->max_front_slip;
}

//--------------------------------------------------------------------------------------------------
float user_get_max_rear_slip(void)
{
    user_t *obj = user_conductor_getter_get_obj ();
    return obj->max_rear_slip;
}

//--------------------------------------------------------------------------------------------------
float user_get_id_p_front(void)
{
    user_t *obj = user_conductor_getter_get_obj ();
    return obj->id_p_front;
}

//--------------------------------------------------------------------------------------------------
float user_get_id_i_front(void)
{
    user_t *obj = user_conductor_getter_get_obj ();
    return obj->id_i_front;
}

//--------------------------------------------------------------------------------------------------
float user_get_id_d_front(void)
{
    user_t *obj = user_conductor_getter_get_obj ();
    return obj->id_d_front;
}

//--------------------------------------------------------------------------------------------------
float user_get_id_p_rear(void)
{
    user_t *obj = user_conductor_getter_get_obj ();
    return obj->id_p_rear;
}

//--------------------------------------------------------------------------------------------------
float user_get_id_i_rear(void)
{
    user_t *obj = user_conductor_getter_get_obj ();
    return obj->id_i_rear;
}

//--------------------------------------------------------------------------------------------------
float user_get_id_d_rear(void)
{
    user_t *obj = user_conductor_getter_get_obj ();
    return obj->id_d_rear;
}

//--------------------------------------------------------------------------------------------------
float user_get_inhibition_system(void)
{
    user_t *obj = user_conductor_getter_get_obj ();
    return obj->inhibition_system;
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
