/**
*	Project: measure system of deviation of collector reverse current of transistors UFM1.450.060
 *
 *	This firmware is for Control Unit V1I0
 *
 *  Functionality of the firmware:
 *  - control mechanics of the measure system (contact motor, solenoids);
 *  - control relays on analog pcb;
 *  - handling IC fall sensor event;
 *  - control high voltage power supply for measurements;
 *  - indicate parameters and sttings on LCD display;
 *  - indicate contact goods on LED bar;
 *  - indicate sorting result on LED bar;
 *  - handling user button and encoder events;
 *  - perform measurement based on program with measurement settings (timings, HV supply values, npn/pnp structure etc.);
 *  - interface with SD card via SDIO interface;
 *  - read configs with measurement programs from SD card;
 *  - write statistic with measured values to SD card;
 *  - RTC for file system;
 *  - send srvice information, measure program info and statistic with measured values to terminal (RS-232);
 *
 *	@author		Filipp Popov
 *	@email		filip@land.ru
 *	@website	
 *	@ide		Keil uVision 5
 *	@packs		
 *	@stdperiph	
 */
#include <stdio.h>
#include <string.h>

/* Include core modules */
#include "stm32f2xx.h"

// Include FreeRTOS
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
//#include "semphr.h"

// Include application
#include "TS_task.h"
#include "TS_queue.h"
//#include "Config.h"
//#include "Measure.h"
#include "ClockOutMCO.h"

#define	ERROR_ACTION( CODE,POS )		do{}while( 0 )

TaskHandle_t xTask_Debug;
TaskHandle_t xTask_DebugLed;
//TaskHandle_t xTask_SDCardLed;
//TaskHandle_t xTask_StatusLed;
TaskHandle_t xTask_MainMeasure;
//TaskHandle_t xTask_FatFs;
TaskHandle_t xTask_Terminal;
TaskHandle_t xTask_HwSPI2;
//TaskHandle_t xTask_SystemTime;
TaskHandle_t xTask_Buttons;
//TaskHandle_t xTask_SDCardDetect;

QueueHandle_t xQueue_Debug;
QueueHandle_t xQueue_DebugLed;
//QueueHandle_t xQueue_SDCardLed;
//QueueHandle_t xQueue_StatusLed;
QueueHandle_t xQueue_MainMeasure;
//QueueHandle_t xQueue_FatFsIn;
//QueueHandle_t xQueue_FatFsOut;
QueueHandle_t xQueue_Terminal;
QueueHandle_t xQueue_HwSPI2_rx;
QueueHandle_t xQueue_HwSPI2_tx;
QueueHandle_t xQueue_HwButtons;
//QueueHandle_t xQueue_SystemTimeIn;
//QueueHandle_t xQueue_SystemTimeOut;

/* User Global Variables */    
//cfgMeasurePlan_t cfgMeasurePlan;
//cfgMeasureEnable_t cfgMeasureEnable;
//uint32_t cardReady = 0;
//uint32_t measureEnableFlag = 0;
//volatile uint32_t runButtonFlag = 0;    //1 - button pressed, 0 - button not pressed
//volatile uint32_t cardInsertState = 0;  //1 - card inserted, 0 - card not inserted

/*******************************************************************/
void vApplicationIdleHook( void )
{
}
/*******************************************************************/
void vApplicationMallocFailedHook( void )
{
    for( ;; );
}
/*******************************************************************/
void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
    ( void ) pcTaskName;
    ( void ) pxTask;
 
    for( ;; );
}
/*******************************************************************/
void vApplicationTickHook( void )
{
}
/*******************************************************************/    

int main(void) {
	SystemInit();

    OutputMCO();
    
	xQueue_DebugLed = xQueueCreate( 5, sizeof( uint8_t ) ); 
	xQueue_DebugLed = xQueueCreate( 5, sizeof( enum stateDebugLed ) ); 
//	xQueue_SDCardLed = xQueueCreate( 5, sizeof( enum stateSDCardLed ) ); 
//	xQueue_StatusLed = xQueueCreate( 5, sizeof( enum stateStatusLed ) ); 
	xQueue_MainMeasure = xQueueCreate( 5, sizeof( MainMeasureQueueData_t ) ); 
//	xQueue_FatFsIn = xQueueCreate( 10, sizeof( FatFsQueueData_t ) ); 
//	xQueue_FatFsOut = xQueueCreate( 10, sizeof( FatFsQueueData_t ) ); 
	xQueue_Terminal = xQueueCreate( 15, sizeof( char[500] ) ); 
	xQueue_HwSPI2_rx = xQueueCreate( 5, sizeof( HwSPI2QueueData_t ) ); 
	xQueue_HwSPI2_tx = xQueueCreate( 5, sizeof( HwSPI2QueueData_t ) ); 
	xQueue_HwButtons = xQueueCreate( 5, sizeof( HwButtonsQueueData_t ) ); 
//	xQueue_SystemTimeIn = xQueueCreate( 5, sizeof( SystemTimeQueueData_t ) ); 
//	xQueue_SystemTimeOut = xQueueCreate( 5, sizeof( SystemTimeQueueData_t ) ); 

#if 1
	if( pdTRUE != xTaskCreate(  vTask_Debug,
                                "Debug",
                                configMINIMAL_STACK_SIZE + 1000,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_DebugLed )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 1
	if( pdTRUE != xTaskCreate(  vTask_DebugLed,
                                "Debug Led",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_DebugLed )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 0
	if( pdTRUE != xTaskCreate(  vTask_SDCardLed,
                                "SD Card Led",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_SDCardLed )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 0
	if( pdTRUE != xTaskCreate(  vTask_StatusLed,
                                "Status Led",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_StatusLed )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 1
    if( pdTRUE != xTaskCreate(  vTask_MainMeasure,
                                "Main Measure",
                                configMINIMAL_STACK_SIZE + 5000,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_MainMeasure )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 0
    if( pdTRUE != xTaskCreate(  vTask_FatFs,
                                "FatFs",
                                configMINIMAL_STACK_SIZE + 2000,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_FatFs )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 1	
    if( pdTRUE != xTaskCreate(  vTask_Terminal,
                                "Terminal",
                                configMINIMAL_STACK_SIZE +500,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_Terminal )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 1	
    if( pdTRUE != xTaskCreate(  vTask_HwSPI2,
                                "HwSPI2",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwSPI2 )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 0
    if( pdTRUE != xTaskCreate(  vTask_SystemTime,
                                "System Time",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_SystemTime )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 1
    if( pdTRUE != xTaskCreate(  vTask_HwButtons,
                                "Run Button",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_Buttons )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 0
    if( pdTRUE != xTaskCreate(  vTask_SDCardDetect,
                                "SD Card Detect",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_SDCardDetect )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	

#endif
    xQueueSend( xQueue_Terminal, "*********   Unstability of Collector Current V1.0  *********\r\n", NULL );



	vTaskStartScheduler();

	while (1) {

	}
}
