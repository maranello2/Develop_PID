/***************************************************************************************************
 * @file flight_controller_driver.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 14/02/2022
 * @date Last modification 17/02/2022 by jnieto
 * @brief FLIGHT_CONTROLLER
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @defgroup FLIGHT_CONTROLLER_DRIVER  FLIGHT_CONTROLLER object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __FLIGHT_CONTROLLER_DRIVER_H
#define __FLIGHT_CONTROLLER_DRIVER_H

/* Includes --------------------------------------------------------------------------------------*/
#include <def_common.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief Init data of flight controller
 *
 * @param arg \ref flight_controller_t
 * @return \ref ret_code_t
 */
ret_code_t flight_controller_driver_init(flight_controller_t *arg);

/**
 * @brief Start periodic function
 *
 * @param arg \ref flight_controller_t
 * @return \ref ret_code_t
 */
ret_code_t flight_controller_driver_start_periodic(flight_controller_t *arg);

/**
 * @brief Stop periodic function
 *
 * @param arg \ref flight_controller_t
 * @return \ref ret_code_t
 */
ret_code_t flight_controller_driver_stop_periodic(flight_controller_t *arg);

/**
 * @brief LOG create module
 *
 * @param arg \ref flight_controller_t
 * @return \ref ret_code_t
 */
ret_code_t flight_controller_driver_log_init(flight_controller_t *arg);

/**
 * @brief Calcualte new PWM
 *
 * @param arg \ref flight_controller_t
 */
void flight_controller_driver_update_dac(flight_controller_t *arg);

void flight_controller_driver_decrease(uint16_t id, uint16_t value);

void flight_controller_driver_increase(uint16_t id, uint16_t value);

void flight_controller_driver_loop_send_values(flight_controller_t *arg);

#endif /* __FLIGHT_CONTROLLER_DRIVER_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
