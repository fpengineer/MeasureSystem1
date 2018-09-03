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


#define DAC_VALUE       40.0f
xQueueSend( xQueue_Terminal, "vTask_Debug - DAC\r\n", NULL );


        dacValue = 0.999f * DAC_VALUE + 2.2f;
HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_DAC_SET;
     HwSPI2QueueData_rx.dataDAC = HVSupply_CalculateDAC( DAC_VALUE ) ;
//     HwSPI2QueueData_rx.dataDAC = ((uint16_t)(( dacValue - 32.01f ) / ( 218.0f / 3474.0f )) + 478 ) << 1 ;
//     HwSPI2QueueData_rx.dataDAC = 3952 << 1 ;
    xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );

        vTaskDelay(10000);

    while (1)
	{



        for ( i = 50; i < 260; i += 10 )
    {
//        dacValue = 0.999f * (float)i + 2.2f;
        HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_DAC_SET;
//     HwSPI2QueueData_rx.dataDAC = i << 1;
//     HwSPI2QueueData_rx.dataDAC = ((uint16_t)(( dacValue - 32.01f ) / ( 218.0f / 3474.0f )) + 478 ) << 1 ;
     HwSPI2QueueData_rx.dataDAC = HVSupply_CalculateDAC( dacValue ) ;
    xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );

    vTaskDelay(10000);
        //                sprintf(tempString, "i = %d\r", i);
//                xQueueSend( xQueue_Terminal, &tempString, NULL );

    }


    }
      
    }



/* End of file */
