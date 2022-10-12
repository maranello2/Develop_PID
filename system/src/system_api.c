/***************************************************************************************************
 * @file system_api.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 24/11/2021
 * @date Last modification 11/04/2021 by jnieto
 * @brief All System of the Kart
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup SYSTEM_API
    @{

*/

/* Includes --------------------------------------------------------------------------------------*/
#include "system/system_api.h"
#include "system/src/system_obj.h"

#include "heartbeat/heartbeat_api.h"
#include "hdwr/gpio_api.h"
#include "periodic/periodic_api.h"
#include "log/log_api.h"
#include "hdwr/uart_api.h"
#include "sevcon/sevcon_api.h"
#include "gps/gps_api.h"
#include "user/user_api.h"

#include "cmsis_os2.h"
#include "def_common.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/
gpio_out_t gpio = LED_BLUE; /**< Fixed the GPIO of LED */

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
void system_init(void)
{
    ret_code_t ret = RET_SUCCESS;
    // gpio_on(gpio);

    gpio_on(gpio);
    /* init LOGs */
    ret = log_init();

    /* Init periodic module */
    ret = (RET_SUCCESS == ret) ? periodic_init() : ret;
    /* Init heartbeat module */
    ret = (RET_SUCCESS == ret) ? heartbeat_init(&heartbeat) : ret;

    /* INIT COMMS */
    /* Init CAN module */
    ret = (RET_SUCCESS == ret) ? can_create(&can_cfg) : ret;
    /* Init USART */
    ret = (RET_SUCCESS == ret) ? uart_create(&uart_cfg) : ret;
    /* Init ADC */
    ret = (RET_SUCCESS == ret) ? adc_init() : ret;

    /* INIT PERIPHERALS */
    /* Init user module */
    ret = (RET_SUCCESS == ret) ? user_init(&user_cfg) : ret;
    /* Init flight controller module */
    ret = (RET_SUCCESS == ret) ? flight_controller_init(&flight_controller_cfg) : ret;

    if (RET_SUCCESS == ret)
    {
        gpio_off(gpio);
    }
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
