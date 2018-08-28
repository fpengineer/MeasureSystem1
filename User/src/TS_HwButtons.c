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
#include "projectDefs.h"


#define BUTTON_HANDLER_ALLOWED              1
#define BUTTON_HANDLER_FORBIDDEN            0  


#define BUTTON_CONTACT_RATTLING_FILTER_MS   25  

enum Buttons { 
    BUTTON_START_PRESSED, 
    BUTTON_STOP_PRESSED, 
    BUTTON_MODE_PRESSED, 
    BUTTON_MENU1_PRESSED, 
    BUTTON_MENU2_PRESSED, 
    BUTTON_MENU3_PRESSED, 
    BUTTON_MENU4_PRESSED, 
    BUTTON_ENCODER_PRESSED, 
    BUTTON_ENCODER_CLOCKWISE_ROTATED, 
    BUTTON_ENCODER_COUNTERCLOCKWISE_ROTATED, 
    BUTTON_IDLE
};

/*
struct ButtonsState{
    GPIO_PinState stateStartButton;
    GPIO_PinState stateStopButton;
    GPIO_PinState stateEncoderButton;
    GPIO_PinState stateModeButton;
    GPIO_PinState stateMenu1Button;
    GPIO_PinState stateMenu2Button;
    GPIO_PinState stateMenu3Button;
    GPIO_PinState stateMenu4Button;
};
*/


// Declare private functions
static void HwButtons_Init(void);
static void WaitButtonPressed( void );
static void WaitAllButtonsReleased( void );
static enum Buttons GetButtonPressed( void );




static char tempString[100] = {""};

void vTask_HwButtons( void *pvParameters )
{
//    extern QueueHandle_t xQueue_HwButtons;
    extern QueueHandle_t xQueue_Terminal;
//    HwButtonsQueueData_t HwButtonsQueueData;



    

    HwButtons_Init();    

	while (1)
	{
        WaitButtonPressed();

        switch( GetButtonPressed() )
        {
            case BUTTON_START_PRESSED:
            {
                vTaskDelay( BUTTON_CONTACT_RATTLING_FILTER_MS );

                if ( !HAL_GPIO_ReadPin(PORT_START_BUTTON, GPIO_START_BUTTON) )
                {
                    sprintf ( tempString, "vTask_HwButtons - BUTTON_START_PRESSED\n\r" );
                    xQueueSend( xQueue_Terminal, &tempString, NULL );
                }
                break;
            }

            case BUTTON_STOP_PRESSED:
            {
                vTaskDelay( BUTTON_CONTACT_RATTLING_FILTER_MS );

                if ( !HAL_GPIO_ReadPin(PORT_STOP_BUTTON, GPIO_STOP_BUTTON) )
                {
                    sprintf ( tempString, "vTask_HwButtons - BUTTON_STOP_PRESSED\n\r" );
                    xQueueSend( xQueue_Terminal, &tempString, NULL );
                }
                break;
            }

            case BUTTON_ENCODER_PRESSED:
            {
                vTaskDelay( BUTTON_CONTACT_RATTLING_FILTER_MS );

                if ( !HAL_GPIO_ReadPin(PORT_ENCODER_BUTTON, GPIO_ENCODER_BUTTON) )
                {
                    sprintf ( tempString, "vTask_HwButtons - BUTTON_ENCODER_PRESSED\n\r" );
                    xQueueSend( xQueue_Terminal, &tempString, NULL );
                }
                break;
            }

            case BUTTON_MODE_PRESSED:
            {
                vTaskDelay( BUTTON_CONTACT_RATTLING_FILTER_MS );

                if ( !HAL_GPIO_ReadPin(PORT_MODE_BUTTON, GPIO_MODE_BUTTON) )
                {
                    sprintf ( tempString, "vTask_HwButtons - BUTTON_MODE_PRESSED\n\r" );
                    xQueueSend( xQueue_Terminal, &tempString, NULL );
                }
                break;
            }

            case BUTTON_MENU1_PRESSED:
            {
                vTaskDelay( BUTTON_CONTACT_RATTLING_FILTER_MS );

                if ( !HAL_GPIO_ReadPin(PORT_MENUX_BUTTON, GPIO_MENU1_BUTTON) )
                {
                    sprintf ( tempString, "vTask_HwButtons - BUTTON_MENU1_PRESSED\n\r" );
                    xQueueSend( xQueue_Terminal, &tempString, NULL );
                }
                break;
            }

            case BUTTON_MENU2_PRESSED:
            {
                vTaskDelay( BUTTON_CONTACT_RATTLING_FILTER_MS );

                if ( !HAL_GPIO_ReadPin(PORT_MENUX_BUTTON, GPIO_MENU2_BUTTON) )
                {
                    sprintf ( tempString, "vTask_HwButtons - BUTTON_MENU2_PRESSED\n\r" );
                    xQueueSend( xQueue_Terminal, &tempString, NULL );
                }
                break;
            }

            case BUTTON_MENU3_PRESSED:
            {
                vTaskDelay( BUTTON_CONTACT_RATTLING_FILTER_MS );

                if ( !HAL_GPIO_ReadPin(PORT_MENUX_BUTTON, GPIO_MENU3_BUTTON) )
                {
                    sprintf ( tempString, "vTask_HwButtons - BUTTON_MENU3_PRESSED\n\r" );
                    xQueueSend( xQueue_Terminal, &tempString, NULL );
                }
                break;
            }

            case BUTTON_MENU4_PRESSED:
            {
                vTaskDelay( BUTTON_CONTACT_RATTLING_FILTER_MS );

                if ( !HAL_GPIO_ReadPin(PORT_MENUX_BUTTON, GPIO_MENU4_BUTTON) )
                {
                    sprintf ( tempString, "vTask_HwButtons - BUTTON_MENU4_PRESSED\n\r" );
                    xQueueSend( xQueue_Terminal, &tempString, NULL );
                }
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

        WaitAllButtonsReleased();
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

//    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 15, 0);
//    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}




//*************************************************
//
// Private function
//
// Wait until any button pressed
//
//*************************************************
static void WaitButtonPressed( void )
{
    while ( HAL_GPIO_ReadPin( PORT_START_BUTTON, GPIO_START_BUTTON )     &&
            HAL_GPIO_ReadPin( PORT_STOP_BUTTON, GPIO_STOP_BUTTON )       &&
            HAL_GPIO_ReadPin( PORT_ENCODER_BUTTON, GPIO_ENCODER_BUTTON ) &&
            HAL_GPIO_ReadPin( PORT_MODE_BUTTON, GPIO_MODE_BUTTON )       &&
            HAL_GPIO_ReadPin( PORT_MENUX_BUTTON, GPIO_MENU1_BUTTON )     &&
            HAL_GPIO_ReadPin( PORT_MENUX_BUTTON, GPIO_MENU2_BUTTON )     &&
            HAL_GPIO_ReadPin( PORT_MENUX_BUTTON, GPIO_MENU3_BUTTON )     &&
            HAL_GPIO_ReadPin( PORT_MENUX_BUTTON, GPIO_MENU4_BUTTON ) )
    {;}
}


//*************************************************
//
// Private function
//
// Wait until all buttons released
//
//*************************************************
static void WaitAllButtonsReleased( void )
{
    while ( !( HAL_GPIO_ReadPin( PORT_START_BUTTON, GPIO_START_BUTTON )     &&
               HAL_GPIO_ReadPin( PORT_STOP_BUTTON, GPIO_STOP_BUTTON )       &&
               HAL_GPIO_ReadPin( PORT_ENCODER_BUTTON, GPIO_ENCODER_BUTTON ) &&
               HAL_GPIO_ReadPin( PORT_MODE_BUTTON, GPIO_MODE_BUTTON )       &&
               HAL_GPIO_ReadPin( PORT_MENUX_BUTTON, GPIO_MENU1_BUTTON )     &&
               HAL_GPIO_ReadPin( PORT_MENUX_BUTTON, GPIO_MENU2_BUTTON )     &&
               HAL_GPIO_ReadPin( PORT_MENUX_BUTTON, GPIO_MENU3_BUTTON )     &&
               HAL_GPIO_ReadPin( PORT_MENUX_BUTTON, GPIO_MENU4_BUTTON ) ) )
    {;}
}

//*************************************************
//
// Private function
//
// Rturn button that has been pressed
//
//*************************************************
static enum Buttons GetButtonPressed( void )
{
    if ( !HAL_GPIO_ReadPin(PORT_START_BUTTON, GPIO_START_BUTTON) ){ return BUTTON_START_PRESSED; }
    if ( !HAL_GPIO_ReadPin(PORT_STOP_BUTTON, GPIO_STOP_BUTTON) ){ return BUTTON_STOP_PRESSED; }
    if ( !HAL_GPIO_ReadPin(PORT_ENCODER_BUTTON, GPIO_ENCODER_BUTTON) ){ return BUTTON_ENCODER_PRESSED; }
    if ( !HAL_GPIO_ReadPin(PORT_MODE_BUTTON, GPIO_MODE_BUTTON) ){ return BUTTON_MODE_PRESSED; }
    if ( !HAL_GPIO_ReadPin(PORT_MODE_BUTTON, GPIO_MODE_BUTTON) ){ return BUTTON_MODE_PRESSED; }
    if ( !HAL_GPIO_ReadPin(PORT_MENUX_BUTTON, GPIO_MENU1_BUTTON) ){ return BUTTON_MENU1_PRESSED; }
    if ( !HAL_GPIO_ReadPin(PORT_MENUX_BUTTON, GPIO_MENU2_BUTTON) ){ return BUTTON_MENU2_PRESSED; }
    if ( !HAL_GPIO_ReadPin(PORT_MENUX_BUTTON, GPIO_MENU3_BUTTON) ){ return BUTTON_MENU3_PRESSED; }
    if ( !HAL_GPIO_ReadPin(PORT_MENUX_BUTTON, GPIO_MENU4_BUTTON) ){ return BUTTON_MENU4_PRESSED; }
    return BUTTON_IDLE;
}


/* End of file */
