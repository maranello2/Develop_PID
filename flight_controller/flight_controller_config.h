/***************************************************************************************************
 * @file flight_controller_config.h
 * @author jnieto
 * @version 1.0.0.0.0
 * @date Creation: 14/02/2022
 * @date Last modification 14/02/2022 by jnieto
 * @brief flight controller
 * @par
 *  COPYRIGHT NOTICE: (c) jnieto
 *  All rights reserved
 ****************************************************************************************************

    @addtogroup FLIGHT_CONTROLLER_CONFIG
    @{

*/
/* Includes --------------------------------------------------------------------------------------*/

/* Defines ---------------------------------------------------------------------------------------*/

// Cofing SLPIT and PID b default values
#define FLIGTH_CONTROLLER_SLIP_FRONT_DEFAULT 0.07 //%
#define FLIGTH_CONTROLLER_SLIP_REAR_DEFAULT 0.07  //%
#define FLIGTH_CONTROLLER_RATIO_FRONT_DEFAULT 2 //%
#define FLIGTH_CONTROLLER_RATIO_REAR_DEFAULT 2.4  //%
#define FLIGTH_CONTROLLER_P_FRONT_DEFAULT 0.3
#define FLIGTH_CONTROLLER_I_FRONT_DEFAULT 0
#define FLIGTH_CONTROLLER_D_FRONT_DEFAULT 0.2
#define FLIGTH_CONTROLLER_P_REAR_DEFAULT 0.3
#define FLIGTH_CONTROLLER_I_REAR_DEFAULT 0
#define FLIGTH_CONTROLLER_D_REAR_DEFAULT 0.2

// 1 byte head + 1 byte id frame + 4*4 frame
#define MAX_SIZEOF_TX_VALUES 18
#define FLIGTH_CONTROLLER_HEAD 0x2A

#define FLIGTH_CONTROLLER_ID_DATA_SLIPT 0x0A
#define FLIGTH_CONTROLLER_ID_DATA_REAR 0x0B
#define FLIGTH_CONTROLLER_ID_DATA_FRONT 0x0C

// EXAMPLE FRAMES
/** FLIGTH_CONTROLLER_ID_DATA_SLIPT
1byte  1byte  4byte       4byte      4byte     4byte
-----------------------------------------------------------
| 0x20 | 0x0A | SLPIT FL | SLPIT FR | SLPIT RL | SLPIT RR |
-----------------------------------------------------------

FLIGTH_CONTROLLER_ID_DATA_REAR
1byte  1byte  4byte 4byte 4byte 4byte
-----------------------------------------
| 0x20 | 0x0C | P   | I   | D   | SLPIT |
-----------------------------------------

FLIGTH_CONTROLLER_ID_DATA_FRONT
1byte  1byte  4byte 4byte 4byte 4byte
-----------------------------------------
| 0x20 | 0x0C | P   | I   | D   | SLPIT |
-----------------------------------------

*/

/* Typedefs --------------------------------------------------------------------------------------*/

/* Private values --------------------------------------------------------------------------------*/

/* Private functions declaration -----------------------------------------------------------------*/

/* Private functions -----------------------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------------------------*/

/**
 * @}
 */

/************************* (C) COPYRIGHT ****** END OF FILE ***************************************/
