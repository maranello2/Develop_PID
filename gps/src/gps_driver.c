/***************************************************************************************************
 * @file gps_driver.c
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 15/03/2022
 * @date Last modification 15/03/2022 by jnieto
 * @brief gps functions
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup GPS_DRIVER
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/
#include "gps_driver.h"
#include "gps_hdwr.h"
#include "gps/gps_config.h"
#include "gps_conductor.h"

#include <def_common.h>
#include <log/log_api.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> /* atof */
#include <stdbool.h>

/* Defines ---------------------------------------------------------------------------------------*/
#define CRC_OK 0x1A8C

/* Typedefs --------------------------------------------------------------------------------------*/
typedef union
{
    uint8_t data_u8[4];
    float data_float;
} convert_string_to_float_t;

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/
/**
 * @brief Process new message
 *
 * @param gps \ref gps_t
 * @param msg ptr to void
 */
static void gps_proccess_message(gps_t *gps, void *msg);
static void proccess_message_ins(gps_t *gps, void *msg);
bool checksum(unsigned char data[], unsigned int length);

static float convert_string_to_float(uint8_t *data_convert);
/* Private functions -----------------------------------------------------------------------------*/
bool checksum(unsigned char data[], unsigned int length)
{
    unsigned int i;
    unsigned short crc = 0;
    for (i = 0; i < length; i++)
    {
        crc = (unsigned char)(crc >> 8) | (crc << 8);
        crc ^= data[i];
        crc ^= (unsigned char)(crc & 0xff) >> 4;
        crc ^= crc << 12;
        crc ^= (crc & 0x00ff) << 5;
    }

    return (crc == CRC_OK) ? true : false;
}

//--------------------------------------------------------------------------------------------------
static void gps_proccess_message(gps_t *gps, void *msg)
{
    uint8_t *new_msg = (uint8_t *)msg;
    output_group_t group;
    type_subscribe_gps_t cllback_group = MAX_SUBSCRIBE_GPS;

    if (new_msg[POS_HEADER_SYNC] == HEADER_SYNC && checksum((unsigned char *)msg, gps->length_msg))
    {
        group.all = new_msg[POS_HEADER_GROUP];
        if (group.bit.commom)
        {
            // UNUSED (commom)
        }
        else if (group.bit.time)
        {
            // UNUSED (time )
        }
        else if (group.bit.imu)
        {
            // UNUSED (imu )
        }
        else if (group.bit.gnss1)
        {
            // UNUSED (gnss1 )
        }
        else if (group.bit.attitude)
        {
            // UNUSED (attitude )
        }
        else if (group.bit.ins)
        {
            proccess_message_ins(gps, msg);
            cllback_group = GROUP_INS;
        }
        else if (group.bit.gsnn2)
        {
            // UNUSED (gsnn2 )
        }

        gps_conductor_notify_new_data(cllback_group);
    }
}

//--------------------------------------------------------------------------------------------------
static void proccess_message_ins(gps_t *gps, void *msg)
{

    uint8_t *ins_msg = (uint8_t *)msg;
    output_fields_ins_t fields;

    fields.all = ((uint16_t)ins_msg[POS_HEADER_FIELDS_MSB] << 4) + ins_msg[POS_HEADER_FIELDS_LSB];

    if (fields.bit.vel_ned)
    {
        gps->velned_north_axis = convert_string_to_float(&ins_msg[POS_INS_VELNED_NORTH_AXIS]);
        gps->velned_east_axis = convert_string_to_float(&ins_msg[POS_INS_VELNED_EAST_AXIS]);
        gps->velned_down_axis = convert_string_to_float(&ins_msg[POS_INS_VELNED_DOWN_AXIS]);
    }
}

//--------------------------------------------------------------------------------------------------
static float convert_string_to_float(uint8_t *data_convert)
{
    convert_string_to_float_t data_converted;

    for (uint8_t idx = 0; idx < 4; idx++)
    {
        data_converted.data_u8[3 - idx] = data_convert[idx];
    }

    return data_converted.data_float;
}

/* Public functions ------------------------------------------------------------------------------*/
ret_code_t gps_driver_log_init(gps_t *gps)
{
    char msg[20];

    sprintf(msg, "CREATED 0x%x", gps);

    return (log_new_msg(gps->name, LOG_DEBUG, msg));
}

//--------------------------------------------------------------------------------------------------
void gps_driver_get_msg(void *arg)
{
    gps_t *gps = (gps_t *)arg;
    void *msg;

    while (1)
    {
        msg = gps_hdwr_get_msg(gps);
        if (msg)
        {
            gps_proccess_message(gps, msg);
        }
    }
}

//--------------------------------------------------------------------------------------------------
float gps_driver_get_velocity_north_axis(gps_t *arg)
{

    return (arg) ? arg->velned_north_axis : 0.0;
}

//--------------------------------------------------------------------------------------------------
float gps_driver_get_velocity_east_axis(gps_t *arg)
{

    return (arg) ? arg->velned_east_axis : 0.0;
}

//--------------------------------------------------------------------------------------------------
float gps_driver_get_velocity_down_axis(gps_t *arg)
{
    return (arg) ? arg->velned_down_axis : 0.0;
}

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
