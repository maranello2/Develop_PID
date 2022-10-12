/***************************************************************************************************
 * @file sevcon_hdwr.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 06/03/2022
 * @date Last modification 07/03/2022 by jnieto
 * @brief SEVCON functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup SEVCON_HDWR
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "sevcon_hdwr.h"
#include <stdint.h>

#include <hdwr/can_api.h>
#include <sevcon/sevcon_config.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/
/** Message CAN */
can_msg_t msg_servcon;

/* Private functions declaration -----------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t sevcon_hdwr_init(sevcon_cfg_t *cfg, sevcon_t *data)
{
    ret_code_t ret = RET_INT_ERROR;

    cfg->fifo_cfg.size_msg = sizeof(can_msg_t);

    data->fifo_id = fifo_create_queue(&cfg->fifo_cfg);

    ret = (data->fifo_id) ? can_suscribe_rx_fifo(data->fifo_id) : ret;

    return ret;
}

//--------------------------------------------------------------------------------------------------
void *sevcon_hdwr_get_msg(sevcon_t *sevcon)
{

    return (RET_SUCCESS == fifo_dequeue_msg(sevcon->fifo_id, &msg_servcon)) ? &msg_servcon : NULL;
}

//--------------------------------------------------------------------------------------------------
uint16_t sevcon_hdwr_get_index(void *msg)
{
    can_msg_t *can_msg = (can_msg_t *)msg;

    return canopen_get_index(can_msg);
}

//--------------------------------------------------------------------------------------------------
uint16_t sevcon_hdwr_get_subindex(void *msg)
{
    can_msg_t *can_msg = (can_msg_t *)msg;

    return canopen_get_subindex(can_msg);
}

//--------------------------------------------------------------------------------------------------
uint32_t sevcon_hdwr_get_data(void *msg)
{
    can_msg_t *can_msg = (can_msg_t *)msg;

    return canopen_get_data(can_msg);
}

//--------------------------------------------------------------------------------------------------
uint16_t sevcon_hdwr_get_num_sevcon(void *msg)
{
    can_msg_t *can_msg = (can_msg_t *)msg;

    return (can_msg->id_frame - OD_TYPE_MSG_CAN);
}

//--------------------------------------------------------------------------------------------------
uint16_t sevcon_hdwr_get_opposite_motor(uint16_t id_motor)
{
    uint16_t ret = UINT16_MAX;
    switch (id_motor)
    {
    case MOTOR_FRONT_LEFT:
        ret = MOTOR_OPPOSITE_FRONT_LEFT;
        break;
    case MOTOR_FRONT_RIGHT:
        ret = MOTOR_OPPOSITE_FRONT_RIGHT;
        break;
    case MOTOR_REAR_LEFT:
        ret = MOTOR_OPPOSITE_REAR_LEFT;
        break;
    case MOTOR_REAR_RIGHT:
        ret = MOTOR_OPPOSITE_REAR_RIGHT;
        break;
    }

    return ret;
}
/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
