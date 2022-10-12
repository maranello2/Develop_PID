/***************************************************************************************************
 * @file user_hdwr.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 31/03/2022
 * @date Last modification 02/04/2022 by jnieto
 * @brief USER functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup USER_HDWR
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "user_hdwr.h"
#include "user/user_api.h"
#include "user/user_config.h"
#include "hdwr/fifo_api.h"
/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/
#if defined (USER_SIZE_PAYLOAD) && defined (USER_NUMBER_PAYLOAD)
    uint8_t msg_user[(USER_SIZE_PAYLOAD * USER_NUMBER_PAYLOAD)+USER_SIZE_HEADER];
#elif defined (USER_SIZE_PAYLOAD)
    uint8_t msg_user[USER_SIZE_PAYLOAD+USER_SIZE_HEADER];
#endif

/* Private functions declaration -----------------------------------------------------------------*/
static uint16_t get_lenght_msg(void);

/* Private functions -----------------------------------------------------------------------------*/
static uint16_t get_lenght_msg(void)
{
    uint16_t ret = 0;
#if defined (USER_SIZE_HEADER)
    ret += USER_SIZE_HEADER;
#endif

#if defined (USER_SIZE_PAYLOAD) && defined (USER_NUMBER_PAYLOAD)
    ret += (USER_SIZE_PAYLOAD * USER_NUMBER_PAYLOAD);
#elif defined (USER_SIZE_PAYLOAD)
    ret += USER_SIZE_PAYLOAD;
#endif

    return ret;
}
/* Public functions ------------------------------------------------------------------------------*/
ret_code_t user_hdwr_init(user_t *obj, user_cfg_t *cfg)
{
    cfg->fifo_cfg.size_msg = get_lenght_msg();
    obj->length_msg_rx = cfg->fifo_cfg.size_msg ;

    obj->id_fifo = fifo_create_queue(&cfg->fifo_cfg);

    ret_code_t ret = (obj->id_fifo) ? uart_suscribe_rx_fifo(obj->id_fifo, cfg->fifo_cfg.size_msg, cfg->uart_number) : RET_INT_ERROR;

    return ret;
}

//--------------------------------------------------------------------------------------------------
void *user_hdwr_get_msg (user_t *obj)
{
    return (RET_SUCCESS == fifo_dequeue_msg(obj->id_fifo, &msg_user)) ? msg_user : NULL;
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
