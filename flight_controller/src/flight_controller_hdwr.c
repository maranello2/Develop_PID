/***************************************************************************************************
 * @file flight_controller_hdwr.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 14/02/2022
 * @date Last modification 17/02/2022 by jnieto
 * @brief periodic functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup FLIGHT_CONTROLLER_HDWR
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "flight_controller_hdwr.h"
#include "flight_controller_conductor.h"
#include <flight_controller/flight_controller_api.h>
#include <flight_controller/flight_controller_config.h>
#include <def_common.h>
#include <stdbool.h>
#include <stdint.h>
#include "hdwr/adc_api.h"
#include "gps/gps_api.h"
#include "sevcon/sevcon_api.h"
#include "user/user_api.h"

/* Defines ---------------------------------------------------------------------------------------*/
#define DIFF_ADC_SET_NEW_VALUE 0.1

/* Typedefs --------------------------------------------------------------------------------------*/
user_api_t flight_controller_api_user;

/* Private values declaration --------------------------------------------------------------------*/
float getter_diff_abs(float value1, float value2);
static void flight_controller_ratio_front_axle(ptr_obj_t arg, float data);
static void flight_controller_ratio_rear_axle(ptr_obj_t arg, float data);
static void flight_controller_max_front_slip(ptr_obj_t arg, float data);
static void flight_controller_max_rear_slip(ptr_obj_t arg, float data);
static void flight_controller_id_p_front(ptr_obj_t arg, float data);
static void flight_controller_id_i_front(ptr_obj_t arg, float data);
static void flight_controller_id_d_front(ptr_obj_t arg, float data);
static void flight_controller_id_p_rear(ptr_obj_t arg, float data);
static void flight_controller_id_i_rear(ptr_obj_t arg, float data);
static void flight_controller_id_d_rear(ptr_obj_t arg, float data);
static void flight_controller_inhibition_system(ptr_obj_t arg, float data);
static void flight_controller_cllback_gps(void *arg);

/* Private functions -----------------------------------------------------------------------------*/
float getter_diff_abs(float value1, float value2)
{

    return ((value1 > value2) ? value1 - value2 : value2 - value1);
}

//--------------------------------------------------------------------------------------------------
static void flight_controller_ratio_front_axle(ptr_obj_t arg, float data)
{
    flight_controller_t *obj = (flight_controller_t *)arg;
    obj->ratio_axle[FRONT_WHEEL_DRIVE] = data;
}

//--------------------------------------------------------------------------------------------------
static void flight_controller_ratio_rear_axle(ptr_obj_t arg, float data)
{
    flight_controller_t *obj = (flight_controller_t *)arg;
    obj->ratio_axle[REAR_WHEEL_DRIVE] = data;
}

//--------------------------------------------------------------------------------------------------
static void flight_controller_max_front_slip(ptr_obj_t arg, float data)
{
    flight_controller_t *obj = (flight_controller_t *)arg;
    obj->max_slip[FRONT_WHEEL_DRIVE] = data;
}

//--------------------------------------------------------------------------------------------------
static void flight_controller_max_rear_slip(ptr_obj_t arg, float data)
{
    flight_controller_t *obj = (flight_controller_t *)arg;
    obj->max_slip[REAR_WHEEL_DRIVE] = data;
}

//--------------------------------------------------------------------------------------------------
static void flight_controller_id_p_front(ptr_obj_t arg, float data)
{
    flight_controller_t *obj = (flight_controller_t *)arg;
    obj->id_p[FRONT_WHEEL_DRIVE] = data;
}

//--------------------------------------------------------------------------------------------------
static void flight_controller_id_i_front(ptr_obj_t arg, float data)
{
    flight_controller_t *obj = (flight_controller_t *)arg;
    obj->id_i[FRONT_WHEEL_DRIVE] = data;
}

//--------------------------------------------------------------------------------------------------
static void flight_controller_id_d_front(ptr_obj_t arg, float data)
{
    flight_controller_t *obj = (flight_controller_t *)arg;
    obj->id_d[FRONT_WHEEL_DRIVE] = data;
}

//--------------------------------------------------------------------------------------------------
static void flight_controller_id_p_rear(ptr_obj_t arg, float data)
{
    flight_controller_t *obj = (flight_controller_t *)arg;
    obj->id_p[REAR_WHEEL_DRIVE] = data;
}

//--------------------------------------------------------------------------------------------------
static void flight_controller_id_i_rear(ptr_obj_t arg, float data)
{
    flight_controller_t *obj = (flight_controller_t *)arg;
    obj->id_i[REAR_WHEEL_DRIVE] = data;
}

//--------------------------------------------------------------------------------------------------
static void flight_controller_id_d_rear(ptr_obj_t arg, float data)
{
    flight_controller_t *obj = (flight_controller_t *)arg;
    obj->id_d[REAR_WHEEL_DRIVE] = data;
}

//--------------------------------------------------------------------------------------------------
static void flight_controller_inhibition_system(ptr_obj_t arg, float data)
{
    flight_controller_t *obj = (flight_controller_t *)arg;
    obj->inhibition_system = data;
}

//--------------------------------------------------------------------------------------------------
static void flight_controller_cllback_gps(void *arg)
{
    if (arg)
    {
        flight_controller_conductor_resume_thread(arg);
    }
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t flight_controller_hdwr_init(flight_controller_t *arg)
{
    ret_code_t ret = RET_SUCCESS;

    for (uint8_t i = 0x00; i < MAX_NUM_CONTROLLER && RET_SUCCESS == ret; i++)
    {
        arg->dac_id[i] = pwm_create(&arg->cfg->dac_cfg[i]);
        ret = (arg->dac_id[i]) ? RET_SUCCESS : RET_INT_ERROR;
    }

    if (ret == RET_SUCCESS)
    {
        arg->gps = gps_init(&arg->cfg->gps_cfg);
        arg->sevcon = sevcon_init(&arg->cfg->sevcon_cfg);
        ret = (arg->gps && arg->sevcon) ? RET_SUCCESS : RET_INT_ERROR;
    }

    ret = (RET_SUCCESS == ret) ? gps_subscribe(arg->gps, flight_controller_cllback_gps, arg, arg->cfg->type_subscribe_gps) : ret;
    ret = (RET_SUCCESS == ret) ? user_init_api(arg, &flight_controller_api_user) : ret;

    return ret;
}

//--------------------------------------------------------------------------------------------------
bool flight_controller_hdwr_check_adc(flight_controller_t *arg)
{
    bool ret = false;

    for (uint8_t i = 0; i < MAX_NUM_CONTROLLER; i++)
    {
        float adc_temp = adc_get_value(arg->cfg->adc_channel[i]) - arg->adc_offset[i];

        if (getter_diff_abs(adc_temp, arg->adc_values[i]) > DIFF_ADC_SET_NEW_VALUE)
        {
            arg->adc_values[i] = adc_temp;
            ret = true;
        }
    }

    return ret;
}

//--------------------------------------------------------------------------------------------------
ret_code_t flight_controller_hdwr_start(flight_controller_t *arg)
{
    ret_code_t ret = RET_SUCCESS;

    for (uint8_t i = 0x00; i < MAX_NUM_CONTROLLER && RET_SUCCESS == ret; i++)
    {
        arg->adc_offset[i] = adc_get_value(arg->cfg->adc_channel[i]);
        ret = (RET_SUCCESS == pwm_start(arg->dac_id[i])) ? RET_SUCCESS : RET_INT_ERROR;
    }

    return ret;
}

//--------------------------------------------------------------------------------------------------
ret_code_t flight_controller_hdwr_set_dac(pwm_id_t arg, uint16_t value_dac)
{
    return pwm_set_new_duty(arg, value_dac);
}

user_api_t flight_controller_api_user = {
    .ratio_front_axle = flight_controller_ratio_front_axle,
    .ratio_rear_axle = flight_controller_ratio_rear_axle,
    .max_front_slip = flight_controller_max_front_slip,
    .max_rear_slip = flight_controller_max_rear_slip,
    .id_p_front = flight_controller_id_p_front,
    .id_i_front = flight_controller_id_i_front,
    .id_d_front = flight_controller_id_d_front,
    .id_p_rear = flight_controller_id_p_rear,
    .id_i_rear = flight_controller_id_i_rear,
    .id_d_rear = flight_controller_id_d_rear,
    .inhibition_system = flight_controller_inhibition_system,
};

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
