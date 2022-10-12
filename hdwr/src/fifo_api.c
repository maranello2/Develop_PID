
/***************************************************************************************************
 * @file fifo_api.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 28/11/2021
 * @date Last modification 06/03/2021 by jnieto
 * @brief Cretated FIFOs with CMSIS
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup FIFO_API
    @{

*/

/* Includes --------------------------------------------------------------------------------------*/
#include "hdwr/fifo_api.h"

#include <string.h>
#include <cmsis_os2.h>

#include <stdio.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
fifo_t fifo_create_queue(fifo_cfg_t *cfg)
{
    if (!cfg)
    {
        return NULL;
    }

    return (osMessageQueueNew(cfg->num_msg, cfg->size_msg, NULL));
}

//--------------------------------------------------------------------------------------------------
ret_code_t fifo_enqueue_msg(fifo_t fifo, void *msg)
{
    ret_code_t ret = RET_PARAM_ERROR;

    if (!fifo || !msg)
    {
        return ret;
    }

    return ((osOK == osMessageQueuePut(fifo, msg, NULL, NULL)) ? RET_SUCCESS : RET_INT_ERROR);
}

//--------------------------------------------------------------------------------------------------
ret_code_t fifo_dequeue_msg(fifo_t fifo, void *msg)
{
    ret_code_t ret = RET_INT_ERROR;
    if (!fifo || !msg)
    {
        return ret;
    }
    ret = (osOK == osMessageQueueGet(fifo, msg, NULL, osWaitForever)) ? RET_SUCCESS : RET_INT_ERROR;
    return ret;
}

//--------------------------------------------------------------------------------------------------
uint32_t fifo_get_space(fifo_t fifo)
{

    if (!fifo)
    {
        return NULL;
    }

    return osMessageQueueGetSpace(fifo);
}

//--------------------------------------------------------------------------------------------------
ret_code_t fifo_reset(fifo_t fifo)
{

    if (!fifo)
    {
        return RET_PARAM_ERROR;
    }

    return (osOK == osMessageQueueReset(fifo)) ? RET_SUCCESS : RET_PARAM_ERROR;
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/