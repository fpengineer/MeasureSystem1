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
    extern QueueHandle_t xQueue_ICMechanic_rx;
    HwSPI2QueueData_t HwSPI2QueueData_rx;
    HwSPI2QueueData_t HwSPI2QueueData_tx;
    ICMechanicQueueData_t ICMechanicQueueData_rx;
    int i = 0;
    float dacValue;
    
    xQueueSend( xQueue_Terminal, "vTask_Debug - Run\r\n", NULL );

    
    vTaskDelay(1000);




    while (1)
	{
/*      Contact testing
        ICMechanicQueueData_rx.stateICMechanic = IC_MECHANIC_CONTACT_ON;
    xQueueSend( xQueue_ICMechanic_rx, &ICMechanicQueueData_rx, NULL );
    vTaskDelay(500);

        ICMechanicQueueData_rx.stateICMechanic = IC_MECHANIC_CONTACT_OFF;
    xQueueSend( xQueue_ICMechanic_rx, &ICMechanicQueueData_rx, NULL );
    vTaskDelay(500);
*/

/*  Sorting testing        
        ICMechanicQueueData_rx.stateICMechanic = IC_MECHANIC_SORTING_GOOD;
    xQueueSend( xQueue_ICMechanic_rx, &ICMechanicQueueData_rx, NULL );
    vTaskDelay(2000);
        
        ICMechanicQueueData_rx.stateICMechanic = IC_MECHANIC_SORTING_BAD;
    xQueueSend( xQueue_ICMechanic_rx, &ICMechanicQueueData_rx, NULL );
    vTaskDelay(2000);
*/        
        
/*  IC unload single testing        
    ICMechanicQueueData_rx.stateICMechanic = IC_MECHANIC_UNLOAD_SINGLE;
    xQueueSend( xQueue_ICMechanic_rx, &ICMechanicQueueData_rx, NULL );
    vTaskDelay(5000);

        // Hold down not working
*/        
        
        
/*  Vibration testing
        ICMechanicQueueData_rx.stateICMechanic = IC_MECHANIC_VIBRATION_ON;
    xQueueSend( xQueue_ICMechanic_rx, &ICMechanicQueueData_rx, NULL );
    vTaskDelay(300);

    ICMechanicQueueData_rx.stateICMechanic = IC_MECHANIC_VIBRATION_OFF;
    xQueueSend( xQueue_ICMechanic_rx, &ICMechanicQueueData_rx, NULL );
    vTaskDelay(2000);
*/
    }
}



/* End of file */
