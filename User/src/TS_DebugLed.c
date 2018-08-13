/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Status LED

*******************************************************************************************************/
#include <stdio.h>
#include <string.h>

#include "stdint.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "TS_task.h"

#include "stm32f2xx.h"

void vTask_DebugLed( void *pvParameters )
{
    extern QueueHandle_t xQueue_DebugLed;
//    extern QueueHandle_t xQueue_Terminal;
    enum stateStatusLed stateStatusLed = STATUS_LED_FLASH;
    TickType_t timeout = 1;
    GPIO_InitTypeDef GPIO_InitStructure; 

    __HAL_RCC_GPIOE_CLK_ENABLE();
// Init LED gpio pin PE11
    GPIO_InitStructure.Pin   = GPIO_PIN_11;
    GPIO_InitStructure.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull  = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_MEDIUM;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStructure);

	while (1)
	{
        xQueueReceive(xQueue_DebugLed, &stateStatusLed, timeout );
        
        switch ((int32_t)stateStatusLed)
        {
            case STATUS_LED_ON:
                /* Enable Led */
                timeout = portMAX_DELAY;
                HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);
                break;
                
            case STATUS_LED_OFF:
                /* Disable Led */
                timeout = portMAX_DELAY;
                HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
                break;
                
            case STATUS_LED_FLASH:
                /* Toggle Led */
                timeout = 500 / portTICK_PERIOD_MS;
                HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_11);   
                break;
                
            default:
                break;
        }
    }
}


/* End of file */
