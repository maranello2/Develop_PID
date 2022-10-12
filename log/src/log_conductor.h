/***************************************************************************************************
 * @file log_conductor.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 27/02/2022
 * @date Last modification 27/02/2022 by jnieto
 * @brief LOG
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @defgroup LOG_CONDUCTOR  LOG object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __LOG_CONDUCTOR_H
#define __LOG_CONDUCTOR_H

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
 * @brief Create LOG module
 * @return \ref ret_code_t
 *
 */
ret_code_t log_conductor_init(void);

/**
 * @brief Save log and wake up the thread
 *
 * @param name_task show name of the task like add new log
 * @param level_debug \ref log_level_debug_t
 * @param info show info he cause of the log
 * @return \ref ret_code_t
 */
ret_code_t log_conductor_new_msg(const char *name_task, log_level_debug_t level_debug, const char *info);

#endif /* __LOG_CONDUCTOR_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
