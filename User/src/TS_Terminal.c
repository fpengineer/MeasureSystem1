/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Terminal

*******************************************************************************************************/
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Include core modules */
#include "stm32f2xx.h"
/* Include my libraries here */

static char tempString[500] = {""}; 
//char* tempString2[20] = {""};
    
void vTask_Terminal( void *pvParameters )
{
    extern QueueHandle_t xQueue_Terminal;
    GPIO_InitTypeDef GPIO_InitStructure; 
    UART_HandleTypeDef UART_HandleStructure;    

    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_USART3_CLK_ENABLE();

/* Initialize USART3, TX: PD8 */
    GPIO_InitStructure.Pin   = GPIO_PIN_8;
    GPIO_InitStructure.Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Pull  = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStructure.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);

/* Initialize USART3, RX: PD9 */
// Not needed yet
    

    UART_HandleStructure.Instance = USART3;
    UART_HandleStructure.Init.BaudRate = 115200;
    UART_HandleStructure.Init.WordLength = UART_WORDLENGTH_8B;
    UART_HandleStructure.Init.StopBits = UART_STOPBITS_1;
    UART_HandleStructure.Init.Parity = UART_PARITY_NONE;
    UART_HandleStructure.Init.Mode = UART_MODE_TX;
    UART_HandleStructure.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    UART_HandleStructure.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&UART_HandleStructure);
    
	while( 1 )
	{
        xQueueReceive( xQueue_Terminal, &tempString, portMAX_DELAY );

        /* Send to USART */
        HAL_UART_Transmit(&UART_HandleStructure, (uint8_t *)tempString, (uint16_t)strlen(tempString), 1000);
	}
}


/* End of file */
