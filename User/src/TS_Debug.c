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

//    xQueueSend( xQueue_Terminal, "vTask_Debug - Run\r\n", NULL );
    vTaskDelay(10);
    xQueueSend( xQueue_Terminal, "\rvTask_Debug - ******** 1 **********\r\r\n", NULL );
    vTaskDelay(1000);


    xQueueSend( xQueue_Terminal, "vTask_Debug - Set relay\r\n", NULL );
    HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_SET;
//    sprintf ( HwSPI2QueueData_rx.relayList, "K1, K2, K3, K8, K9, K10, K15, K16, R17");
    sprintf ( HwSPI2QueueData_rx.relayList, "K1, K2, K3, K8, K16, K24, K32");
    xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );


    vTaskDelay(10);
    xQueueSend( xQueue_Terminal, "\rvTask_Debug - ******** 2 **********\r\r\n", NULL );
    vTaskDelay(1000);


    xQueueSend( xQueue_Terminal, "vTask_Debug - Clear relay\r\n", NULL );
    HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_CLEAR;
    sprintf ( HwSPI2QueueData_rx.relayList, "K8, K16");
    xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );


    vTaskDelay(10);
    xQueueSend( xQueue_Terminal, "\rvTask_Debug - ******** 3 **********\r\r\n", NULL );
    vTaskDelay(1000);


    xQueueSend( xQueue_Terminal, "vTask_Debug - Clear all relay\r\n", NULL );
    HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_CLEAR_ALL;
//    sprintf ( HwSPI2QueueData_rx.relayList, "K4, K12");
    xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );



/*
    vTaskDelay(10);
    xQueueSend( xQueue_Terminal, "\rvTask_Debug - ******** 4 **********\r\r\n", NULL );
    vTaskDelay(1000);


    xQueueSend( xQueue_Terminal, "vTask_Debug - Clear all relay\r\n", NULL );
    HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_CLEAR_ALL;
//    sprintf ( HwSPI2QueueData_rx.relayList, "K4, K12");
    xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );

  */  
    
    
    
    
	while (1)
	{
        
    }
}


/* End of file */
