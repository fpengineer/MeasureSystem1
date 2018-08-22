/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Start Button Handler

*******************************************************************************************************/
#include <stdio.h>
#include <string.h>

#include "stdint.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Include core modules */
#include "stm32f2xx.h"

/* Include user modules */
#include "TS_task.h"
#include "TS_queue.h"


// Declare private functions
static void HwButtons_Init(void);


static char tempString[100] = {""};

void vTask_HwButtons( void *pvParameters )
{
    extern QueueHandle_t xQueue_HwButtons;
    extern QueueHandle_t xQueue_Terminal;
    HwButtonsQueueData_t HwButtonsQueueData;

    sprintf ( tempString, "vTask_HwButtons - Run\n\r");
    xQueueSend( xQueue_Terminal, &tempString, NULL );

    HwButtons_Init();    

	while (1)
	{
        xQueueReceive( xQueue_HwButtons, &HwButtonsQueueData, portMAX_DELAY );

        switch( HwButtonsQueueData.stateButtons )
        {
            case BUTTON_START_PRESSED:
            {
                sprintf ( tempString, "vTask_HwButtons - BUTTON_START_PRESSED\n\r");
                xQueueSend( xQueue_Terminal, &tempString, NULL );
                break;
            }

            case BUTTON_STOP_PRESSED:
            {
                break;
            }

            case BUTTON_MODE_PRESSED:
            {
                break;
            }

            case BUTTON_MENU1_PRESSED:
            {
                break;
            }

            case BUTTON_MENU2_PRESSED:
            {
                break;
            }

            case BUTTON_MENU3_PRESSED:
            {
                break;
            }

            case BUTTON_MENU4_PRESSED:
            {
                break;
            }

            case BUTTON_ENCODER_PRESSED:
            {
                break;
            }

            case BUTTON_ENCODER_CLOCKWISE_ROTATED:
            {
                break;
            }

            case BUTTON_ENCODER_COUNTERCLOCKWISE_ROTATED:
            {
                break;
            }

            case BUTTON_IDLE:
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


//*************************************************
//
// Private function
//
// Initialize hardware for current task.
//
//*************************************************
static void HwButtons_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; 

    __HAL_RCC_GPIOD_CLK_ENABLE();

/* Initialize Start Button: PD10 */
    GPIO_InitStructure.Pin   = GPIO_PIN_10;
    GPIO_InitStructure.Mode  = GPIO_MODE_IT_FALLING;
    GPIO_InitStructure.Pull  = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);

    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}


//*************************************************
//
// IRQ Handler
//
// EXTI [15:10] channels
//
//*************************************************
void EXTI15_10IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
}


//*************************************************
//
// IRQ Handler
//
// EXTI [15:10] channels
//
//*************************************************
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    extern QueueHandle_t xQueue_HwButtons;
    HwButtonsQueueData_t HwButtonsQueueData;

    HwButtonsQueueData.stateButtons = BUTTON_START_PRESSED;
    xQueueSendFromISR( xQueue_HwButtons, &HwButtonsQueueData, NULL );
}

/* End of file */
