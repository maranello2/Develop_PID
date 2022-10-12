/***************************************************************************************************
 * @file user_hdwr.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 31/03/2022
 * @date Last modification 31/03/2022 by jnieto
 * @brief USER
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @defgroup USER_HDWR  USER object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __USER_HDWR_H
#define __USER_HDWR_H

/* Includes --------------------------------------------------------------------------------------*/
#include <def_common.h>
#include "user/user_api.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief Init hadrware of user module
 *
 * @param obj \ref usert_t
 * @param cfg \ref user_cfg_t
 * @return ret_code_t
 */
ret_code_t user_hdwr_init(user_t *obj, user_cfg_t *cfg);

/**
 * @brief dequeue msg uart
 * 
 * @param obj 
 * @return void* 
 */
void *user_hdwr_get_msg (user_t *obj);

#endif /* __USER_HDWR_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
