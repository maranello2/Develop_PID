/**
 ***********************************************************************************************************************************
 * @file    ieee754.h
 * @author  jnieto
 * @version V1.0.0
 * @date    22/03/2021
 * @brief   Standar IEEE 754 Floating-Point Representation
 * @par
 *  COPYRIGHT NOTICE: (c) 2021 Power Electronics.
 *  All rights reserved
  **********************************************************************************************************************************
 * @defgroup RACK_IEEE754
 * @{
 * @brief   RACK IEEE754
 * @details A real-valued number is represented in a floating-point format as:
 *                   (-1)Sign × Significand × BaseExponent
 * Where:
 * 
 *     Sign is 0 for positive values, 1 for negative values.
 *     Significand is a real number, composed as integer.fraction. (Also known as "mantissa".)
 *     Base is an integer value, presumably the numeric base. Typically either 10 (for people) or 2 (for computers)
 * (or 16 for some IBM computers).
 *     Exponent is an integer value.
 * Soruce: https://montcs.bloomu.edu/Information/LowLevel/IEEE-754.html#754
 */
 
#ifndef IEEE_754_H
#define IEEE_754_H

#include <stdint.h>

uint32_t pack754_32 ( float *f );

float unpack754_32( uint32_t *float_to_int );


#endif
/**
 * @}
 */

/************************* (C) COPYRIGHT Power Electronics *****END OF FILE****/
