/*****************************************************************************************************

    
    
    
    Author: Filipp Popov

    Overview: RTOS Task functions header

*******************************************************************************************************/


#ifndef _TS_TASK_H_
#define _TS_TASK_H_

#include <stdint.h>

enum stateSystemTime {
    SYSTEM_TIME_SET,
    SYSTEM_TIME_GET
};

enum stateDebugLed {
    DEBUG_LED_ON,
    DEBUG_LED_OFF,
    DEBUG_LED_FLASH
};

enum stateStatusLed {
    STATUS_LED_ON,
    STATUS_LED_OFF,
    STATUS_LED_FLASH
};

enum stateSDCardLed {
    SDCARD_LED_ON,
    SDCARD_LED_OFF,
    SDCARD_LED_FLASH
};

enum stateFatFs { 
    FATFS_INIT_SD_CARD,
    FATFS_DEINIT_SD_CARD,
    FATFS_CREATE_NEW_MEASUREMENT_FILE,
    FATFS_WRITE_DATA_TO_MEASUREMENT_FILE,
    FATFS_GET_CONFIG,
    FATFS_CHECK_CONFIG_FILE_EXIST,
    FATFS_IDLE 
};

enum stateHwSPI2 { 
    HW_SPI2_RELAY_SET,
    HW_SPI2_RELAY_CLEAR,
    HW_SPI2_RELAY_CLEAR_ALL,
    HW_SPI2_LEDS_SORTING_SET,
    HW_SPI2_LEDS_CONTACT_SET,
    HW_SPI2_LEDS_SHIFT_DOWN,
    HW_SPI2_LEDS_CLEAR_ALL,
    HW_SPI2_DAC_SET,
    HW_SPI2_ADC_GET,
    HW_SPI2_IDLE 
};

enum stateMainMeasure { 
    MEASURE_WAIT, 
    MEASURE_RUN, 
    MEASURE_STOP, 
    MEASURE_TACT, 
    MEASURE_IDLE
};

enum stateButtons { 
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


void vTask_Debug(void *pvParameters);
void vTask_DebugLed(void *pvParameters);
//void vTask_SDCardLed(void *pvParameters);
//void vTask_StatusLed(void *pvParameters);
void vTask_MainMeasure(void *pvParameters);
//void vTask_FatFs(void *pvParameters);
void vTask_Terminal(void *pvParameters);
void vTask_HwSPI2(void *pvParameters);
//void vTask_SystemTime(void *pvParameters);
void vTask_HwButtons(void *pvParameters);
//void vTask_SDCardDetect(void *pvParameters);

#endif /* _TS_TASK_H_ */
/* End of file */
