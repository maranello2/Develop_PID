
/***************************************************************************************************
 * @file uart_api.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 10/03/2022
 * @date Last modification 03/04/2022 by jnieto
 * @brief UART
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup UART_API
    @{

*/

/* Includes --------------------------------------------------------------------------------------*/
#include "hdwr\uart_api.h"

#include <log\log_api.h>
#include <def_common.h>
#include <stm32l5xx_hal_uart.h>
#include <stdio.h>
#include <cmsis_os2.h>
#include <stdbool.h>

/* Defines ---------------------------------------------------------------------------------------*/
extern UART_HandleTypeDef hlpuart1;
;
extern UART_HandleTypeDef huart3;

/** Size FIFO RX */
#define SIZEOF_UART_RX 20

/* Private values --------------------------------------------------------------------------------*/

/** Name for fifo queue */
char name_fifo_uart[10] = "UART_FIFO_";

/** Name for thread */
char name_thread_uart[6] = "UART_";

/** ID of thread */
static osThreadId_t id_thread;

/** Definitions for defaultTask */
osThreadAttr_t uart_task_attributes =
    {
        .priority = (osPriority_t)osPriorityNormal,
        .stack_size = 512,
};

typedef struct
{
    fifo_t uart_fifo_subscribe; /** FIFO RX subscribe to UART */
    uint16_t uart_fifo_size;    /** FIFO RX size to UART */
    UART_HandleTypeDef *handle; /** Handle uart */
} uart_subscribe_t;

uart_subscribe_t uart_subscribe[UART_MAX_MODULES_SUBSCRIBE];

/** FIFO RX */
uint8_t uart_rx[SIZEOF_UART_RX] = {0};

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Run Thread
 *
 * @param aguments \ref spi_t
 */
void uart_task(void *aguments);

UART_HandleTypeDef *get_handle(uart_number_t uart);

/* Private functions -----------------------------------------------------------------------------*/
void uart_task(void *aguments)
{
    // uart_cfg_t *uart = (uart_cfg_t *)aguments;

    osThreadFlagsWait(NULL, osFlagsWaitAny, osWaitForever);
}

//--------------------------------------------------------------------------------------------------
UART_HandleTypeDef *get_handle(uart_number_t uart)
{
    UART_HandleTypeDef *handle = NULL;
    if (uart == UART_1)
    {
        handle = &hlpuart1;
    }
    else if (uart == UART_3)
    {
        handle = &huart3;
    }

    return handle;
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t uart_create(uart_cfg_t *cfg)
{
    ret_code_t ret = RET_INT_ERROR;

    if (!cfg || cfg->assignament_uart >= UART_MAX || cfg->num_msg == NULL)
    {
        return ret;
    }

    cfg->handle = get_handle(cfg->assignament_uart);
    if (!cfg->handle)
    {
        return ret;
    }

    name_thread_uart[5] = '0' + cfg->assignament_uart;
    uart_task_attributes.name = name_thread_uart;
    id_thread = osThreadNew(uart_task, cfg, &uart_task_attributes);

    char msg[20];
    if (id_thread) // HAL_OK == ret_hal)
    {
        return (log_new_msg(uart_task_attributes.name, LOG_DEBUG, msg));
    }

    log_new_msg(uart_task_attributes.name, LOG_DEBUG, msg);

    return ret;
}

//--------------------------------------------------------------------------------------------------
ret_code_t uart_suscribe_rx_fifo(fifo_t *fifo_rx, uint16_t size, uart_number_t uart)
{
    ret_code_t ret = RET_PARAM_ERROR;

    for (uint8_t i = 0x00; i < UART_MAX_MODULES_SUBSCRIBE; i++)
    {
        if (!uart_subscribe[i].uart_fifo_subscribe)
        {
            uart_subscribe[i].uart_fifo_subscribe = fifo_rx;
            uart_subscribe[i].uart_fifo_size = size;
            uart_subscribe[i].handle = get_handle(uart);
            ret = RET_SUCCESS;

            if (uart_subscribe[i].handle)
            {
                HAL_UART_Receive_IT(uart_subscribe[i].handle, uart_rx, size);
            }
            i = UART_MAX_MODULES_SUBSCRIBE + 1;
        }
    }

    return ret;
}

//--------------------------------------------------------------------------------------------------
ret_code_t uart_unsuscribe_rx_fifo(fifo_t *fifo_rx)
{
    ret_code_t ret = RET_PARAM_ERROR;

    for (uint8_t i = 0x00; i < UART_MAX_MODULES_SUBSCRIBE; i++)
    {
        if (uart_subscribe[i].uart_fifo_subscribe == fifo_rx)
        {
            uart_subscribe[i].uart_fifo_subscribe = NULL;
            uart_subscribe[i].uart_fifo_size = NULL;
            uart_subscribe[i].handle = NULL;
            ret = RET_SUCCESS;
            i = UART_MAX_MODULES_SUBSCRIBE + 1;
        }
    }

    return ret;
}

//--------------------------------------------------------------------------------------------------
ret_code_t uart_tx(uart_number_t uart, uint8_t *value_tx, uint16_t size)
{
    ret_code_t ret = RET_INT_ERROR;

    if (!value_tx || uart >= UART_MAX)
    {
        return ret;
    }

    ret = (HAL_OK == HAL_UART_Transmit(get_handle(uart), value_tx, size, UINT16_MAX)) ? RET_SUCCESS : RET_INT_ERROR;

    return ret;
}

//* ISR --------------------------------------------------------------------------------------------
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    for (uint8_t i = 0x00; i < UART_MAX_MODULES_SUBSCRIBE; i++)
    {
        if (uart_subscribe[i].uart_fifo_subscribe && uart_subscribe[i].handle == UartHandle)
        {
            fifo_enqueue_msg(uart_subscribe[i].uart_fifo_subscribe, &uart_rx);
            HAL_UART_Receive_IT(uart_subscribe[i].handle, uart_rx,
                                uart_subscribe[i].uart_fifo_size);
        }
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    /* Set transmission flag: transfer complete */
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/