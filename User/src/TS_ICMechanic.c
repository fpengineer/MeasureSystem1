/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - IC Load/Unload

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

void vTask_ICMechanic( void *pvParameters )
{
    extern QueueHandle_t xQueue_Terminal;
    extern QueueHandle_t xQueue_HwSPI2_rx;
    extern QueueHandle_t xQueue_HwSPI2_tx;
    extern QueueHandle_t xQueue_ICMechanic_rx;
    HwSPI2QueueData_t HwSPI2QueueData_rx;
    HwSPI2QueueData_t HwSPI2QueueData_tx;
    ICMechanicQueueData_t ICMechanicQueueData_rx;
    
    xQueueSend( xQueue_Terminal, "vTask_ICMechanic - Run\r\n", NULL );

    while (1)
	{
        xQueueReceive( xQueue_ICMechanic_rx, &ICMechanicQueueData_rx, portMAX_DELAY );

        switch( ICMechanicQueueData_rx.stateICMechanic )
        {
            case IC_MECHANIC_LOAD:
            {
                HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_CLEAR;
                sprintf( HwSPI2QueueData_rx.relayList, HOLD_DOWN );
                xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );

                vTaskDelay( 30 );

                HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_CLEAR;
                sprintf( HwSPI2QueueData_rx.relayList, CONTACT_MOTOR );
                xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );

                vTaskDelay( 700 );

                HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_CLEAR;
                sprintf( HwSPI2QueueData_rx.relayList, HOLD_UP );
                xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );
                break;
            }

            case IC_MECHANIC_UNLOAD_SINGLE:
            {
                HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_CLEAR;
                sprintf( HwSPI2QueueData_rx.relayList, CONTACT_MOTOR );
                xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );

                vTaskDelay( 700 );

                HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_SET;
                sprintf( HwSPI2QueueData_rx.relayList, HOLD_UP );
                xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );

                vTaskDelay( 30 );

                HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_SET;
                sprintf( HwSPI2QueueData_rx.relayList, HOLD_DOWN );
                xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );

                vTaskDelay( 200 );

                HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_CLEAR;
                sprintf( HwSPI2QueueData_rx.relayList, HOLD_DOWN );
                xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );

                vTaskDelay( 30 );

                HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_CLEAR;
                sprintf( HwSPI2QueueData_rx.relayList, HOLD_UP );
                xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );

                break;
            }

            case IC_MECHANIC_UNLOAD_ALL:
            {
                HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_CLEAR;
                sprintf( HwSPI2QueueData_rx.relayList, CONTACT_MOTOR );
                xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );

                vTaskDelay( 700 );

                HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_CLEAR;
                sprintf( HwSPI2QueueData_rx.relayList, HOLD_UP );
                xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );

                vTaskDelay( 30 );

                HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_SET;
                sprintf( HwSPI2QueueData_rx.relayList, HOLD_DOWN );
                xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );

                vTaskDelay( 700 );

                HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_CLEAR;
                sprintf( HwSPI2QueueData_rx.relayList, HOLD_DOWN );
                xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );

                break;
            }                

            case IC_MECHANIC_VIBRATION_ON: 
            {
                HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_SET;
                sprintf( HwSPI2QueueData_rx.relayList, VIBRATION_MOTOR );
                xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );
                break;
            }

            case IC_MECHANIC_VIBRATION_OFF: 
            {
                HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_CLEAR;
                sprintf( HwSPI2QueueData_rx.relayList, VIBRATION_MOTOR );
                xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );
                break;
            }

            case IC_MECHANIC_CONTACT_ON: 
            {
                HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_SET;
                sprintf( HwSPI2QueueData_rx.relayList, CONTACT_MOTOR );
                xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );
                break;
            }

            case IC_MECHANIC_CONTACT_OFF: 
            {
                HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_CLEAR;
                sprintf( HwSPI2QueueData_rx.relayList, CONTACT_MOTOR );
                xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );
                break;
            }

            case IC_MECHANIC_SORTING_GOOD: 
            {
                HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_CLEAR;
                sprintf( HwSPI2QueueData_rx.relayList, SORTING_SHADE );
                xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );
                break;
            }

            case IC_MECHANIC_SORTING_BAD: 
            {
                HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_RELAY_SET;
                sprintf( HwSPI2QueueData_rx.relayList, SORTING_SHADE );
                xQueueSend( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, NULL );
                break;
            }

            case IC_MECHANIC_IDLE:
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
