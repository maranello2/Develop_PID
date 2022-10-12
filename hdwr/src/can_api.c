
/***************************************************************************************************
 * @file can_api.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 05/03/2022
 * @date Last modification 06/03/2022 by jnieto
 * @brief CAN
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup CAN_API
    @{

       * Clock's CAN is 110 MHz
       * source: https://phryniszak.github.io/stm32g-fdcan/
*/

/* Includes --------------------------------------------------------------------------------------*/
#include "hdwr/can_api.h"
#include <stm32l5xx_hal_fdcan.h>

#include <def_common.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <def_common.h>
#include <log/log_api.h>
#include <hdwr/fifo_api.h>

/* Defines ---------------------------------------------------------------------------------------*/
/** Offset to indicate data length \ref FDCAN_data_length_code */
#define OFFSET_BITS_DLC 16

/* Private values --------------------------------------------------------------------------------*/
/** struct external of HAL libarires */
extern FDCAN_HandleTypeDef hfdcan1;

/** Name for fifo queue */
char name_fifo_can[10] = "CAN_FIFO_";

/** Name for thread */
char name_thread_can[5] = "CAN_";

/** ID of thread */
static osThreadId_t id_thread;

/** Definitions for defaultTask */
osThreadAttr_t can_task_attributes =
    {
        .priority = (osPriority_t)osPriorityNormal,
        .stack_size = 512,
};

/** FIFO RX subscribe to CAN */
fifo_t can_fifo_subscribe[CAN_MAX_MODULES_SUBSCRIBE];

/** Structure for CAN Open */
typedef struct msg_canopen_s
{
    union
    {
        uint32_t all;
        struct
        {
            uint32_t mode_access : 8;     /* Access Mode (OD_READ or OD_WRITE)*/
            uint32_t index : 8;           /* Index */
            uint32_t index_highlevel : 8; /* Index high level */
            uint32_t subindex : 8;        /* Subindex */
        } byte;
    } idx_canopen;
    union
    {
        uint32_t all;
        struct
        {
            uint32_t data_1 : 8;
            uint32_t data_2 : 8;
            uint32_t data_3 : 8;
            uint32_t data_4 : 8;
        } byte;
    } data;
} msg_canopen_t;

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Run Thread
 *
 * @param aguments \ref spi_t
 */
void can_task(void *aguments);

/**
 * @brief Enqueue new message CAN recived by CAN
 *
 */
void can_enqueue_new_message(void *handle, uint32_t fifo_can);

/* Private functions -----------------------------------------------------------------------------*/
void can_task(void *aguments)
{
    //can_cfg_t *can = (can_cfg_t *)aguments;

    osThreadFlagsWait(NULL, osFlagsWaitAny, osWaitForever);
}

//--------------------------------------------------------------------------------------------------
void can_enqueue_new_message(void *handle, uint32_t fifo_can)
{
    can_msg_t msg;
    FDCAN_RxHeaderTypeDef pRxHeader;
    uint8_t data[MAX_CAN_MSG_LENGTH];

    if (HAL_OK == HAL_FDCAN_GetRxMessage(handle, fifo_can, &pRxHeader, data))
    {
        msg.id_frame = pRxHeader.Identifier;
        msg.length = pRxHeader.DataLength >> OFFSET_BITS_DLC;
        for (uint16_t i = 0x00; i < msg.length; i++)
        {
            msg.data[i] = data[i];
        }

        for (uint8_t i = 0x00; i < CAN_MAX_MODULES_SUBSCRIBE; i++)
        {
            if (can_fifo_subscribe[i])
            {
                fifo_enqueue_msg(can_fifo_subscribe[i], &msg);
            }
        }
    }
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t can_create(can_cfg_t *cfg)
{
    ret_code_t ret = RET_INT_ERROR;

    if (!cfg || cfg->assignament_can >= CAN_MAX || cfg->num_msg == NULL)
    {
        return ret;
    }

    if (cfg->assignament_can == CAN_1)
    {
        cfg->handle = &hfdcan1;
    }
    else
    {
        return ret;
    }

    name_thread_can[4] = '0' + cfg->assignament_can;
    can_task_attributes.name = name_thread_can;
    id_thread = osThreadNew(can_task, cfg, &can_task_attributes);

    if (id_thread)
    {
      /* Start the FDCAN module */
      HAL_StatusTypeDef ret_hal = HAL_FDCAN_Start(cfg->handle);
      ret = (HAL_OK == ret_hal) ? RET_SUCCESS : RET_INT_ERROR;

      char msg[20];
      if (HAL_OK == ret_hal)
      {
          /** Activate ISR FIFO 0 and FIFO 1 */
          HAL_FDCAN_ActivateNotification(cfg->handle, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
          HAL_FDCAN_ActivateNotification(cfg->handle, FDCAN_IT_RX_FIFO0_MESSAGE_LOST, 0);
          HAL_FDCAN_ActivateNotification(cfg->handle, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0);
          HAL_FDCAN_ActivateNotification(cfg->handle, FDCAN_IT_RX_FIFO1_MESSAGE_LOST, 0);

          sprintf(msg, "CREATED CAN %d", cfg->assignament_can);

          return (log_new_msg(can_task_attributes.name, LOG_DEBUG, msg));
      }

      sprintf(msg, "FAIL CREATED CAN %d", cfg->assignament_can);
      log_new_msg(can_task_attributes.name, LOG_DEBUG, msg);
    }
    return ret;
}

//--------------------------------------------------------------------------------------------------
ret_code_t can_tx(can_number_t can_id, can_msg_t *msg)
{
    ret_code_t ret = RET_INT_ERROR;

    if (can_id >= CAN_MAX)
    {
        return ret;
    }

    uint32_t mailbox = 0; // required by the current HAL
    FDCAN_TxHeaderTypeDef tx_msg;
    FDCAN_HandleTypeDef *handle;

    if (can_id == CAN_1)
    {
        handle = &hfdcan1;
        // tx_msg.Identifier = hfdca
    }
    tx_msg.Identifier = msg->id_frame;
    tx_msg.IdType = CAN_TYPE_STD;
    tx_msg.TxFrameType = FDCAN_DATA_FRAME;
    tx_msg.DataLength = msg->length << OFFSET_BITS_DLC;
    tx_msg.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    tx_msg.BitRateSwitch = FDCAN_BRS_OFF;
    tx_msg.BitRateSwitch = FDCAN_BRS_OFF;
    tx_msg.FDFormat = FDCAN_CLASSIC_CAN;
    tx_msg.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    tx_msg.MessageMarker = 0;

    ret = (HAL_OK == HAL_FDCAN_AddMessageToTxFifoQ(handle, &tx_msg, msg->data)) ? RET_SUCCESS : RET_INT_ERROR;

    while (HAL_FDCAN_IsTxBufferMessagePending(handle, mailbox))
        ;

    return ret;
}

//--------------------------------------------------------------------------------------------------
ret_code_t can_suscribe_rx_fifo(fifo_t *fifo_rx)
{
    ret_code_t ret = RET_PARAM_ERROR;

    for (uint8_t i = 0x00; i < CAN_MAX_MODULES_SUBSCRIBE; i++)
    {
        if (!can_fifo_subscribe[i])
        {
            can_fifo_subscribe[i] = fifo_rx;
            ret = RET_SUCCESS;
            i = CAN_MAX_MODULES_SUBSCRIBE + 1;
        }
    }

    return ret;
}

//--------------------------------------------------------------------------------------------------
ret_code_t can_unsuscribe_rx_fifo(fifo_t *fifo_rx)
{
    ret_code_t ret = RET_PARAM_ERROR;

    for (uint8_t i = 0x00; i < CAN_MAX_MODULES_SUBSCRIBE; i++)
    {
        if (can_fifo_subscribe[i] == fifo_rx)
        {
            can_fifo_subscribe[i] = NULL;
            ret = RET_SUCCESS;
            i = CAN_MAX_MODULES_SUBSCRIBE + 1;
        }
    }

    return ret;
}

/* CANOPEN ---------------------------------------------------------------------------------------*/
uint16_t canopen_get_mode_access(can_msg_t *msg_can)
{
    msg_canopen_t *msg_canopen;
    if (!msg_can)
    {
        return OD_ERROR;
    }

    msg_canopen = (msg_canopen_t *)msg_can->data;

    return msg_canopen->idx_canopen.byte.mode_access;
}

//--------------------------------------------------------------------------------------------------
uint16_t canopen_get_index(can_msg_t *msg_can)
{
    if (!msg_can)
    {
        return UINT16_MAX;
    }

    msg_canopen_t *msg_canopen = (msg_canopen_t *)msg_can->data;

    return (((uint16_t)msg_canopen->idx_canopen.byte.index_highlevel << 8) + (uint16_t)msg_canopen->idx_canopen.byte.index);
}

//--------------------------------------------------------------------------------------------------
uint16_t canopen_get_subindex(can_msg_t *msg_can)
{
    if (!msg_can)
    {
        return UINT16_MAX;
    }

    msg_canopen_t *msg_canopen = (msg_canopen_t *)msg_can->data;

    return msg_canopen->idx_canopen.byte.subindex;
}

//--------------------------------------------------------------------------------------------------
uint32_t canopen_get_data(can_msg_t *msg_can)
{

    uint32_t ret = NULL;

    if (!msg_can)
    {
        return ret;
    }

    msg_canopen_t *msg_canopen = (msg_canopen_t *)msg_can->data;

    switch (msg_canopen->idx_canopen.byte.mode_access)
    {
    case OD_READ:
    case OD_WRITE:
    case OD_READ_4BYTES:
    {
        ret = 0x000000FF & (uint32_t)(msg_canopen->data.byte.data_1);
        ret = 0x0000FFFF & (((uint32_t)(msg_canopen->data.byte.data_2) << 8) + ret);
        ret = 0x00FFFFFF & (((uint32_t)(msg_canopen->data.byte.data_3) << 16) + ret);
        ret = 0xFFFFFFFF & (((uint32_t)(msg_canopen->data.byte.data_4) << 24) + ret);
        break;
    } // END case 4 Bytes

    case OD_READ_2BYTES:
    case OD_WRITE_2BYTES:
    {
        ret = 0x000000FF & (uint32_t)(msg_canopen->data.byte.data_1);
        ret = 0x0000FFFF & (((uint32_t)(msg_canopen->data.byte.data_2) << 8) + ret);
        break;
    } // END case 2 Bytes

    case OD_READ_1BYTES:
    case OD_WRITE_1BYTES:
    {
        ret = 0x000000FF & (uint32_t)(msg_canopen->data.byte.data_1);
        break;
    } // END case 1 Bytes

    default:
        ret = 0xFFFFFFFF;
    } // END switch

    return ret;
}

/* ISR -------------------------------------------------------------------------------------------*/
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    can_enqueue_new_message(hfdcan, FDCAN_RX_FIFO0);
}

//--------------------------------------------------------------------------------------------------
void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{

    can_enqueue_new_message(hfdcan, FDCAN_RX_FIFO1);
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/