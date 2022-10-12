/***************************************************************************************************
 * @file flight_controller_driver.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 14/02/2022
 * @date Last modification 18/04/2022 by jnieto
 * @brief FLIGHT_CONTROLLER functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup FLIGHT_CONTROLLER_DRIVER
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "flight_controller/flight_controller_api.h"
#include <def_common.h>
#include "flight_controller_conductor.h"
#include "flight_controller_driver.h"
#include "flight_controller_hdwr.h"
#include "log/log_api.h"
#include "hdwr/ieee754.h"
#include <stdio.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
typedef struct
{
    uint32_t last_time; /**< get last tick after It calculated PD */
    uint32_t diff_time; /**< It diff last tic with actual tick */
} times_t;



/* Private values --------------------------------------------------------------------------------*/
uint16_t decrease_max_percent_working[MAX_NUM_CONTROLLER];
uint16_t delay_tx_msg, tx_front_rear = 0;

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Funtion for periodic
 *
 * @param arg \ref flight_controller_t
 */
static void
flight_controller_driver_periodic(void *arg);

/* Private functions -----------------------------------------------------------------------------*/
static void flight_controller_driver_periodic(void *arg)
{
    if (arg)
    {
        flight_controller_t *obj = (flight_controller_t *)arg;
        flight_controller_driver_loop_send_values(obj);
    }
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t flight_controller_driver_init(flight_controller_t *arg)
{
    arg->periodic_id = periodic_register((periodic_timers_t)arg->cfg->periodic_timer,
                                         flight_controller_driver_periodic,
                                         arg);

    // Set default values
    arg->max_slip[FRONT_WHEEL_DRIVE] = FLIGTH_CONTROLLER_SLIP_FRONT_DEFAULT;
    arg->max_slip[REAR_WHEEL_DRIVE] = FLIGTH_CONTROLLER_SLIP_REAR_DEFAULT;
    arg->id_p[FRONT_WHEEL_DRIVE] = FLIGTH_CONTROLLER_P_FRONT_DEFAULT;
    arg->id_i[FRONT_WHEEL_DRIVE] = FLIGTH_CONTROLLER_I_FRONT_DEFAULT;
    arg->id_d[FRONT_WHEEL_DRIVE] = FLIGTH_CONTROLLER_D_FRONT_DEFAULT;
    arg->id_p[REAR_WHEEL_DRIVE] = FLIGTH_CONTROLLER_P_REAR_DEFAULT;
    arg->id_i[REAR_WHEEL_DRIVE] = FLIGTH_CONTROLLER_I_REAR_DEFAULT;
    arg->id_d[REAR_WHEEL_DRIVE] = FLIGTH_CONTROLLER_D_REAR_DEFAULT;
    arg->ratio[FRONT_WHEEL_DRIVE] = FLIGTH_CONTROLLER_RATIO_FRONT_DEFAULT;
    arg->ratio[REAR_WHEEL_DRIVE] = FLIGTH_CONTROLLER_RATIO_REAR_DEFAULT;


    return (arg->periodic_id ? RET_SUCCESS : RET_INT_ERROR);
}

//--------------------------------------------------------------------------------------------------
ret_code_t flight_controller_driver_start_periodic(flight_controller_t *arg)
{
    if (arg->periodic_id)
    {
        return periodic_start(arg->periodic_id);
    }

    return RET_INT_ERROR;
}

//--------------------------------------------------------------------------------------------------
ret_code_t flight_controller_driver_stop_periodic(flight_controller_t *arg)
{
    if (arg->periodic_id)
    {
        return periodic_stop(arg->periodic_id);
    }

    return RET_INT_ERROR;
}

//--------------------------------------------------------------------------------------------------
void flight_controller_driver_update_dac(flight_controller_t *arg)
{
    float breakout = 1.0;

    // Get value velocity real in m\s
    float v_real = gps_get_velocity_north_axis(arg->gps);

    for (uint8_t idx_motor = 0x00; idx_motor < MAX_NUM_CONTROLLER; idx_motor++)
    {
        // Get position wheel driver FRONT O REAR
        uint16_t wheel_driver = sevcon_get_position_wheel_driver(arg->sevcon, idx_motor);

        // Calculate slip every motor in % over velocity real
        float measured = sevcon_get_velocity_in_m_s(arg->sevcon, idx_motor) / arg->ratio[wheel_driver] ;
        arg->slip[idx_motor] = (v_real > 0.3) ? (measured/v_real) - 1 : 0.0; //%

        if (wheel_driver != UINT16_MAX && arg->slip[idx_motor] > arg->max_slip[wheel_driver]) //PID Calculation
        {
            // get error
            float error = arg->arg->slip[idx_motor] - max_slip[wheel_driver];
            float derivative = error - arg->last_error[idx_motor];
            // Calculate PID
            breakout = 1 - abs((arg->id_p[wheel_driver] * error + arg->id_d[wheel_driver] * derivative) / arg->diff_time);
            // update values
            arg->last_error[idx_motor] = error;
        } // END if wheel_driver
        else
        {
            // No control
            breakout = 1.0;
        }

        arg->dac_values[idx_motor] = (uint16_t)(((arg->adc_values[idx_motor] * 100.0) / 3.0) * breakout);
        // Add max percent working
        //arg->dac_values[idx_motor] = (arg->dac_values[idx_motor] > decrease_max_percent_working[idx_motor]) ? decrease_max_percent_working[idx_motor] : arg->dac_values[idx_motor];
        // Inverter PWM
        arg->dac_values[idx_motor] = 100 - arg->dac_values[idx_motor];
        flight_controller_hdwr_set_dac(arg->dac_id[idx_motor], arg->dac_values[idx_motor]);
    } // END for
}

//--------------------------------------------------------------------------------------------------
ret_code_t flight_controller_driver_log_init(flight_controller_t *arg)
{
    char msg[20];

    sprintf(msg, "CREATED 0x%x", arg);

    return (log_new_msg(arg->cfg->name, LOG_DEBUG, msg));
}

//--------------------------------------------------------------------------------------------------
void flight_controller_driver_decrease(uint16_t id, uint16_t value)
{
    decrease_max_percent_working[id] += value;
    if (decrease_max_percent_working[id] > 100)
    {
        decrease_max_percent_working[id] = 100;
    }
}

//--------------------------------------------------------------------------------------------------
void flight_controller_driver_increase(uint16_t id, uint16_t value)
{
    decrease_max_percent_working[id] = (decrease_max_percent_working[id] > value) ? decrease_max_percent_working[id] - value : 0;
}

//--------------------------------------------------------------------------------------------------
void flight_controller_driver_loop_send_values(flight_controller_t *arg)
{
    if (delay_tx_msg % 2 == 0)
    {
        uint32_t value_send[4] = {0};
        uint8_t frame_tx[MAX_SIZEOF_TX_VALUES], j = 2;
        frame_tx[0] = FLIGTH_CONTROLLER_HEAD;
        // Send fast values
        if (delay_tx_msg < 8)
        {
            frame_tx[1] = FLIGTH_CONTROLLER_ID_DATA_SLIPT;
            for (uint8_t i = 0; i < MAX_NUM_CONTROLLER; i++)
            {
                value_send[i] = pack754_32(&arg->slip[i]);
            }
        }
        // Send slow values
        else
        {
            delay_tx_msg = 1;
            frame_tx[1] = (tx_front_rear == FRONT_WHEEL_DRIVE) ? FLIGTH_CONTROLLER_ID_DATA_FRONT : FLIGTH_CONTROLLER_ID_DATA_REAR;
            value_send[0] = pack754_32(&arg->id_p[tx_front_rear]);
            value_send[1] = pack754_32(&arg->id_i[tx_front_rear]);
            value_send[2] = pack754_32(&arg->id_d[tx_front_rear]);
            value_send[3] = pack754_32(&arg->max_slip[tx_front_rear]);
            tx_front_rear = (tx_front_rear == FRONT_WHEEL_DRIVE) ? REAR_WHEEL_DRIVE : FRONT_WHEEL_DRIVE;
        }
        // convert uint32 to char
        for (uint8_t i = 0; i < MAX_NUM_CONTROLLER; i++)
        {
            for (uint8_t z = 0; z < 4; z++)
            {
                frame_tx[j + z] = value_send[i] & 0x000000FF;
                value_send[i] = value_send[i] >> 8;
            }
            j += 4;
        }

        uart_tx(arg->cfg->com, frame_tx, MAX_SIZEOF_TX_VALUES);
    }
    delay_tx_msg++;
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
