/**
 ***********************************************************************************************************************************
 * @file    ieee754.c
 * @author  jnieto
 * @version V1.0.0
 * @date    08/04/2021
 * @brief   Standar IEEE 754 Floating-Point Representation
 * @par
 *  COPYRIGHT NOTICE: (c) 2021 Power Electronics.
 *  All rights reserved
 ***********************************************************************************************************************************
 *
 * @addtogroup RACK_IEEE754
 * @{
 *
 */
 
/* Includes ***********************************************************************************************************************/
#include "hdwr/ieee754.h"
#include <stdio.h>
#include <stdint.h>

/* Defines ************************************************************************************************************************/
#define NTH_BIT(b, n) ((b >> n) & 0x1)

#define BYTE_TO_BIN(b)    (( b & 0x80 ) ) |\
                          (( b & 0x40 ) ) |\
                          (( b & 0x20 ) ) |\
                          (( b & 0x10 ) ) |\
                          (( b & 0x08 ) ) |\
                          (( b & 0x04 ) ) |\
                          (( b & 0x02 ) ) |\
                           ( b & 0x01 )

#define MANTISSA_TO_BIN(b)  ((  b & 0x400000) ) |\
                            (( b & 0x200000 ) ) |\
                            (( b & 0x100000 ) ) |\
                            (( b & 0x80000  ) ) |\
                            (( b & 0x40000  ) ) |\
                            (( b & 0x20000  ) ) |\
                            (( b & 0x10000  ) ) |\
                            (( b & 0x8000   ) ) |\
                            (( b & 0x4000   ) ) |\
                            (( b & 0x2000   ) ) |\
                            (( b & 0x1000   ) ) |\
                            (( b & 0x800    ) ) |\
                            (( b & 0x400    ) ) |\
                            (( b & 0x200    ) ) |\
                            (( b & 0x100    ) ) |\
                            (( b & 0x80     ) ) |\
                            (( b & 0x40     ) ) |\
                            (( b & 0x20     ) ) |\
                            (( b & 0x10     ) ) |\
                            (( b & 0x08     ) ) |\
                            (( b & 0x04     ) ) |\
                            (( b & 0x02     ) ) |\
                             ( b & 0x01     )

/* Private Variables **************************************************************************************************************/
typedef union UnFloatingPointIEEE754
    {
     struct
        {
        unsigned int mantissa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;
        } raw;   
    float f;  
} UFloatingPointIEEE754;

/* Private Prototypes *************************************************************************************************************/
uint32_t pack754_32 ( float *f )
{
  UFloatingPointIEEE754 ieee754;
  uint32_t    floatingToIntValue = 0;
  ieee754.f = *f;
 
  floatingToIntValue = (((NTH_BIT(ieee754.raw.sign, 0) << 8) | (BYTE_TO_BIN(ieee754.raw.exponent)))  << 23 ) | 
                         MANTISSA_TO_BIN(ieee754.raw.mantissa);
 
  return floatingToIntValue;
}

//--------------------------------------------------------------------------------------------------
 float unpack754_32( uint32_t *floatingToIntValue )
 {
   UFloatingPointIEEE754 ieee754 = {0};    
   unsigned int mantissa = 0;
   unsigned int exponent = 0 ;
   unsigned int sign = 0;    
   
   sign  = NTH_BIT(*floatingToIntValue, 31);
  
   for( int ix=0; ix<8; ix++)
  {
        exponent = (exponent | (NTH_BIT(*floatingToIntValue, (30-ix))))<<1;
  }
   exponent = exponent>>1;
  
   for( int ix=0; ix<23; ix++)
   {
        mantissa = (mantissa | (NTH_BIT(*floatingToIntValue, (22-ix))))<<1;
   }
   mantissa = mantissa >> 1;    
   
   ieee754.raw.sign = sign;
   ieee754.raw.exponent = exponent;
   ieee754.raw.mantissa = mantissa;

   return ieee754.f;
 }