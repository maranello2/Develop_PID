/***************************************************************************************************
 * @file gps_hdwr.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 15/03/2022
 * @date Last modification 15/03/2022 by jnieto
 * @brief gps
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @defgroup GPS_HDWR  gps object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __GPS_HDWR_H
#define __GPS_HDWR_H

/* Includes --------------------------------------------------------------------------------------*/
#include <gps/gps_api.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief init hadware gps
 *
 * @param cfg \ref gps_cfg_t
 * @param data \ref gps_t
 * @return \ref ret_code_t
 */
ret_code_t gps_hdwr_init(gps_cfg_t *cfg, gps_t *data);

/**
 * @brief get message from fifo modules
 *
 * @param gps \ref gps_t
 * @return void* \ref can_msg_t
 */
void *gps_hdwr_get_msg(gps_t *gps);

#endif /* __GPS_HDWR_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
