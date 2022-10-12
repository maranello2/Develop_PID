/***************************************************************************************************
 * @file uart_api.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 10/03/2022
 * @date Last modification 10/03/2022 by jnieto
 * @brief UART
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************
    @addtogroup UART
    @{
    @defgroup UART_API  UART object
    @{
    @brief
    @details
*/
/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef _UART_API_H
#define _UART_API_H

/* Includes --------------------------------------------------------------------------------------*/
#include <main.h>
#include <def_common.h>
#include <hdwr/fifo_api.h>

/* Defines ---------------------------------------------------------------------------------------*/
/** Maximum modules uart use the uart */
#define UART_MAX_MODULES_SUBSCRIBE 2

/* Typedefs --------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** uart bus config number uart */
typedef enum uart_number
{
    UART_1 = 1, /**< uart 1 of the microcontroller */
    UART_2,
    UART_3,
    UART_4,
    UART_5,
    UART_MAX /**< Maximum uart of the microcontroller */
} uart_number_t;

/*! uart configuration structure */
typedef struct uart_cfg_s
{
    uint16_t num_msg;               /*!< Numbers of message for FIFO */
    uart_number_t assignament_uart; /*!< Select uart \ref uart_number_t */
    void *handle;                   /*!< libary HAL */
} uart_cfg_t;

/* Private values --------------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * Creates a uart instance
 *
 * @param cfg uart configuration data
 * @return \ref ret_code_t
 */
ret_code_t uart_create(uart_cfg_t *cfg);

/*!
 * Register RX queue for a given uart instance
 *
 * @param uart_id \ref uart_number_t
 * @param queue_id OSAL queue id
 * @retval RET_SUCCESS if ok
 * @retval RET_INV_PARAMS if invalid uart or queue id
 * @retval RET_INT_ERROR if any other error
 */
ret_code_t uart_register_rx_queue(uart_number_t uart_id, fifo_t queue_id);

/**
 * @brief Register fifos queue when recived a message uart
 *
 * @param fifo_rx \ref fifo_t
 * @return \ref ret_code_t
 */
ret_code_t uart_suscribe_rx_fifo(fifo_t *fifo_rx, uint16_t size, uart_number_t uart);

/**
 * @brief Delete register fifos queue when recived a message uart
 *
 * @param fifo_rx \ref fifo_t
 * @return \ref ret_code_t
 */
ret_code_t uart_unsuscribe_rx_fifo(fifo_t *fifo_rx);

/**
 * @brief Send new message uart
 *
 * @return \ref ret_code_t
 */
ret_code_t uart_tx(uart_number_t uart, uint8_t *value_tx, uint16_t size);

#endif /* _uart_API_H */
       /**
        * @}
        */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/