/***************************************************************************************************
 * @file gps_hdwr.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 15/03/2022
 * @date Last modification 31/03/2022 by jnieto
 * @brief gps functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup gps_HDWR
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "gps_hdwr.h"
#include "gps/gps_config.h"
#include "gps_driver.h"

#include "hdwr/uart_api.h"

/* Defines ---------------------------------------------------------------------------------------*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/
uint8_t msg[SIZEOF_MSG_GPS];

/* Private functions declaration -----------------------------------------------------------------*/
static uint16_t get_lenght_msg(gps_cfg_t *arg);
static uint16_t get_lenght_fields_lenght(output_fields_t field);

/* Private functions -----------------------------------------------------------------------------*/
static uint16_t get_lenght_msg(gps_cfg_t *arg)
{
    uint16_t ret = HEADER_SIZE + CRC_SIZE;

    ret += get_lenght_fields_lenght(arg->output_fields);

    return ret;
}

//--------------------------------------------------------------------------------------------------
static uint16_t get_lenght_fields_lenght(output_fields_t field)
{
    uint16_t ret = 0;
    output_fields_ins_t ins_lenght = field.ins;

    ret += (ins_lenght.bit.ins_status) * 2;
    ret += (ins_lenght.bit.pos_lla) * 24;
    ret += (ins_lenght.bit.pos_ecef) * 24;
    ret += (ins_lenght.bit.vel_body) * 12;
    ret += (ins_lenght.bit.vel_ned) * 12;
    ret += (ins_lenght.bit.vel_ecef) * 12;
    ret += (ins_lenght.bit.mag_ecef) * 12;
    ret += (ins_lenght.bit.accel_ecef) * 12;
    ret += (ins_lenght.bit.lineal_accel_ecef) * 12;
    ret += (ins_lenght.bit.pos_u) * 4;
    ret += (ins_lenght.bit.vel_u) * 4;

    return ret;
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t gps_hdwr_init(gps_cfg_t *cfg, gps_t *data)
{
    ret_code_t ret = RET_INT_ERROR;

    cfg->fifo_cfg.size_msg = get_lenght_msg(cfg);
    data->length_msg = cfg->fifo_cfg.size_msg;

    data->fifo_id = fifo_create_queue(&cfg->fifo_cfg);

    ret = (data->fifo_id) ? uart_suscribe_rx_fifo(data->fifo_id, cfg->fifo_cfg.size_msg, cfg->uart_number) : ret;

    return ret;
}

//--------------------------------------------------------------------------------------------------
void *gps_hdwr_get_msg(gps_t *gps)
{
    return (RET_SUCCESS == fifo_dequeue_msg(gps->fifo_id, &msg)) ? msg : NULL;
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
