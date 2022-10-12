/***************************************************************************************************
 * @file pwm_api.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 27/12/2021
 * @date Last modification 27/12/2021 by jnieto
 * @brief PWM
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************
    @addtogroup PWM
    @{
    @defgroup PWM_API  PWM object
    @{
    @brief
    @details
*/
/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __PWM_API_H
#define __PWM_API_H

/* Includes --------------------------------------------------------------------------------------*/
#include <main.h>
#include <stdint.h>
#include <def_common.h>

/* Defines ---------------------------------------------------------------------------------------*/
/** CAN ID */
typedef uint32_t pwm_id_t;

/* Typedefs --------------------------------------------------------------------------------------*/
/** Enum of number from PWMs */
typedef enum
{
    PWM_1,
    PWM_2,
    PWM_3,
    PWM_4,
    PWM_5,
    PWM_6,
    PWM_7,
    PWM_8,
    PWM_15,
    PWM_16,
    PWM_17,
    PWM_MAX,
} pwm_number_t;

/** Enum of number of channels from PWMs */
typedef enum
{
    PWM_CHANNEL_1 = 0x00000000U,   /*!< Capture/compare channel 1 identifier      */
    PWM_CHANNEL_2 = 0x00000004U,   /*!< Capture/compare channel 2 identifier      */
    PWM_CHANNEL_3 = 0x00000008U,   /*!< Capture/compare channel 3 identifier      */
    PWM_CHANNEL_4 = 0x0000000CU,   /*!< Capture/compare channel 4 identifier      */
    PWM_CHANNEL_5 = 0x00000010U,   /*!< Compare channel 5 identifier              */
    PWM_CHANNEL_6 = 0x00000014U,   /*!< Compare channel 6 identifier              */
    PWM_CHANNEL_ALL = 0x0000003CU, /*!< Global Capture/compare channel identifier  */
    PWM_CHANNEL_MAX,
} pwm_channel_t;

/* Private values --------------------------------------------------------------------------------*/
typedef struct pwm_cfg_s
{
    pwm_number_t pwm;      /** Number of PWM */
    pwm_channel_t channel; /** Numbewr of channel of PWM */
    uint32_t duty;         /** Duty of pwm 0%-100% */
    uint32_t frequency;    /** Frecuency of signal in Hz */
} pwm_cfg_t;

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief create PWMs instance
 *
 * @param cfg \ref pwm_cfg_t
 * @return pwm_id_t \ref pwm_id_t
 */
pwm_id_t pwm_create(pwm_cfg_t *cfg);

/**
 * @brief Start PWMs
 *
 * @param arg \ref pwm_id_t
 * @return \ref ret_code_t
 */
ret_code_t pwm_start(pwm_id_t arg);

/**
 * @brief Update  value duty of PWM
 *
 * @param arg \ref pwm_id_t
 * @param duty new duty value 0% - 100%
 * @return \ref ret_code_t
 */
ret_code_t pwm_set_new_duty(pwm_id_t arg, uint16_t duty);

#endif /* __PWM_API_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/