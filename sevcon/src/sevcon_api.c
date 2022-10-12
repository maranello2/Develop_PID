/***************************************************************************************************
 * @file sevcon_api.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 06/03/2022
 * @date Last modification 18/04/2021 by jnieto
 * @brief SEVCON functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup SEVCON_API
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include <sevcon/sevcon_api.h>
#include <def_common.h>

#include "sevcon_conductor.h"
#include "sevcon_driver.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
sevcon_id_t sevcon_init(sevcon_cfg_t *cfg)
{
    ret_code_t ret = RET_INT_ERROR;

    if (!cfg)
    {
        return ret;
    }

    return sevcon_conductor_init(cfg);
}

//--------------------------------------------------------------------------------------------------
float sevcon_get_velocity_in_m_s(sevcon_id_t arg, uint16_t num_driver)
{
    if (!arg || num_driver > SEVCON_MAX_DRIVERS)
    {
        return UINT32_MAX;
    }

    sevcon_t *obj = (sevcon_t *)arg;

    return (sevcon_driver_get_velocity(obj, num_driver));
}

//--------------------------------------------------------------------------------------------------
uint16_t sevcon_get_position_wheel_driver(sevcon_id_t arg, uint16_t num_driver)
{
    if (!arg || num_driver > SEVCON_MAX_DRIVERS)
    {
        return UINT16_MAX;
    }
    
    uint16_t ret = UINT16_MAX;

    switch (num_driver)
    {
    case MOTOR_FRONT_LEFT:
    case MOTOR_FRONT_RIGHT:
        ret = FRONT_WHEEL_DRIVE;
        break;
    case MOTOR_REAR_LEFT:
    case MOTOR_REAR_RIGHT:
        ret = REAR_WHEEL_DRIVE;
        break;

    default:
        break;
    }

    return ret;
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
