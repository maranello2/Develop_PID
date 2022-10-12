/***************************************************************************************************
 * @file flight_controller_hdwr.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 14/02/2022
 * @date Last modification 17/02/2022 by jnieto
 * @brief periodic
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @defgroup FLIGHT_CONTROLLER_HDWR  PERIODIC object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __FLIGHT_CONTROLLER_HDWR_H
#define __FLIGHT_CONTROLLER_HDWR_H

/* Includes --------------------------------------------------------------------------------------*/
#include <def_common.h>
#include "flight_controller/flight_controller_api.h"
#include <stdbool.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief init hardware for this modules, ADCs and DAC
 *
 * @param arg \ref flight_controller_t
 * @return ret_code_t \ref ret_code_t
 */
ret_code_t flight_controller_hdwr_init(flight_controller_t *arg);

/**
 * @brief check if change the ADCs
 *
 * @param arg \ref flight_controller_t
 * @return bool TRUE  = Do changes in the ADCs
 *              FALSE = Don´t changes in the ADCs
 */
bool flight_controller_hdwr_check_adc(flight_controller_t *arg);

/**
 * @brief Start DACs
 *
 * @param arg \ref flight_controller_t
 * @return \ref ret_code_t
 */
ret_code_t flight_controller_hdwr_start(flight_controller_t *arg);

/**
 * @brief Update value DAC
 *
 * @param arg \ref pwm_id_t
 * @param value_dac new valure from DAC
 * @return \ref ret_code_t
 */
ret_code_t flight_controller_hdwr_set_dac(pwm_id_t arg, uint16_t value_dac);

#endif /* __FLIGHT_CONTROLLER_HDWR_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
