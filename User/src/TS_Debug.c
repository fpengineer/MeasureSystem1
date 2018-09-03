/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Debug

*******************************************************************************************************/
#include <stdio.h>
#include <string.h>

#include "stdint.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "TS_task.h"
#include "TS_queue.h"

#include "DAC_AD5620.h"

static char tempString[100] = {""};

void vTask_Debug( void *pvParameters )
{
    extern QueueHandle_t xQueue_Debug;
    extern QueueHandle_t xQueue_Terminal;
    extern QueueHandle_t xQueue_HwSPI2_rx;
    extern QueueHandle_t xQueue_HwSPI2_tx;
    HwSPI2QueueData_t HwSPI2QueueData_rx;
    HwSPI2QueueData_t HwSPI2QueueData_tx;
    int i = 0;
    float dacValue;
    
    xQueueSend( xQueue_Terminal, "vTask_Debug - Run\r\n", NULL );

    
    vTaskDelay(1000);


    xQueueSend( xQueue_Terminal, "vTask_Debug - DAC\r\n", NULL );

    HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_DAC_SET;
    HwSPI2QueueData_rx.dataDAC = HVSupply_CalculateDAC( 40.0f ) ;
    xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );

    vTaskDelay(10000);

    while (1)
	{



        for ( i = 50; i < 260; i += 10 )
        {
            HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_DAC_SET;
            HwSPI2QueueData_rx.dataDAC = HVSupply_CalculateDAC( (float)i ) ;
            xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );

            vTaskDelay(10000);
        }
    }
}



/* End of file */
