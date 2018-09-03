/*****************************************************************************************************

    Author: Filipp Popov

    Overview: DAC AD5620 functions header

*******************************************************************************************************/
#ifndef _DAC_AD5620_H_
#define _DAC_AD5620_H_

#include <stdint.h>

#define AD5620_OPERATING_MODE_NORMAL                   0x0000
#define AD5620_OPERATING_MODE_POWER_DOWN_10K_TO_GND    0x4000
#define AD5620_OPERATING_MODE_POWER_DOWN_100K_TO_GND   0x8000
#define AD5620_OPERATING_MODE_POWER_DOWN_THREE_STATE   0xC000

#define AD5620_MAX_VALUE        4095

#define AD5620_12_BIT_COUNTS    4096.0f

#define HV_LOW_LIMIT_V            32.01f
#define HV_HIGH_LIMIT_V           250.01f

#define HV_LOW_LIMIT_DAC          478.0f
#define HV_HIGH_LIMIT_DAC         3952.0f

#define HV_CALIBRATION_SLOPE      0.999f
#define HV_CALIBRATION_OFFSET     2.2f


uint16_t HVSupply_CalculateDAC( float value );

#endif /* _DAC_AD5620_H_ */
/* End of file */
