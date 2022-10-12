/***************************************************************************************************
 * @file sevcon_driver.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 06/03/2022
 * @date Last modification 18/04/2022 by jnieto
 * @brief SEVCON functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup SEVCON_DRIVER
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "sevcon_driver.h"
#include "sevcon_hdwr.h"
#include "sevcon_driver_dictionary.h"
#include "sevcon/sevcon_config.h"

#include <def_common.h>
#include <log/log_api.h>
#include <stdio.h>
#include <stdint.h>

#include <hdwr/can_api.h>
#include <flight_controller/flight_controller_api.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Process new message
 *
 * @param sevcon \ref sevcon_t
 * @param msg ptr to void
 */
void sevcon_proccess_message(sevcon_t *sevcon, void *msg);

/**
 * @brief Proccess message of velocity
 *
 * @param sevcon \ref sevcon_t
 */
static void sevcon_proccess_velocity(sevcon_t *sevcon, uint16_t id_sevcon, uint32_t data);

/**
 * @brief Proccess message of temperature
 *
 * @param sevcon \ref sevcon_t
 */
static void sevcon_proccess_temperature(sevcon_t *sevcon, uint16_t id_sevcon, uint32_t data);

/**
 * @brief Proccess message of error
 *
 * @param sevcon \ref sevcon_t
 */
static void sevcon_proccess_error(sevcon_t *sevcon, uint16_t id_sevcon, uint32_t data);

/* Private functions -----------------------------------------------------------------------------*/
void sevcon_proccess_message(sevcon_t *sevcon, void *msg)
{

    uint16_t id_sevcon = sevcon_hdwr_get_num_sevcon(msg);
    if (id_sevcon >= SEVCON_MAX_DRIVERS)
    {
        // Force exit because id does not exists
        return;
    }

    uint16_t idx = sevcon_hdwr_get_index(msg);
    uint16_t subidx = sevcon_hdwr_get_subindex(msg);

    switch (sevcon_dictionary_found_id(idx, subidx))
    {
    case VELOCITY:
        sevcon_proccess_velocity(sevcon, id_sevcon, sevcon_hdwr_get_data(msg));
        break;
    case MOTOR_TEMPERATURE_1:
        sevcon_proccess_temperature(sevcon, id_sevcon, sevcon_hdwr_get_data(msg));
        break;
    case ERROR_SEVCON:
        sevcon_proccess_error(sevcon, id_sevcon, sevcon_hdwr_get_data(msg));
        break;
    case MAX_DICTIONARY:
    default:
        // printf("MAX_DICTIONARY\n");
        break;
    }
}

//--------------------------------------------------------------------------------------------------
static void sevcon_proccess_velocity(sevcon_t *sevcon, uint16_t id_sevcon, uint32_t data)
{
    if (data != sevcon->driver[id_sevcon].vel_rpm)
    {
        uint16_t opposite_motor = sevcon_hdwr_get_opposite_motor(id_sevcon);

        sevcon->driver[id_sevcon].vel_rpm = data;
        sevcon->driver[id_sevcon].vel_m_s = (data * WHEEL_SPOKE) * CONTS_RPM_WHEEL_AXLE;
    }
}

//--------------------------------------------------------------------------------------------------
static void sevcon_proccess_temperature(sevcon_t *sevcon, uint16_t id_sevcon, uint32_t data)
{
    driver_data_t *driver = &sevcon->driver[id_sevcon];

    if (data != driver->temperature)
    {
        uint16_t opposite_motor = sevcon_hdwr_get_opposite_motor(id_sevcon);

        driver->temperature = data;
#if 0
        if (driver->temperature > WRN_TEMP_LEVEL_1 && !driver->warning_temp)
        {
            flight_controller_increase(id_sevcon, WRN_DECREASE_MOTOR_WORKING_LVL_1);
            flight_controller_increase(opposite_motor, WRN_DECREASE_MOTOR_WORKING_LVL_1);
            driver->warning_temp = WRN_DECREASE_MOTOR_WORKING_LVL_1;
        }
        else if (driver->temperature > WRN_TEMP_LEVEL_2)
        {
            int16_t lvl_decrease = WRN_DECREASE_MOTOR_WORKING_LVL_1 - WRN_DECREASE_MOTOR_WORKING_LVL_2;
            flight_controller_increase(id_sevcon, lvl_decrease);
            flight_controller_increase(opposite_motor, lvl_decrease);
            driver->warning_temp = lvl_decrease;
        }
        else if (driver->warning_temp)
        {
            driver->warning_temp = false;
            flight_controller_decrease(id_sevcon, driver->warning_temp);
            flight_controller_decrease(opposite_motor, driver->warning_temp);
            driver->warning_temp = 0;
        }
#endif
    }
}

//--------------------------------------------------------------------------------------------------
static void sevcon_proccess_error(sevcon_t *sevcon, uint16_t id_sevcon, uint32_t data)
{
    driver_data_t *driver = &sevcon->driver[id_sevcon];
    uint16_t opposite_motor = sevcon_hdwr_get_opposite_motor(id_sevcon);

    // Sevcon with error
    if (data)
    {
        driver->error = data;
        flight_controller_increase(id_sevcon, WRN_DECREASE_MOTOR_WORKING_ERROR);
        flight_controller_increase(opposite_motor, WRN_DECREASE_MOTOR_WORKING_ERROR);
    }
    // Sevcon withou error now, but Sevcon has a error
    else if (driver->error)
    {
        driver->error = 0;
        flight_controller_decrease(id_sevcon, WRN_DECREASE_MOTOR_WORKING_ERROR);
        flight_controller_decrease(opposite_motor, WRN_DECREASE_MOTOR_WORKING_ERROR);
    }
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t sevcon_driver_log_init(sevcon_t *sevcon)
{
    char msg[20];

    sprintf(msg, "CREATED 0x%x", sevcon);

    return (log_new_msg(sevcon->name, LOG_DEBUG, msg));
}

//--------------------------------------------------------------------------------------------------
void sevcon_driver_get_msg(void *arg)
{
    sevcon_t *sevcon = (sevcon_t *)arg;
    void *msg;

    while (1)
    {
        msg = sevcon_hdwr_get_msg(sevcon);
        if (msg)
        {
            sevcon_proccess_message(sevcon, msg);
        }
    }
}

//--------------------------------------------------------------------------------------------------
float sevcon_driver_get_velocity(sevcon_t *obj, uint16_t num_driver)
{
    return (obj->driver[num_driver].vel_m_s);
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
