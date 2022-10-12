/***************************************************************************************************
 * @file gpio_api.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 11/11/2021
 * @date Last modification 17/11/2021 by jnieto
 * @brief GPIO
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************
    @addtogroup GPIO
    @{
    @defgroup GPIO_API  GPIO object
    @{
    @brief
    @details
*/
/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __GPIO_API_H
#define __GPIO_API_H

/* Includes --------------------------------------------------------------------------------------*/
#include <main.h>
#include <stdint.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
typedef enum
{
    LED_RED,
    LED_GREEN,
    LED_BLUE,
    MAX_GPIO_OUT
} gpio_out_t;

typedef enum
{
    MAX_GPIO_IN
} gpio_in_t;

/* Private values --------------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
void gpio_on(gpio_out_t pin);
void gpio_off(gpio_out_t pin);
void gpio_toggle(gpio_out_t pin);

#endif /* __GPIO_API_H */
       /**
        * @}
        */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/