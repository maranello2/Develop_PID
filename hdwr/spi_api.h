/***************************************************************************************************
 * @file spi_api.h 
 * @author jnieto
 * @version 1.0.0.0.0 
 * @date Creation: 17/11/2021
 * @date Last modification 17/11/2021 by jnieto
 * @brief SPI
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************
    @addtogroup SPI
    @{
    @defgroup SPI_API  SPI object
    @{
    @brief
    @details
*/
/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __SPI_API_H
#define __SPI_API_H

/* Includes --------------------------------------------------------------------------------------*/
#include <def_common.h>
#include <hdwr/fifo_api.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/
/** Types de SPI */
typedef enum
{
    SPI_A,
    SPI_B,
    SPI_C,
    SPI_MAX
} num_spi_t;

typedef struct spi_cfg_s
{
    num_spi_t spi;
    fifo_cfg_t spi_fifo; /** FIFO configuration */
} spi_cfg_t;

/* Private values --------------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief Init comunications with SPI
 * 
 * @param cfg \ref num_spi_t
 * @return pointer of obj
 */
void *spi_init(spi_cfg_t *cfg);

/**
 * @brief Send new message by SPI
 * 
 * @param arg \ref spi_t
 * @return ret_code_t \ref ret_code_t
 */
ret_code_t spi_enqueue(void *arg);

#endif /* __SPI_API_H */
       /**
  * @}
  */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/