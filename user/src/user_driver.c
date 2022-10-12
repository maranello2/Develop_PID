/***************************************************************************************************
 * @file user_driver.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 31/03/2022
 * @date Last modification 02/04/2022 by jnieto
 * @brief USER functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup USER_DRIVER
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "user_driver.h"
#include "user_hdwr.h"
#include <user/user_api.h>
#include <user/user_config.h>
#include <hdwr/ieee754.h>

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "cmsis_os2.h"

/* Defines ---------------------------------------------------------------------------------------*/
#define SHIFT_BYTE 8

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/
static void proccess_message(user_t *obj, uint8_t *data);
static void set_data_on_object(user_t *obj, uint8_t *data);
static uint32_t get_value_data(uint8_t *data);

/* Private functions -----------------------------------------------------------------------------*/
static void proccess_message(user_t *obj, uint8_t *data)
{
    if (data[0] == USER_HEADER)
    {
        uint16_t count_msg = USER_SIZE_HEADER;
        do
        {
            set_data_on_object(obj, &data[count_msg]);
            count_msg += USER_SIZE_PAYLOAD;
        } while (count_msg < obj->length_msg_rx);
    }
}

//--------------------------------------------------------------------------------------------------
static void set_data_on_object(user_t *obj, uint8_t *data)
{
    if (!data)
        return;
    uint32_t value = get_value_data(data);

    switch ((user_ids_t)data[0])
    {
    case (USER_ID_RATIO_FRONT_AXLE):
        obj->ratio_front_axle = (unpack754_32(&value));
        if (obj->api.ratio_front_axle && obj->ptr_data_api)
        {
            obj->api.ratio_front_axle(obj->ptr_data_api, obj->ratio_front_axle);
        }
        break;
    case (USER_ID_RATIO_REAR_AXLE):
        obj->ratio_rear_axle = (unpack754_32(&value));
        if (obj->api.ratio_rear_axle && obj->ptr_data_api)
        {
            obj->api.ratio_rear_axle(obj->ptr_data_api, obj->ratio_rear_axle);
        }
        break;
    case (USER_ID_MAX_FRONT_SLIP):
        obj->max_front_slip = (unpack754_32(&value));
        if (obj->api.max_front_slip && obj->ptr_data_api)
        {
            obj->api.max_front_slip(&obj->ptr_data_api, obj->max_front_slip);
        }
        break;
    case (USER_ID_MAX_REAR_SLIP):
        obj->max_rear_slip = (unpack754_32(&value));
        if (obj->api.max_rear_slip && obj->ptr_data_api)
        {
            obj->api.max_rear_slip(obj->ptr_data_api, obj->max_rear_slip);
        }
        break;
    case (USER_ID_P_REAR):
        obj->id_p_rear = (unpack754_32(&value));
        if (obj->api.id_p_rear && obj->ptr_data_api)
        {
            obj->api.id_p_rear(obj->ptr_data_api, obj->id_p_rear);
        }
        break;
    case (USER_ID_I_REAR):
        obj->id_i_rear = (unpack754_32(&value));
        if (obj->api.id_i_rear && obj->ptr_data_api)
        {
            obj->api.id_i_rear(obj->ptr_data_api, obj->id_i_rear);
        }
        break;
    case (USER_ID_D_REAR):
        obj->id_d_rear = (unpack754_32(&value));
        if (obj->api.id_d_rear && obj->ptr_data_api)
        {
            obj->api.id_d_rear(obj->ptr_data_api, obj->id_d_rear);
        }
        break;
    case (USER_ID_P_FRONT):
        obj->id_p_front = (unpack754_32(&value));
        if (obj->api.id_p_front && obj->ptr_data_api)
        {
            obj->api.id_p_front(obj->ptr_data_api, obj->id_p_front);
        }
        break;
    case (USER_ID_I_FRONT):
        obj->id_i_front = (unpack754_32(&value));
        if (obj->api.id_i_front && obj->ptr_data_api)
        {
            obj->api.id_i_front(obj->ptr_data_api, obj->id_i_front);
        }
        break;
    case (USER_ID_D_FRONT):
        obj->id_d_front = (unpack754_32(&value));
        if (obj->api.id_d_front && obj->ptr_data_api)
        {
            obj->api.id_d_front(obj->ptr_data_api, obj->id_d_front);
        }
        break;
    case (USER_ID_INHIBITION_SYSTEM):
        obj->inhibition_system = (unpack754_32(&value));
        if (obj->api.inhibition_system && obj->ptr_data_api)
        {
            obj->api.inhibition_system(obj->ptr_data_api, obj->inhibition_system);
        }
        break;
    }
}

//--------------------------------------------------------------------------------------------------
static uint32_t get_value_data(uint8_t *data)
{
    uint32_t ret = 0, lv_data;
    uint8_t idx, i;

    for (i = 0; i < (USER_SIZE_PAYLOAD - 1); i++)
    {
        idx = (USER_SIZE_PAYLOAD - 1) - i;
        lv_data = data[idx];
        ret += (lv_data << (SHIFT_BYTE * i));
    }
    return ret;
}
/* Public functions ------------------------------------------------------------------------------*/
void user_driver_get_msg(void *arg)
{
    user_t *obj = (user_t *)arg;
    void *msg;

    while (1)
    {
        msg = user_hdwr_get_msg(obj);

        if (msg)
        {
            proccess_message(obj, msg);
        }
    }
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
