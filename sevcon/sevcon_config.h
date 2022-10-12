/***************************************************************************************************
 * @file sevcon_config.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 06/03/2022
 * @date Last modification 06/03/2022 by jnieto
 * @brief SEVCON
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ***************************************************************************************************

    @defgroup SEVCON_CONFIG  SEVCON object
    @{
    @brief
    @details

***************************************************************************************************/

/* Define to prevent recursive inclusion ---------------------------------------------------------*/
#ifndef __SEVCON_CONFIG_H
#define __SEVCON_CONFIG_H

/* Includes --------------------------------------------------------------------------------------*/
#include <hdwr/can_api.h>

/* Defines ---------------------------------------------------------------------------------------*/
/** MAX of functions callback regsiter every SEVCON */
#define SEVCON_MAX_DRIVERS 4

/** Define type message RX of the CANOpen */
#define OD_TYPE_MSG_CAN MNT

/** define ID of every motor */
#define MOTOR_FRONT_LEFT 0
#define MOTOR_FRONT_RIGHT 1
#define MOTOR_REAR_LEFT 2
#define MOTOR_REAR_RIGHT 3

/** Define opposite motor */
#define MOTOR_OPPOSITE_FRONT_LEFT 1
#define MOTOR_OPPOSITE_FRONT_RIGHT 0
#define MOTOR_OPPOSITE_REAR_LEFT 3
#define MOTOR_OPPOSITE_REAR_RIGHT 2

/** Define parameters of kart */
#define WHEEL_SPOKE (float)0.1319 // wheel radius meter
#define CONTS_RPM_WHEEL_AXLE (float)0.10472 // 2*pi/60

/** Define levels security */
#define WRN_TEMP_LEVEL_1 80                  //ºC
#define WRN_TEMP_LEVEL_2 100                 //ºC
#define WRN_DECREASE_MOTOR_WORKING_LVL_1 20  //%
#define WRN_DECREASE_MOTOR_WORKING_LVL_2 80  //%
#define WRN_DECREASE_MOTOR_WORKING_ERROR 100 //%

#endif /* __SEVCON_CONFIG_H */

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
