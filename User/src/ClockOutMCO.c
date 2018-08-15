/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: 

*******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "stm32f2xx.h"

void OutputMCO() {

    HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_PLLCLK, RCC_MCODIV_1);

}



/* End of file */
