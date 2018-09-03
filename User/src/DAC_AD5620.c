/*****************************************************************************************************

    Author: Filipp Popov

    Overview: DAC. Interface with ADC AD5620

*******************************************************************************************************/
#include <stdint.h>
#include <math.h> 
#include "DAC_AD5620.h" 


uint16_t HVSupply_CalculateDAC( float value )
{
    int32_t temp = 0;

    value = HV_CALIBRATION_SLOPE * value + HV_CALIBRATION_OFFSET;
    
    temp = (int32_t)( ( ( value - HV_LOW_LIMIT_V ) /
                      ( ( HV_HIGH_LIMIT_V - HV_LOW_LIMIT_V ) / ( HV_HIGH_LIMIT_DAC - HV_LOW_LIMIT_DAC ) ) ) + 
                          HV_LOW_LIMIT_DAC );

    if( temp >= ( AD5620_MAX_VALUE + 1 ) )
    {
        temp = AD5620_MAX_VALUE;
    }
    else if( temp < 0 )
    {
        temp = 0;
    }
    
    return (uint16_t)( temp << 1 );
}

/* End of file */
