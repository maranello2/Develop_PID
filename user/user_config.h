/***************************************************************************************************
 * @file user_config.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 31/03/2022
 * @date Last modification 31/03/2022 by jnieto
 * @brief USER
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @defgroup USER_CONFIG  USER config module
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclUSERion ---------------------------------------------------------*/
#ifndef __USER_CONFIG_H
#define __USER_CONFIG_H

/* Includes --------------------------------------------------------------------------------------*/

/* Defines ---------------------------------------------------------------------------------------*/
// HEADER
#define USER_HEADER 0x1A
#define USER_SIZE_HEADER 1
// END
#define USER_SIZE_END_PAYLOAD 1

// PAYLOAD
#define USER_NUMBER_PAYLOAD 1
#define USER_SIZE_PAYLOAD 5 // ID (1 BYTE) + PAYLOAD (4 BYTES)

typedef enum
{
    USER_ID_RATIO_FRONT_AXLE,
    USER_ID_RATIO_REAR_AXLE,
    USER_ID_MAX_FRONT_SLIP,
    USER_ID_MAX_REAR_SLIP,
    USER_ID_P_REAR,
    USER_ID_I_REAR,
    USER_ID_D_REAR,
    USER_ID_P_FRONT,
    USER_ID_I_FRONT,
    USER_ID_D_FRONT,
    USER_ID_INHIBITION_SYSTEM
} user_ids_t;

#endif /* __USER_CONFIG_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
