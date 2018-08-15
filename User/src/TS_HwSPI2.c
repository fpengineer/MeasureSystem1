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
#include "Relay.h"


// Define macroses for CS pin for relay, leds, ADC, DAC
#define RELAY_CS_0()               HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET)
#define RELAY_CS_1()               HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET)

#define LEDS_CS_0()                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET)
#define LEDS_CS_1()                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET)

#define ADC_CS_0()                 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET)
#define ADC_CS_1()                 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET)

#define DAC_CS_0()                 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET)
#define DAC_CS_1()                 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)


struct ledData {
    uint8_t ledGood;
    uint8_t ledBad;
    uint8_t ledContact;
};


// Declare private functions
static void HwSPI2_Init(void);
static void HwSPI2_SendRelay(uint8_t *relayField, uint8_t len);
static uint16_t HwSPI2_GetSingleADC(void);



// Declare private variables
static char tempString[100] = {""};
//static char relayList[100] = {""};
//static struct ledData ledData;
static GPIO_InitTypeDef GPIO_InitStructure; 
static SPI_HandleTypeDef SPI_Handle;
static uint8_t relayField[RELAY_FIELD_LENGTH];

// Task
void vTask_HwSPI2( void *pvParameters )
{
    extern QueueHandle_t xQueue_Terminal;
    extern QueueHandle_t xQueue_HwSPI2_rx;
    extern QueueHandle_t xQueue_HwSPI2_tx;
    HwSPI2QueueData_t HwSPI2QueueData_rx;
    HwSPI2QueueData_t HwSPI2QueueData_tx;

    
    HwSPI2_Init();
    
    RELAY_CS_1();
    LEDS_CS_1();
    ADC_CS_1();
    DAC_CS_1();

    HwSPI2QueueData_rx.stateHwSPI2 = HW_SPI2_IDLE;

//    ledData.ledGood = 0x00;
//    ledData.ledBad = 0x00;
//    ledData.ledContact = 0x00;


    RelayClearAll(relayField, RELAY_FIELD_LENGTH);
    HwSPI2_SendRelay(relayField, RELAY_FIELD_LENGTH);

//    xQueueSend( xQueue_Terminal, "vTask_HwSPI2 - Run\r\n", NULL );
    while( 1 )
	{
        xQueueReceive( xQueue_HwSPI2_rx, &HwSPI2QueueData_rx, portMAX_DELAY );

        switch( HwSPI2QueueData_rx.stateHwSPI2 )
        {
            case HW_SPI2_RELAY_SET:
            {
                sprintf(tempString, "HwSPI2QueueData_rx.relayList - %s\r\n", HwSPI2QueueData_rx.relayList);
                xQueueSend( xQueue_Terminal, &tempString, NULL );

                RelaySet(relayField, HwSPI2QueueData_rx.relayList);
                
                sprintf(tempString, "relayField[0] - 0x%02x\r"
                                    "relayField[1] - 0x%02x\r"
                                    "relayField[2] - 0x%02x\r"
                                    "relayField[3] - 0x%02x\r"
                                    "relayField[4] - 0x%02x\r\n",
                                    relayField[0],
                                    relayField[1],
                                    relayField[2],
                                    relayField[3],
                                    relayField[4]);
                xQueueSend( xQueue_Terminal, &tempString, NULL );

                RELAY_CS_0();
                HwSPI2_SendRelay(relayField, RELAY_FIELD_LENGTH);
                RELAY_CS_1();
                break;
            }
 
            case HW_SPI2_RELAY_CLEAR:
            {
                sprintf(tempString, "HwSPI2QueueData_rx.relayList - %s\r\n", HwSPI2QueueData_rx.relayList);
                xQueueSend( xQueue_Terminal, &tempString, NULL );

                RelayClear(relayField, HwSPI2QueueData_rx.relayList);

                sprintf(tempString, "relayField[0] - 0x%02x\r"
                                    "relayField[1] - 0x%02x\r"
                                    "relayField[2] - 0x%02x\r"
                                    "relayField[3] - 0x%02x\r"
                                    "relayField[4] - 0x%02x\r\n",
                                    relayField[0],
                                    relayField[1],
                                    relayField[2],
                                    relayField[3],
                                    relayField[4]);
                xQueueSend( xQueue_Terminal, &tempString, NULL );

                RELAY_CS_0();
                HwSPI2_SendRelay(relayField, RELAY_FIELD_LENGTH);
                RELAY_CS_1();
                break;
            }

            case HW_SPI2_RELAY_CLEAR_ALL:
            {
                RelayClearAll(relayField, RELAY_FIELD_LENGTH);

                sprintf(tempString, "relayField[0] - 0x%02x\r"
                                    "relayField[1] - 0x%02x\r"
                                    "relayField[2] - 0x%02x\r"
                                    "relayField[3] - 0x%02x\r"
                                    "relayField[4] - 0x%02x\r\n",
                                    relayField[0],
                                    relayField[1],
                                    relayField[2],
                                    relayField[3],
                                    relayField[4]);
                xQueueSend( xQueue_Terminal, &tempString, NULL );

                RELAY_CS_0();
                HwSPI2_SendRelay(relayField, RELAY_FIELD_LENGTH);
                RELAY_CS_1();
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

            case HW_SPI2_ADC_GET:
            {
                ADC_CS_0();
                HwSPI2QueueData_tx.dataADC = HwSPI2_GetSingleADC();
                ADC_CS_1();

                HwSPI2QueueData_tx.stateHwSPI2 = HwSPI2QueueData_rx.stateHwSPI2;
                xQueueSend( xQueue_HwSPI2_tx, &HwSPI2QueueData_tx, NULL );
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

//*************************************************
//
// Private function
//
// Initialize hardware for current task.
//
//*************************************************
static void HwSPI2_Init(void)
{
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
}



//*************************************************
//
// Private function
//
// Send relay field
//
//*************************************************
static void HwSPI2_SendRelay(uint8_t *relayField, uint8_t len)
{
    int32_t i = 0;

    for (i = (len - 1); i >= 0; i--)
    {
        HAL_SPI_Transmit(&SPI_Handle, &relayField[i], 1, 1000);
    }
}




//*************************************************
//
// Private function
//
// Get single ADC
//
//*************************************************
static uint16_t HwSPI2_GetSingleADC(void)
{
//    int32_t i = 0;
    uint8_t temp_tx = 0xFF;
    uint8_t temp_rx[2] = { 0x00, 0x00};
    
    HAL_SPI_Transmit(&SPI_Handle, &temp_tx, 1, 1000);
    HAL_SPI_Receive(&SPI_Handle, &temp_rx[1], 1, 1000);

    HAL_SPI_Transmit(&SPI_Handle, &temp_tx, 1, 1000);
    HAL_SPI_Receive(&SPI_Handle, &temp_rx[0], 1, 1000);
    return ((uint16_t)temp_rx[1] << 8) | ((uint16_t)temp_rx[0]);
}

/* End of file */
