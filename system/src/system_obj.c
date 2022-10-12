/***************************************************************************************************
 * @file system_obj.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 24/11/2021
 * @date Last modification 11/04/2021 by jnieto
 * @brief Define all objets of the system Kart
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup SYSTEM_OBJ
    @{

*/

/* Includes --------------------------------------------------------------------------------------*/
#include "system_obj.h"
#include <heartbeat/heartbeat_api.h>
//#include "flight_controller/flight_controller_api.h"
#include <hdwr/adc_api.h>
#include <hdwr/can_api.h>
#include <periodic/periodic_api.h>
#include <sevcon/sevcon_api.h>
#include <hdwr/uart_api.h>
#include <gps/gps_api.h>
#include <user/user_api.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/
/** Struct of the HeartBeat */
heartbeat_cfg_t heartbeat =
    {
        .delay_ms = PERIODIC_EVERY_1_SG, // 1 sg
        .gpio = LED_GREEN,
        .name = "HEARTBEAT",
};

/** Struct of the flight controller */
flight_controller_cfg_t flight_controller_cfg =
    {
        .name = "FLIGHT_CONTROLLER",
        .adc_channel =
            {
                [0] = ADC_A0,
                [1] = ADC_A1,
                [2] = ADC_A2,
                [3] = ADC_A3,
            },
        .periodic_timer = PERIODIC_EVERY_200_MS,
        .dac_cfg =
            {
                [0] = {
                    .frequency = 10000, // 10KHz
                    .duty = 80,         // 0%
                    .pwm = PWM_3,
                    .channel = PWM_CHANNEL_2,

                },
                [1] = {
                    .frequency = 10000, // 10KHz
                    .duty = 80,         // 0%
                    .pwm = PWM_3,
                    .channel = PWM_CHANNEL_3,

                },
                [2] = {
                    .frequency = 10000, // 10KHz
                    .duty = 80,         // 0%
                    .pwm = PWM_3,
                    .channel = PWM_CHANNEL_4,

                },
                [3] = {
                    .frequency = 10000, // 10KHz
                    .duty = 80,         // 0%
                    .pwm = PWM_3,
                    .channel = PWM_CHANNEL_1,

                },

            },
        .gps_cfg = {.fifo_cfg = {
                        .num_msg = 2,
                    },
                    .uart_number = UART_3,
                    .output_fields = {
                        .ins.bit.vel_ned = 1,
                    }},
        .sevcon_cfg = {.fifo_cfg = {
                           .num_msg = 20,
                       }},
        .com = UART_1,
        .type_subscribe_gps = GROUP_INS};

/** Struct of the CAN BUS */
can_cfg_t can_cfg =
    {
        .num_msg = 16,
        .assignament_can = CAN_1,
        .type = CAN_TYPE_STD,
        .filter = NULL,
};

/** Struct of USART3 */
uart_cfg_t uart_cfg =
    {
        .assignament_uart = UART_3,
        .num_msg = 1,
};

/** Struct of USER */
user_cfg_t user_cfg =
    {
        .uart_number = UART_1,
        .fifo_cfg = {
            .num_msg = 3},
};

/** Struct of the DAC */

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
