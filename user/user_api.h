/***************************************************************************************************
 * @file user_api.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 31/03/2022
 * @date Last modification 31/03/2022 by jnieto
 * @brief USER
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @addtogroup USER
    @{
    @defgroup USER_API  USER object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __USER_API_H
#define __USER_API_H

/* Includes --------------------------------------------------------------------------------------*/
#include <def_common.h>
#include <stdint.h>
#include "cmsis_os2.h"
#include "hdwr/fifo_api.h"
#include "hdwr/uart_api.h"

/* Defines ---------------------------------------------------------------------------------------*/
typedef void *ptr_obj_t;

/* Typedefs --------------------------------------------------------------------------------------*/
typedef struct
{
    void (*ratio_front_axle)(ptr_obj_t arg, float data);
    void (*ratio_rear_axle)(ptr_obj_t arg, float data);
    void (*max_front_slip)(ptr_obj_t arg, float data);
    void (*max_rear_slip)(ptr_obj_t arg, float data);
    void (*id_p_front)(ptr_obj_t arg, float data);
    void (*id_i_front)(ptr_obj_t arg, float data);
    void (*id_d_front)(ptr_obj_t arg, float data);
    void (*id_p_rear)(ptr_obj_t arg, float data);
    void (*id_i_rear)(ptr_obj_t arg, float data);
    void (*id_d_rear)(ptr_obj_t arg, float data);
    void (*inhibition_system)(ptr_obj_t arg, float data);

} user_api_t;

/** Struct cfg by user module */
typedef struct
{
    fifo_cfg_t fifo_cfg;       /** FIFO CFG */
    uart_number_t uart_number; /** Number uart */
} user_cfg_t;

/** Struct data by user module */
typedef struct
{
    user_api_t api;
    ptr_obj_t ptr_data_api;
    osThreadId_t id_thread; /** ID for thread */
    fifo_t id_fifo;
    uint16_t length_msg_tx;
    uint16_t length_msg_rx;
    float ratio_front_axle;
    float ratio_rear_axle;
    float max_front_slip;
    float max_rear_slip;
    float id_p_front;
    float id_i_front;
    float id_d_front;
    float id_p_rear;
    float id_i_rear;
    float id_d_rear;
    float inhibition_system;
} user_t;

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief Init user module
 *
 * @param cfg \ref user_cfg_t
 * @return \ref ret_code_t
 */
ret_code_t user_init(user_cfg_t *cfg);

ret_code_t user_init_api(void *obj, user_api_t *api);

float user_get_ratio_front_axle(void);
float user_get_ratio_rear_axle(void);
float user_get_max_front_slip(void);
float user_get_max_rear_slip(void);
float user_get_id_p_front(void);
float user_get_id_i_front(void);
float user_get_id_d_front(void);
float user_get_id_p_rear(void);
float user_get_id_i_rear(void);
float user_get_id_d_rear(void);
float user_get_inhibition_system(void);

#endif /* __USER_API_H */

/**
 * @}
 */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
