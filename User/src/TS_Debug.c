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

void vTask_Debug( void *pvParameters )
{
    extern QueueHandle_t xQueue_Debug;
    extern QueueHandle_t xQueue_Terminal;
    extern QueueHandle_t xQueue_HwSPI2_rx;
    HwSPI2QueueData_t HwSPI2QueueData_rx;

    xQueueSend( xQueue_Terminal, "vTask_Debug - Run\r\n", NULL );


    xQueueSend( xQueue_Terminal, "vTask_Debug - Set relay K1\r\n", NULL );
    HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_SET;
    HwSPI2QueueData_rx.relay = RELAY_K1;
    xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );

    vTaskDelay(10);
    xQueueSend( xQueue_Terminal, "\rvTask_Debug - delay 3000\r\r\n", NULL );
    vTaskDelay(3000);
    
    xQueueSend( xQueue_Terminal, "vTask_Debug - Set relay K2\r\n", NULL );
    HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_SET;
    HwSPI2QueueData_rx.relay = RELAY_K2;
    xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );
   
    
    
    
    
    
    
    
	while (1)
	{
        
    }
}


/* End of file */
