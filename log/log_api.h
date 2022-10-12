/***************************************************************************************************
 * @file log_api.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 27/02/2022
 * @date Last modification 27/02/2022 by jnieto
 * @brief LOG
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @addtogroup LOG
    @{
    @defgroup LOG_API  LOG object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __LOG_API_H
#define __LOG_API_H

/* Includes --------------------------------------------------------------------------------------*/
#include <def_common.h>
#include <stdint.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
typedef enum log_level_debug_e
{
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_MAX_LEVEL
} log_level_debug_t;

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief Init log module
 *
 * @return \ref ret_code_t
 */
ret_code_t log_init(void);

/**
 * @brief Log new message from other modules
 *
 * @param name_task show name of the task like add new log
 * @param level_debug \ref log_level_debug_t
 * @param info show info he cause of the log
 * @return \ref ret_code_t
 */
ret_code_t log_new_msg(const char *name_task, log_level_debug_t level_debug, const char *info);

/**
 * @brief  Función que transforma un int a una cadena de caracteres.
 * @param  i valor entero que se quiere convertir en ASCII.
 * @param  b[] puntero del array donde guardar el valor int en ASCII.
 */
char *itoa(int i, char b[]);

#endif /* __LOG_API_H */

/**
 * @}
 */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
