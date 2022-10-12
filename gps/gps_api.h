/***************************************************************************************************
 * @file gps_api.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 15/03/2022
 * @date Last modification 15/03/2022 by jnieto
 * @brief gps
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @addtogroup GPS
    @{
    @defgroup GPS_API  gps object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __GPS_API_H
#define __GPS_API_H

/* Includes --------------------------------------------------------------------------------------*/
#include <def_common.h>
#include <stdint.h>
#include <hdwr/fifo_api.h>
#include <hdwr/uart_api.h>

/* Defines ---------------------------------------------------------------------------------------*/
/** Pontier of struct of GPS */
typedef uint32_t gps_id_t;

/* Typedefs --------------------------------------------------------------------------------------*/

/** Typedef function callback in the module peridic */
typedef void (*gps_cllbck)(void *arg);

/** OutputGroup */
typedef union output_group_s
{
    uint8_t all;
    struct
    {
        uint8_t commom : 1;
        uint8_t time : 1;
        uint8_t imu : 1;
        uint8_t gnss1 : 1;
        uint8_t attitude : 1;
        uint8_t ins : 1;
        uint8_t gsnn2 : 1;
        uint8_t free : 1;
    } bit;

} output_group_t;

/** OutputFields by OutputGroup 1 Common */
typedef union output_fields_common_s
{
    uint16_t all;
    struct
    {
        uint16_t time_startup : 1;
        uint16_t time_gps : 1;
        uint16_t time_syncln : 1;
        uint16_t yaw_pitch_roll : 1;
        uint16_t quaternion : 1;
        uint16_t angular_rate : 1;
        uint16_t position : 1;
        uint16_t velocity : 1;
        uint16_t accel : 1;
        uint16_t imu : 1;
        uint16_t mag_pres : 1;
        uint16_t delta_theta : 1;
        uint16_t ins_status : 1;
        uint16_t syncincnt : 1;
        uint16_t time_gps_pps : 1;
        uint16_t free : 1;
    } bit;

} output_fields_common_t;

/** OutputFields by OutputGroup 2 Time */
typedef union output_fields_time_s
{
    uint16_t all;
    struct
    {
        uint16_t time_startup : 1;
        uint16_t time_gps : 1;
        uint16_t gps_tow : 1;
        uint16_t gps_week : 1;
        uint16_t time_syncln : 1;
        uint16_t time_gps_pps : 1;
        uint16_t time_utc : 1;
        uint16_t sync_in_cnt : 1;
        uint16_t sync_out_cnt : 1;
        uint16_t time_status : 1;
        uint16_t free : 6;
    } bit;

} output_fields_time_t;

/** OutputFields by OutputGroup 3 IMU */
typedef union output_fields_imu_s
{
    uint16_t all;
    struct
    {
        uint16_t imu_status : 1;
        uint16_t uncomp_mag : 1;
        uint16_t uncomp_accel : 1;
        uint16_t uncomp_gyro : 1;
        uint16_t temp : 1;
        uint16_t pres : 1;
        uint16_t delta_theta : 1;
        uint16_t delta_vel : 1;
        uint16_t mag : 1;
        uint16_t accel : 1;
        uint16_t angular_rate : 1;
        uint16_t free : 5;
    } bit;

} output_fields_imu_t;

/** OutputFields by OutputGroup 4 GNSS1 */
typedef union output_fields_gnss1_s
{
    uint16_t all;
    struct
    {
        uint16_t utc : 1;
        uint16_t tow : 1;
        uint16_t week : 1;
        uint16_t num_sats : 1;
        uint16_t fix : 1;
        uint16_t pos_lla : 1;
        uint16_t pos_ecef : 1;
        uint16_t vel_ned : 1;
        uint16_t vel_ecef : 1;
        uint16_t pos_u : 1;
        uint16_t vel_u : 1;
        uint16_t time_u : 1;
        uint16_t time_info : 1;
        uint16_t dop : 1;
        uint16_t sat_info : 1;
        uint16_t raw_meas : 1;
    } bit;

} output_fields_gnss1_t;

/** OutputFields by OutputGroup 5 ATTITUDE */
typedef union output_fields_attitude_s
{
    uint16_t all;
    struct
    {
        uint16_t resrved : 1;
        uint16_t yaw_pitch_roll : 1;
        uint16_t quaternion : 1;
        uint16_t dcm : 1;
        uint16_t mag_ned : 1;
        uint16_t accel_ned : 1;
        uint16_t linear_accel_body : 1;
        uint16_t linear_accel_ned : 1;
        uint16_t ypr_u : 1;
        uint16_t reserved_2 : 3;
        uint16_t free : 4;
    } bit;

} output_fields_attitude_t;

/** OutputFields by OutputGroup 6 INS */
typedef union output_fields_ins_s
{
    uint16_t all;
    struct
    {
        uint16_t ins_status : 1;
        uint16_t pos_lla : 1;
        uint16_t pos_ecef : 1;
        uint16_t vel_body : 1;
        uint16_t vel_ned : 1;
        uint16_t vel_ecef : 1;
        uint16_t mag_ecef : 1;
        uint16_t accel_ecef : 1;
        uint16_t lineal_accel_ecef : 1;
        uint16_t pos_u : 1;
        uint16_t vel_u : 1;
        uint16_t free : 5;
    } bit;

} output_fields_ins_t;

/** OutputFields by OutputGroup 7 GNSS2 */
typedef union output_fields_gnss2_s
{
    uint16_t all;
    struct
    {
        uint16_t utc : 1;
        uint16_t tow : 1;
        uint16_t week : 1;
        uint16_t num_sats : 1;
        uint16_t fix : 1;
        uint16_t pos_lla : 1;
        uint16_t pos_ecef : 1;
        uint16_t vel_ned : 1;
        uint16_t vel_ecef : 1;
        uint16_t pos_u : 1;
        uint16_t vel_u : 1;
        uint16_t time_u : 1;
        uint16_t time_info : 1;
        uint16_t dop : 1;
        uint16_t sat_info : 1;
        uint16_t raw_meas : 1;
    } bit;

} output_fields_gnss2_t;

/** OutputFields */
typedef struct output_fields_s
{
    output_fields_common_t common;
    output_fields_time_t time;
    output_fields_imu_t imu;
    output_fields_gnss1_t gnss1;
    output_fields_attitude_t attitude;
    output_fields_ins_t ins;
    output_fields_gnss2_t gnss2;
} output_fields_t;

/** Configuration of gps */
typedef struct gps_cfg_s
{
    fifo_cfg_t fifo_cfg;
    uart_number_t uart_number;
    output_fields_t output_fields;
} gps_cfg_t;

/** Data of secvon */
typedef struct gps_s
{
    char const *name;
    osThreadId_t id_thread;
    fifo_t fifo_id;
    output_fields_t output_fields;
    uint16_t length_msg;
    float velned_north_axis;
    float velned_east_axis;
    float velned_down_axis;
} gps_t;

/** ENUM susbcribe */
typedef enum type_subscribe_gps_e
{
    GROUP_COMMOM,
    GROUP_TIME,
    GROUP_IMU,
    GROUP_GNSS1,
    GROUP_ATTITUDE,
    GROUP_INS,
    GROUP_GSNN2,
    MAX_SUBSCRIBE_GPS
} type_subscribe_gps_t;

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/
/**
 * @brief config gps drivers
 *
 * @param cfg \ref gps_cfg_t
 * @return \ref ret_code_t
 */
gps_id_t
gps_init(gps_cfg_t *cfg);

/**
 * @brief Getter values reads by GPS
 *
 * @return float
 */
float gps_get_velocity_north_axis(gps_id_t id);
float gps_get_velocity_east_axis(gps_id_t id);
float gps_get_velocity_down_axis(gps_id_t id);
ret_code_t gps_subscribe(gps_id_t id, gps_cllbck cllbck, void *arg, type_subscribe_gps_t type_subscribe_gps);

#endif /* __GPS_API_H */

/**
 * @}
 */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
