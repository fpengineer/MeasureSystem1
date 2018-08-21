/*****************************************************************************************************

    Author: Filipp Popov

    Overview: DAC. Interface with ADC AD5620

*******************************************************************************************************/
#include <stdint.h>
#include <math.h> 
#include "DAC_AD5620.h" 


uint16_t DAC_AD5620_CalculateDAC( float value, float range )
{
    int32_t temp = 0;
    
    temp = (int32_t) ( roundf( ( value * AD5620_12_BIT_COUNTS ) / range ) );

    if( temp >= ( AD5620_MAX_VALUE + 1 ) )
    {
        temp = AD5620_MAX_VALUE;
    }
    else if( temp < 0 )
    {
        temp = 0;
    }
    
    return (uint16_t) temp;
}

/* End of file */
