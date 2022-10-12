/***************************************************************************************************
 * @file can_api.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 05/03/2022
 * @date Last modification 06/03/2022 by jnieto
 * @brief CAN
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************
    @addtogroup CAN
    @{
    @defgroup CAN_API  CAN object
    @{
    @brief
    @details
*/
/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef _CAN_API_H
#define _CAN_API_H

/* Includes --------------------------------------------------------------------------------------*/
#include <main.h>
#include <def_common.h>
#include <hdwr/fifo_api.h>

/* Defines ---------------------------------------------------------------------------------------*/
/** Maximum length of the data of a CAN message */
#define MAX_CAN_MSG_LENGTH 8

/** Maximum modules can use the can */
#define CAN_MAX_MODULES_SUBSCRIBE 1

/** MOVE TO CANOPEN LIBRARY */
/* Parametros de comunicacion del BUS CAN   */
/** Direcciones del campo CAN-ID del protocolo CANpen */
#define EMCY_ID 0x80
#define TPDO1 0x180
#define RPDO1 0x200
#define TPDO2 0x280
#define RPDO2 0x300
#define TPDO3 0x480
#define RPDO3 0x400
#define TPDO4 0x580
#define RPDO4 0x500
#define TSDO 0x580
#define RSDO 0x600
#define MNT 0x700

/** Modo de acceso a una entrada del diccionario de objetos, READ*/
#define OD_READ 0x40
#define OD_READ_4BYTES 0x43
#define OD_READ_2BYTES 0x4B
#define OD_READ_1BYTES 0x4F

/** Modo de acceso a una entrada del diccionario de objetos, WRITE*/
#define OD_WRITE 0x20
#define OD_WRITE_4BYTES 0x23
#define OD_WRITE_2BYTES 0x2B
#define OD_WRITE_1BYTES 0x2F

#define OD_ERROR 0x80
#define OD_ANSWER 0x60

/** Struct of dictionary */
typedef struct dictionary_canopen_s
{
    uint16_t mode_access; /** Mode de access READ o WRITE */
    uint16_t index;       /** Index of dictionary */
    uint16_t subindex;    /** Subindex of dictionary */
} dictionary_canopen_t;

/* Typedefs --------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** CAN bus config number CAN */
typedef enum CAN_NUMBER
{
    CAN_1 = 1, /**< CAN 1 of the microcontroller */
    CAN_MAX    /**< Maximum CAN of the microcontroller */
} can_number_t;

/** CAN bus config number CAN */
typedef enum CAN_FIFO_HAL
{
    CAN_FIFO_0 = 0, /**< FIFO CAN 1 of the microcontroller */
    CAN_FIFO_1,     /**< FIFO CAN 2 of the microcontroller */
    CAN_FIFO_MAX
} can_fifo_hal_t;

/*! CAN Id (standard/extended) required by the communication protocol */
typedef enum CAN_ID_TYPE
{
    CAN_TYPE_STD = 0x00000000U, /*!< Select ID Standard, in driver's HAL is 0 */
    CAN_TYPE_EXT = 0x40000000U  /*!< Select ID Extended, in driver's HAL is 4 */
} can_id_type_t;

/** Enum for select the filter mode.
 id_mode for filter (list or mask)_(sizeof in bits)_(number fifo CAN).
 source : Reference Manual by ST (en.CD00171190.pdf). Figure 231.
*/
typedef enum MODE_FILTER
{
    ID_LIST_32_FIFO0,             /**< Filter by list with ID extend, in the fifo 0 */
    ID_MASK_32_FIFO0,             /**< Filter by mask with ID extend, in the fifo 0 */
    ID_MASK_16_FIFO1,             /**< Filter by mask with ID standard, in the fifo 1 */
    ID_LIST_16_FIFO0,             /**< Filter by list with ID standard, in the fifo 0 */
    ID_LIST_32_FIFO1,             /**< Filter by list with ID extend, in the fifo 1 */
    ID_LIST_32_FIFO0_DEACTIVATED, /**< Not used */
    ID_MASK_16_FIFO0,             /**< Filter by mask with ID standard, in the fifo 0 */
    ID_MASK_16_FIFO1_DEACTIVATED, /**< Not used */
    ID_MASK_16_FIFO1_EXT,         /**< Filter by mask with ID standard, in the fifo 1 */
    ID_LIST_32_FIFO0_EXT,         /**< Filter by list with ID extend, in the fifo 0 */
    ID_LIST_16_FIFO1_DEACTIVATED, /**< Not used */
    ID_LIST_32_FIFO1_EXT,         /**< Filter by list with ID extend, in the fifo 1 */
    ID_MASK_32_FIFO1,             /**< Filter by mask with ID extend, in the fifo 1 */
    ID_MASK_32_FIFO0_EXT,         /**< Filter by mask with ID extend, in the fifo 0 */
} mode_filter_t;

/** CAN select Bit Rate */
typedef enum CAN_BITRATE
{
    BITRATE_10_KBITS_S,  /**< Bitrate CAN to 10 Kbits/s */
    BITRATE_20_KBITS_S,  /**< Bitrate CAN to 20 Kbits/s */
    BITRATE_50_KBITS_S,  /**< Bitrate CAN to 50 Kbits/s */
    BITRATE_125_KBITS_S, /**< Bitrate CAN to 125 Kbits/s */
    BITRATE_250_KBITS_S, /**< Bitrate CAN to 250 Kbits/s */
    BITRATE_500_KBITS_S, /**< Bitrate CAN to 500 Kbits/s */
    BITRATE_800_KBITS_S, /**< Bitrate CAN to 800 Kbits/s - NOT USED - */
    BITRATE_1_MBITS_S,   /**< Bitrate CAN to 1 Mbits/s */
    MAX_BITRATE          /**< Maximum Bitrates */
} can_bitrate_t;

/** Struct to config the can filters */
typedef struct
{
    uint32_t filter;           /**< CAN filter */
    uint32_t mask;             /**< CAN mask */
    mode_filter_t mode_filter; /**< Mode filter \ref mode_filter_t */
} can_filter_t;

/** CAN message structure */
typedef struct can_msg_s
{
    uint32_t id_frame;                /**< CAN Id of the sender */
    uint8_t data[MAX_CAN_MSG_LENGTH]; /**< Data of the message */
    uint8_t length;                   /**< Length of the data */
} can_msg_t;

/*! CAN configuration structure */
typedef struct can_cfg_s
{
    const can_filter_t **filter;  /*!< Configuration of filter CAN \ref can_filter_t*/
    uint16_t num_msg;             /*!< Numbers of message for FIFO */
    can_number_t assignament_can; /*!< Select CAN \ref can_number_t */
    can_id_type_t type;           /*!< Type CAN STD o EXT */
    void *handle;
} can_cfg_t;

/* Private values --------------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * Creates a CAN instance
 *
 * @param cfg Can configuration data
 * @return \ref ret_code_t
 */
ret_code_t can_create(can_cfg_t *cfg);

/*!
 * Register RX queue for a given CAN instance
 *
 * @param can_id \ref can_number_t
 * @param queue_id OSAL queue id
 * @retval RET_SUCCESS if ok
 * @retval RET_INV_PARAMS if invalid CAN or queue id
 * @retval RET_INT_ERROR if any other error
 */
ret_code_t can_register_rx_queue(can_number_t can_id, fifo_t queue_id);

/**
 * @brief Transmitter a message by CAN bus
 *
 * @param can_id \ref can_number_t
 * @param msg \ref can_msg_t
 * @return \ref ret_code_t
 */
ret_code_t can_tx(can_number_t can_id, can_msg_t *msg);

/**
 * @brief Register fifos queue when recived a message CAN
 *
 * @param fifo_rx \ref fifo_t
 * @return \ref ret_code_t
 */
ret_code_t can_suscribe_rx_fifo(fifo_t *fifo_rx);

/**
 * @brief Delete register fifos queue when recived a message CAN
 *
 * @param fifo_rx \ref fifo_t
 * @return \ref ret_code_t
 */
ret_code_t can_unsuscribe_rx_fifo(fifo_t *fifo_rx);

uint16_t canopen_get_mode_access(can_msg_t *msg_can);

//--------------------------------------------------------------------------------------------------
uint16_t canopen_get_index(can_msg_t *msg_can);

//--------------------------------------------------------------------------------------------------
uint16_t canopen_get_subindex(can_msg_t *msg_can);

//--------------------------------------------------------------------------------------------------
uint32_t canopen_get_data(can_msg_t *msg_can);

#endif /* _CAN_API_H */
       /**
        * @}
        */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/