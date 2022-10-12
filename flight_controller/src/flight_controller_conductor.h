/***************************************************************************************************
 * @file flight_controller_conductor.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 14/02/2022
 * @date Last modification 17/02/2022 by jnieto
 * @brief FLIGHT_CONTROLLER
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @defgroup FLIGHT_CONTROLLER_CONDUCTOR  FLIGHT_CONTROLLER object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __FLIGHT_CONTROLLER_CONDUCTOR_H
#define __FLIGHT_CONTROLLER_CONDUCTOR_H

/* Includes --------------------------------------------------------------------------------------*/
#include <def_common.h>
#include <flight_controller/flight_controller_api.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief Configure Thread and IA of flight controller
 *
 * @param cfg \ref flight_controller_cfg_t
 * @return ret_code_t \ref ret_code_t
 */
ret_code_t flight_controller_conductor_init(flight_controller_cfg_t *cfg);

/**
 * @brief weak up thread
 *
 * @param arg \ref flight_controller_t
 */
void flight_controller_conductor_resume_thread(flight_controller_t *arg);

#endif /* __FLIGHT_CONTROLLER_CONDUCTOR_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
