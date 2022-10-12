/***************************************************************************************************
 * @file gps_driver.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 15/03/2022
 * @date Last modification 15/03/2022 by jnieto
 * @brief gps
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @defgroup GPS_DRIVER  gps object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __GPS_DRIVER_H
#define __GPS_DRIVER_H

/* Includes --------------------------------------------------------------------------------------*/
#include <gps/gps_api.h>
#include <def_common.h>

/* Defines ---------------------------------------------------------------------------------------*/
#define HEADER_SYNC 0xFA
#define HEADER_SIZE 0x04
#define CRC_SIZE 0x02

#define POS_HEADER_SYNC 0x00
#define POS_HEADER_GROUP 0x01
#define POS_HEADER_FIELDS_LSB 0x02
#define POS_HEADER_FIELDS_MSB 0x03

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief Log init gps
 *
 * @param gps \ref gps_t
 * @return \ref ret_code_t
 */
ret_code_t gps_driver_log_init(gps_t *gps);

/**
 * @brief while 1
 *
 * @param arg \ref gps_t
 */
void gps_driver_get_msg(void *arg);

/**
 * @brief Return actual value of the GPS
 *
 * @param \ref gps_t arg
 * @return float
 */
float gps_driver_get_velocity_north_axis(gps_t *arg);
float gps_driver_get_velocity_east_axis(gps_t *arg);
float gps_driver_get_velocity_down_axis(gps_t *arg);

#endif /* __GPS_DRIVER_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
