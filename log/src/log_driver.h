/***************************************************************************************************
 * @file log_driver.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 27/02/2022
 * @date Last modification 27/02/2022 by jnieto
 * @brief LOG
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @defgroup LOG_DRIVER  LOG object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __LOG_DRIVER_H
#define __LOG_DRIVER_H

/* Includes --------------------------------------------------------------------------------------*/
#include <def_common.h>
#include <log/log_api.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief Add new msg to log modules
 *
 * @param name_task name of task add new message
 * @param level_debug \ref log_level_debug_t
 * @param info message
 * @return \ref ret_code_t
 */
ret_code_t log_driver_create_new_message(const char *name_task, log_level_debug_t level_debug, const char *info);

#endif /* __LOG_DRIVER_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
