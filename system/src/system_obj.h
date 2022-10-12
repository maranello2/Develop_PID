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
 ***************************************************************************************************

    @addtogroup SYSTEM_OBJ
    @{
    @defgroup SYSTEM_OBJ  SYSTEM object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __SYSTEM_OBJ_H
#define __SYSTEM_OBJ_H

/* Includes --------------------------------------------------------------------------------------*/
#include <def_common.h>
#include <heartbeat/heartbeat_api.h>
#include <hdwr/can_api.h>
#include "flight_controller/flight_controller_api.h"
#include <sevcon/sevcon_api.h>
#include <hdwr/uart_api.h>
#include <gps/gps_api.h>
#include <user/user_api.h>

/* Typedefs --------------------------------------------------------------------------------------*/
extern heartbeat_cfg_t heartbeat;
extern flight_controller_cfg_t flight_controller_cfg;
extern can_cfg_t can_cfg;
extern uart_cfg_t uart_cfg;
extern user_cfg_t user_cfg;

/* Public Function -------------------------------------------------------------------------------*/

#endif /* __SYSTEM_OBJ_H */

/**
 * @}
 */
/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
