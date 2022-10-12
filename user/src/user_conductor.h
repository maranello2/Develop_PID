/***************************************************************************************************
 * @file user_conductor.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 31/03/2022
 * @date Last modification 02/04/2022 by jnieto
 * @brief USER
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @defgroup USER_CONDUCTOR  USER object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __USER_CONDUCTOR_H
#define __USER_CONDUCTOR_H

/* Includes --------------------------------------------------------------------------------------*/
#include <def_common.h>
#include <user/user_api.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief Create LOG module
 * @return \ref ret_code_t
 *
 */
ret_code_t user_conductor_init(user_cfg_t *cfg);

user_t *user_conductor_getter_get_obj (void);

#endif /* __USER_CONDUCTOR_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
