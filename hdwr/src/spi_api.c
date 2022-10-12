
/***************************************************************************************************
 * @file spi_api.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 11/11/2021
 * @date Last modification 11/11/2021 by jnieto
 * @brief SPI
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup SPI_API
    @{

*/

/* Includes --------------------------------------------------------------------------------------*/
#include "hdwr/spi_api.h"

#include <hdwr/fifo_api.h>
#include <cmsis_os2.h>
#include <stm32l5xx_hal.h>
#include <def_common.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Defines ---------------------------------------------------------------------------------------*/
/** Inital name of SPIs */
#define NAME_SPI "SPI_"

__attribute__((weak)) extern SPI_HandleTypeDef hspi1;
__attribute__((weak)) extern SPI_HandleTypeDef hspi2;
__attribute__((weak)) extern SPI_HandleTypeDef hspi3;

/* Typedefs --------------------------------------------------------------------------------------*/
/** Definitions for defaultTask */
osThreadAttr_t spi_task_attributes =
    {
        .priority = (osPriority_t)osPriorityNormal,
        .stack_size = 100};

/** define all falgs */
#define SPI_TX (0x01U << 0)
#define SPI_RX (0x01U << 1)
#define SPI_ALL_FLAG (SPI_RX | SPI_TX)

/** Redefine structures of HAL by STM32 */
typedef struct spi_obj_hal_s
{
    SPI_HandleTypeDef *spi_hal[SPI_MAX]; /**< Struct HAL Drivers */
} spi_obj_hal_t;

spi_obj_hal_t spi_obj_hal[] =
    {
        [SPI_A] =
            {
                .spi_hal = &hspi1,
            },
        [SPI_B] =
            {
                .spi_hal = &hspi2,
            },
        [SPI_C] =
            {
                .spi_hal = &hspi3,
            },
};

/** Structure internal of SPI */
typedef struct spi_s
{
    char name[5];           /**< Name of thread */
    void *driver_hal;       /**< Pointer of object of driver HAL */
    void *id_fifo;          /**< ID by FIFOs */
    osThreadId_t id_thread; /**< ID of thread */
} spi_t;

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Run Thread
 *
 * @param aguments \ref spi_t
 */
void spi_task(void *aguments);

/* Private functions -----------------------------------------------------------------------------*/
void spi_task(void *arguments)
{
    uint8_t data[4] = {1, 2, 3, 4};

    if (arguments)
    {
        spi_t *spi = (spi_t *)arguments;
        uint32_t flag_thread;

        while (1)
        {
            flag_thread = osThreadFlagsWait(SPI_ALL_FLAG, osFlagsWaitAny, osWaitForever);

            if (flag_thread == SPI_TX)
            {
                HAL_SPI_Transmit(spi->driver_hal, &data[0], sizeof(data), 0x00);
            }
        }
    }
}
/* Public functions ------------------------------------------------------------------------------*/
void *spi_init(spi_cfg_t *cfg)
{

    if (SPI_MAX < cfg->spi)
    {
        return NULL;
    }

    spi_t *spi = (spi_t *)calloc(1, sizeof(spi_t));

    if (spi)
    {
        char id_sci[] = "1";
        spi->driver_hal = &spi_obj_hal[cfg->spi];

        strncat(spi->name, NAME_SPI, sizeof(spi->name) - 1);
        id_sci[0] += cfg->spi;
        strncat(spi->name, id_sci, 1);

        spi_task_attributes.name = (spi->name) ? spi->name : "unknown";
        spi->id_thread = osThreadNew(spi_task, spi, &spi_task_attributes);

        spi->id_fifo = fifo_create_queue(&cfg->spi_fifo);
    }

    return spi;
}

//--------------------------------------------------------------------------------------------------
ret_code_t spi_enqueue(void *arg)
{
    ret_code_t ret = RET_PARAM_ERROR;
    spi_t *spi = (spi_t *)arg;

    if (!spi || NULL == spi->id_thread)
    {
        return ret;
    }

    // jnieto encolar el mensaje a enviar

    ret = !(osThreadFlagsSet(spi->id_thread, SPI_TX))
              ? RET_SUCCESS
              : RET_INT_ERROR;

    return ret;
}
/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/