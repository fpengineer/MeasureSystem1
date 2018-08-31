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
    
    xQueueSend( xQueue_Terminal, "vTask_Debug - Run\r\n", NULL );

/*
    xQueueSend( xQueue_Terminal, "vTask_Debug - Contact motor\r\n", NULL );

    for ( i = 0; i < 500; i++ )
    {
        HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_SET;
        sprintf ( HwSPI2QueueData_rx.relayList, "K28");
        xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );

        vTaskDelay(1000);

        HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_CLEAR;
        sprintf ( HwSPI2QueueData_rx.relayList, "K28");
        xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );

        vTaskDelay(1000);
    }
*/   
    
        vTaskDelay(1000);

    xQueueSend( xQueue_Terminal, "vTask_Debug - DAC\r\n", NULL );

        HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_DAC_SET;
     HwSPI2QueueData_rx.dataDAC = ((uint16_t)(( 200.0f - 32.01f ) / ( 218.0f / 3474.0f )) + 478 ) << 1 ;
//     HwSPI2QueueData_rx.dataDAC = 3952 << 1 ;
    xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );


    while (1)
	{

/*

        for ( i = 0; i < 4096; i++ )
    {
        HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_DAC_SET;
     HwSPI2QueueData_rx.dataDAC = i << 1;
    xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );

    vTaskDelay(1);
        //                sprintf(tempString, "i = %d\r", i);
//                xQueueSend( xQueue_Terminal, &tempString, NULL );

    }
*/

    }
      
    }



/* End of file */
