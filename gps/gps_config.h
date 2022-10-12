/***************************************************************************************************
 * @file gps_config.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 15/03/2022
 * @date Last modification 15/03/2022 by jnieto
 * @brief gps
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @defgroup GPS_CONFIG  gps object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __GPS_CONFIG_H
#define __GPS_CONFIG_H

/* Includes --------------------------------------------------------------------------------------*/

/* Defines ---------------------------------------------------------------------------------------*/
#define SIZEOF_MSG_GPS 20

#define POS_INS_VELNED_NORTH_AXIS (POS_HEADER_FIELDS_MSB + 0x01)
#define POS_INS_VELNED_EAST_AXIS (POS_INS_VELNED_NORTH_AXIS + 0x04)
#define POS_INS_VELNED_DOWN_AXIS (POS_INS_VELNED_EAST_AXIS + 0x04)

#endif /* __GPS_CONFIG_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
