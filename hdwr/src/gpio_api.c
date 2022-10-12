
/***************************************************************************************************
 * @file gpio_api.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 11/11/2021
 * @date Last modification 11/11/2021 by jnieto
 * @brief GPIO
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup GPIO_API
    @{

*/

/* Includes --------------------------------------------------------------------------------------*/
#include "hdwr/gpio_api.h"
#include "main.h"
#include <stm32l5xx_hal_gpio.h>

/* Defines ---------------------------------------------------------------------------------------*/
typedef struct gpio_hal_s
{
    void *port;
    uint16_t pin;
} gpio_hal_t;

gpio_hal_t gpio_hal[] =
    {
        [LED_RED] = {LED_RED_GPIO_Port, LED_RED_Pin},
        [LED_GREEN] = {LED_GREEN_GPIO_Port, LED_GREEN_Pin},
        [LED_BLUE] = {LED_BLUE_GPIO_Port, LED_BLUE_Pin},
};

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
void gpio_on(gpio_out_t pin)
{
    if (MAX_GPIO_OUT > pin)
    {
        HAL_GPIO_WritePin(gpio_hal[pin].port, gpio_hal[pin].pin, GPIO_PIN_SET);
    }
}

//--------------------------------------------------------------------------------------------------
void gpio_off(gpio_out_t pin)
{
    if (MAX_GPIO_OUT > pin)
    {
        HAL_GPIO_WritePin(gpio_hal[pin].port, gpio_hal[pin].pin, GPIO_PIN_RESET);
    }
}

//--------------------------------------------------------------------------------------------------
void gpio_toggle(gpio_out_t pin)
{
    if (MAX_GPIO_OUT > pin)
    {
        HAL_GPIO_TogglePin(gpio_hal[pin].port, gpio_hal[pin].pin);
    }
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/