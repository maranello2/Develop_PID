/***************************************************************************************************
 * @file log_driver.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 27/02/2022
 * @date Last modification 27/02/2022 by jnieto
 * @brief LOG functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup LOG_DRIVER
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "log_driver.h"
#include <log/log_api.h>
#include <log/log_config.h>

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "cmsis_os2.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** struct the message for Debug */
typedef struct log_msg_s
{
    uint32_t tick;
    char name_task[LOG_MAX_NAME_TASK];
    log_level_debug_t level_debug;
    char info[LOG_MAX_INFO_MSG];
} log_msg_t;

log_msg_t log_msg[LOG_MAX_MSG];
/** Index array log_msg */
uint16_t id_msg_rx = 0x00, id_msg_tx = 0x00;

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/
static const char *log_get_string_level(log_level_debug_t level_debug);

/* Private functions -----------------------------------------------------------------------------*/
static const char *log_get_string_level(log_level_debug_t level_debug)
{
    switch (level_debug)
    {
    case (LOG_DEBUG):
        return "DEBUG";
        break;
    case (LOG_INFO):
        return "INFO";
        break;
    case (LOG_WARNING):
        return "WARNING";
        break;
    case (LOG_ERROR):
        return "ERROR";
        break;
    default:
        return "UNKNOW";
        break;
    }
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t log_driver_create_new_message(const char *name_task, log_level_debug_t level_debug, const char *info)
{
    memcpy(&log_msg[id_msg_rx].name_task, name_task, sizeof(log_msg[id_msg_rx].name_task));
    memcpy(&log_msg[id_msg_rx].info, info, sizeof(log_msg[id_msg_rx].info));
    log_msg[id_msg_rx].level_debug = level_debug;
    // ticks
    log_msg[id_msg_rx].tick = osKernelGetTickCount();
    const char *level = log_get_string_level(log_msg[id_msg_rx].level_debug);

    // printf("%d [ %s ] %s: %s\n", log_msg[id_msg_rx].tick, log_msg[id_msg_rx].name_task, level, log_msg[id_msg_rx].info);

    id_msg_rx++;
    id_msg_rx = (id_msg_rx >= LOG_MAX_MSG) ? 0x00 : id_msg_rx;

    return RET_SUCCESS;
}
/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
