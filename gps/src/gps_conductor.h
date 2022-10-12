/***************************************************************************************************
 * @file gps_conductor.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 15/03/2022
 * @date Last modification 15/03/2022 by jnieto
 * @brief gps
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @defgroup GPS_CONDUCTOR  gps object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __GPS_CONDUCTOR_H
#define __GPS_CONDUCTOR_H

/* Includes --------------------------------------------------------------------------------------*/
#include <def_common.h>
#include <gps/gps_api.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief Init high level of gps
 *
 * @param cfg \ref gps_cfg_t
 * @return \ref gps_id_t
 */
gps_id_t gps_conductor_init(gps_cfg_t *cfg);

/**
 * @brief Getter instace
 *
 * @return \ref gps_t
 */
gps_t *gps_getter_instace(void);

/**
 * @brief
 *
 * @param id
 * @param cllbck
 * @param arg
 * @param type_subscribe_gps
 * @return ret_code_t
 */
ret_code_t gps_conductor_subscribe(gps_id_t id, gps_cllbck cllbck, void *arg, type_subscribe_gps_t type_subscribe_gps);

/**
 * @brief
 *
 * @param type_subscribe_gps
 */
void gps_conductor_notify_new_data(type_subscribe_gps_t type_subscribe_gps);

#endif /* __GPS_CONDUCTOR_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
