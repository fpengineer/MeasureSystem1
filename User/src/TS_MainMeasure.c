/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Main measure

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

void vTask_MainMeasure( void *pvParameters )
{
    extern QueueHandle_t xQueue_MainMeasure;
    extern QueueHandle_t xQueue_Terminal;
    extern QueueHandle_t xQueue_HwSPI2_rx;
    extern QueueHandle_t xQueue_HwSPI2_tx;
    HwSPI2QueueData_t HwSPI2QueueData_rx;
    HwSPI2QueueData_t HwSPI2QueueData_tx;
    MainMeasureQueueData_t MainMeasureQueueData_rx;
    MainMeasureQueueData_t MainMeasureQueueData_tx;

    sprintf ( tempString, "vTask_MainMeasure - Run\n\r");
    xQueueSend( xQueue_Terminal, &tempString, NULL );
  
    
    
	while (1)
	{
        xQueueReceive( xQueue_MainMeasure, &MainMeasureQueueData_rx, portMAX_DELAY );

        switch( MainMeasureQueueData_rx.stateMainMeasure )
        {
            case MEASURE_WAIT:
            {
                break;
            }

            case MEASURE_RUN:
            {
                break;
            }

            case MEASURE_STOP:
            {
                break;
            }                

            case MEASURE_TACT: 
            {
                break;
            }

            case MEASURE_IDLE:
            {
                break;
            }
            
            default:
            {
                break;
            }
        }
    }
}


/* End of file */
