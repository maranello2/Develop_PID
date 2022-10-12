/***************************************************************************************************
 * @file sevcon_conductor.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 06/03/2022
 * @date Last modification 11/04/2021 by jnieto
 * @brief SEVCON
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @defgroup SEVCON_CONDUCTOR  SEVCON object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __SEVCON_CONDUCTOR_H
#define __SEVCON_CONDUCTOR_H

/* Includes --------------------------------------------------------------------------------------*/
#include <def_common.h>
#include <sevcon/sevcon_api.h>

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief Init high level of sevcon
 *
 * @param cfg \ref sevcon_cfg_t
 * @return \ref sevcon_id_t
 */
sevcon_id_t sevcon_conductor_init(sevcon_cfg_t *cfg);

#endif /* __SEVCON_CONDUCTOR_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
