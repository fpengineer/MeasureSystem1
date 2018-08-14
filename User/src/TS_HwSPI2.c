/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - HwSPI2

*******************************************************************************************************/
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Include core modules */
#include "stm32f2xx.h"
/* Include my libraries here */
#include "TS_task.h"
#include "TS_queue.h"


// Define macroses for CS pin for relay, leds, ADC, DAC
#define PORT_RELAY_CS_0()               HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET)
#define PORT_RELAY_CS_1()               HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET)

#define LEDS_CS_0()                     HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET)
#define LEDS_CS_1()                     HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET)

#define ADC_CS_0()                      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET)
#define ADC_CS_1()                      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET)

#define DAC_CS_0()                      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET)
#define DAC_CS_1()                      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)


void vTask_HwSPI2( void *pvParameters )
{
    extern QueueHandle_t xQueue_HwSPI2_rx;
    extern QueueHandle_t xQueue_HwSPI2_tx;

    HwSPI2QueueData_t HwSPI2QueueData_rx;
    HwSPI2QueueData_t HwSPI2QueueData_tx;
    GPIO_InitTypeDef GPIO_InitStructure; 
    SPI_HandleTypeDef SPI_Handle;
        
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_SPI2_CLK_ENABLE();

/* Initialize SPI2 SCK: PB13 */
    GPIO_InitStructure.Pin   = GPIO_PIN_13;
    GPIO_InitStructure.Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Pull  = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStructure.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

/* Initialize SPI2 MOSI: PB15 */
    GPIO_InitStructure.Pin   = GPIO_PIN_15;
    GPIO_InitStructure.Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Pull  = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStructure.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

/* Initialize SPI2 MISO: PB14 */
    GPIO_InitStructure.Pin   = GPIO_PIN_14;
    GPIO_InitStructure.Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Pull  = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStructure.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

/* Initialize SPI2 */
    SPI_Handle.Instance = SPI2;
    SPI_Handle.Init.Mode = SPI_MODE_MASTER;
    SPI_Handle.Init.Direction = SPI_DIRECTION_2LINES;
    SPI_Handle.Init.DataSize = SPI_DATASIZE_8BIT;
    SPI_Handle.Init.CLKPolarity = SPI_POLARITY_LOW;
    SPI_Handle.Init.CLKPhase = SPI_PHASE_1EDGE;
    SPI_Handle.Init.NSS = SPI_NSS_SOFT;
    SPI_Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    SPI_Handle.Init.FirstBit = SPI_FIRSTBIT_MSB;
    SPI_Handle.Init.TIMode = SPI_TIMODE_DISABLE;
    SPI_Handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    SPI_Handle.Init.CRCPolynomial = 10;
    HAL_SPI_Init(&SPI_Handle);
   
/* Initialize Realy CS: PB10 */
    GPIO_InitStructure.Pin   = GPIO_PIN_10;
    GPIO_InitStructure.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull  = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

/* Initialize LEDs CS: PC4 */
    GPIO_InitStructure.Pin   = GPIO_PIN_4;
    GPIO_InitStructure.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull  = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

/* Initialize ADC CS: PB11 */
    GPIO_InitStructure.Pin   = GPIO_PIN_11;
    GPIO_InitStructure.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull  = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

/* Initialize DAC CS: PB12 */
    GPIO_InitStructure.Pin   = GPIO_PIN_12;
    GPIO_InitStructure.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull  = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

    PORT_RELAY_CS_1();
    LEDS_CS_1();
    ADC_CS_1();
    DAC_CS_1();

    HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_IDLE;

    while( 1 )
	{
        xQueueReceive( xQueue_HwSPI2_rx, &xQueue_HwSPI2_rx, portMAX_DELAY );

        switch( HwSPI2QueueData_rx.stateHwSPI2 )
        {
            case HW_SPI2_RELAY_ON:
            {
                PORT_RELAY_CS_0();

                PORT_RELAY_CS_1();
                break;
            }
 
            case HW_SPI2_RELAY_OFF:
            {
                PORT_RELAY_CS_0();

                PORT_RELAY_CS_1();
                break;
            }

            case HW_SPI2_RELAY_CLEAR_ALL:
            {
                PORT_RELAY_CS_0();

                PORT_RELAY_CS_1();
                break;
            }

            case HW_SPI2_LEDS_SORTING_SET:
            {
                LEDS_CS_0();

                LEDS_CS_1();
                break;
            }

            case HW_SPI2_LEDS_CONTACT_SET:
            {
                LEDS_CS_0();

                LEDS_CS_1();
                break;
            }

            case HW_SPI2_LEDS_SHIFT_DOWN:
            {
                LEDS_CS_0();

                LEDS_CS_1();
                break;
            }

            case HW_SPI2_LEDS_CLEAR_ALL:
            {
                LEDS_CS_0();

                LEDS_CS_1();
                break;
            }

            case HW_SPI2_HV_SUPPLY_SET:
            {
                DAC_CS_0();

                DAC_CS_1();
                break;
            }

            case HW_SPI2_CURRENT_MEASURE_GET:
            {
                ADC_CS_0();

                ADC_CS_1();
                break;
            }

            case HW_SPI2_IDLE:
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
