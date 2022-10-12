/***************************************************************************************************
 * @file heartbeat_api.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 11/11/2021
 * @date Last modification 06/02/2022 by jnieto
 * @brief HeartBeat
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @addtogroup HEARTBEAT
    @{
    @defgroup HEARTBEAT_API  HEARTBEAT object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __HEARTBEAT_API_H
#define __HEARTBEAT_API_H

/* Includes --------------------------------------------------------------------------------------*/
#include <stdint.h>
#include <def_common.h>
#include "hdwr/gpio_api.h"

/* Typedefs --------------------------------------------------------------------------------------*/
/** Object of configuration of heartbeat */
typedef struct
{
    gpio_out_t gpio;   /**< Fixed the GPIO of LED */
    uint32_t delay_ms; /**< Time of delay for toggle led, in ms */
    const char *name;  /**< name of thread */
} heartbeat_cfg_t;

/* Public Function -------------------------------------------------------------------------------*/
/**
 * @brief Public function for configure the heartbeat thread
 *
 * @param cfg \ref heartbeat_cfg_t
 * @return \ref ret_code_t
 */
ret_code_t heartbeat_init(heartbeat_cfg_t *cfg);

#endif /* __HEARTBEAT_API_H */

/**
 * @}
 */
/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
