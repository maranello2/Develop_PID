/***************************************************************************************************
 * @file sevcon_hdwr.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 06/03/2022
 * @date Last modification 06/03/2022 by jnieto
 * @brief SEVCON
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @defgroup SEVCON_HDWR  SEVCON object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __SEVCON_HDWR_H
#define __SEVCON_HDWR_H

/* Includes --------------------------------------------------------------------------------------*/
#include <sevcon/sevcon_api.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief init hadware sevcon
 *
 * @param cfg \ref sevcon_cfg_t
 * @param data \ref sevcon_t
 * @return \ref ret_code_t
 */
ret_code_t sevcon_hdwr_init(sevcon_cfg_t *cfg, sevcon_t *data);

/**
 * @brief get message from fifo modules
 *
 * @param sevcon \ref sevcon_t
 * @return void* \ref can_msg_t
 */
void *sevcon_hdwr_get_msg(sevcon_t *sevcon);

/**
 * @brief Get index of new message
 *
 * @param msg \ref msg_can_t
 * @return uint16_t
 */
uint16_t sevcon_hdwr_get_index(void *msg);

/**
 * @brief Get subindex of new message
 *
 * @param msg \ref msg_can_t
 * @return uint16_t
 */
uint16_t sevcon_hdwr_get_subindex(void *msg);

/**
 * @brief Get data of new message
 *
 * @param msg \ref msg_can_t
 * @return uint16_t
 */
uint32_t sevcon_hdwr_get_data(void *msg);

/**
 * @brief Get index of sevcon
 *
 * @param msg  \ref msg_can_t
 * @return uint16_t
 */
uint16_t sevcon_hdwr_get_num_sevcon(void *msg);

/**
 * @brief return index of opposite motor
 *
 * @param id_motor defines on sevcon_config.h
 * @return uint16_t
 */
uint16_t sevcon_hdwr_get_opposite_motor(uint16_t id_motor);

#endif /* __SEVCON_HDWR_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
