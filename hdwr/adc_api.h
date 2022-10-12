/***************************************************************************************************
 * @file adc_api.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 12/02/2022
 * @date Last modification 12/02/2022 by jnieto
 * @brief ADC
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************
    @addtogroup ADC
    @{
    @defgroup ADC_API  ADC object
    @{
    @brief
    @details
*/
/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __ADC_API_H
#define __ADC_API_H

/* Includes --------------------------------------------------------------------------------------*/
#include <main.h>
#include <stdint.h>
#include "def_common.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** Enum ADCs configurated */
typedef enum
{
    ADC_A0,
    ADC_A1,
    ADC_A2,
    ADC_A3,
    ADC_T_MICRO,
    ADC_MAX
} adc_stm32_t;

typedef void (*adc_cllbk)(void *arg); /** Pointer callback when adc finish conversion*/

/* Private values --------------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief Init ADC module
 *
 * @return \ref ret_code_t
 */
ret_code_t adc_init(void);

/**
 * @brief get value adc
 *
 * @param adc_ch \ref adc_stm32_t
 * @return float 0-3.3 V
 */
float adc_get_value(adc_stm32_t adc_ch);

/**
 * @brief Register fifos queue when recived a message CAN
 *
 * @param cllback \ref adc_cllbk
 * @param arg ptr data
 * @return \ref ret_code_t
 */
ret_code_t adc_suscribe(adc_cllbk cllbck, void *arg);

#endif

/* __ADC_API_H */
/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/