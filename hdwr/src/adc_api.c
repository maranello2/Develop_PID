
/***************************************************************************************************
 * @file adc_api.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 12/02/2022
 * @date Last modification 12/02/2022 by jnieto
 * @brief adc
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup ADC_API
    @{

*/

/* Includes --------------------------------------------------------------------------------------*/
#include "hdwr/adc_api.h"
#include <stm32l5xx_hal_adc.h>
#include <stm32l552xx.h>
#include "def_common.h"

#include <stdio.h>
#include <stdbool.h>

extern ADC_HandleTypeDef hadc1;
/* Defines ---------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/
/** Values save adc converter and read from DMA */
uint32_t adc1_dma[ADC_MAX];

/** Flag check if configurated the ADC */
bool configurated = false;

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t adc_init(void)
{
    if (configurated)
    {
        return RET_SUCCESS;
    }

    HAL_NVIC_DisableIRQ(DMA1_Channel1_IRQn);

    // Calibrate The ADC On Power-Up For Better Accuracy
    HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);

    configurated = (HAL_OK == HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc1_dma, ADC_MAX))
                       ? true
                       : false;

    return (configurated ? RET_SUCCESS : RET_INT_ERROR);
}

//--------------------------------------------------------------------------------------------------
float adc_get_value(adc_stm32_t adc_ch)
{
    float value;

    if (ADC_MAX <= adc_ch)
    {
        value = UINT32_MAX;
    }
    else
    {
        value = ((adc1_dma[adc_ch] * 3.3) / 4096.0);

        if (adc_ch == ADC_T_MICRO)
        {
            value = (value - 0.76) / 0.0025 + 25;
        }
    }

    return value;
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/