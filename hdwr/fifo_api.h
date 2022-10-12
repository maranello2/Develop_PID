/***************************************************************************************************
 * @file fifo_api.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 28/11/2021
 * @date Last modification 07/03/2021 by jnieto
 * @brief Cretated FIFOs with CMSIS
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************
    @addtogroup FIFO
    @{
    @defgroup FIFO_API  FIFO object
    @{
    @brief
    @details
*/
/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __FIFO_API_H
#define __FIFO_API_H

/* Includes --------------------------------------------------------------------------------------*/
#include "cmsis_os2.h"
#include <def_common.h>
#include <stdint.h>

/* Defines ---------------------------------------------------------------------------------------*/
#define fifo_t osMessageQueueId_t

/* Typedefs --------------------------------------------------------------------------------------*/
/** Struct of FIFO configurated */
typedef struct fifo_cfg_s
{
    uint32_t num_msg;  /**< Maximum number of messager for queue */
    uint32_t size_msg; /**< Sizeof every message */
} fifo_cfg_t;

/* Private values --------------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief Create new FIFO
 *
 * @return fifo_t \ref osMessageQueueId_t
 */
fifo_t fifo_create_queue(fifo_cfg_t *cfg);

/**
 * @brief Enqueue new message to FIFO
 *
 * @param fifo \ref osMessageQueueId_t
 * @param msg pointer of new message
 * @return \ref ret_code_t
 */
ret_code_t fifo_enqueue_msg(fifo_t fifo, void *msg);

/**
 * @brief  Dequeue message from FIFO
 *
 * @param fifo \ref osMessageQueueId_t
 * @param msg pointer of new message
 * @return \ref ret_code_t
 */
ret_code_t fifo_dequeue_msg(fifo_t fifo, void *msg);

/**
 * @brief Get number of available slots for messages
 *
 * @param fifo \ref osMessageQueueId_t
 * @return uint32_t number of available slots for messages
 */
uint32_t fifo_get_space(fifo_t fifo);

/**
 * @brief Reset FIFO
 *
 * @param fifo \ref osMessageQueueId_t
 * @return ret_code_t \ref ret_code_t
 */
ret_code_t fifo_reset(fifo_t fifo);

#endif /* __FIFO_API_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/