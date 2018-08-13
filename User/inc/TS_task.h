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
    SPI2_RELAY_ON,
    SPI2_RELAY_OFF,
    SPI2_RELAY_CLEAR_ALL,
    SPI2_LEDS_SORTING_SET,
    SPI2_LEDS_CONTACT_SET,
    SPI2_LEDS_SHIFT_DOWN,
    SPI2_LEDS_CLEAR_ALL,
    SPI2_HV_SUPPLY_SET,
    SPI2_CURRENT_MEASURE_GET,
    SPI2_IDLE 
};

enum stateMainMeasure { 
    MEASURE_WAIT, 
    MEASURE_RUN, 
    MEASURE_STOP, 
    MEASURE_TACT, 
    MEASURE_IDLE
};


void vTask_DebugLed(void *pvParameters);
//void vTask_SDCardLed(void *pvParameters);
//void vTask_StatusLed(void *pvParameters);
//void vTask_MainMeasure(void *pvParameters);
//void vTask_FatFs(void *pvParameters);
void vTask_Terminal(void *pvParameters);
void vTask_HwSPI2(void *pvParameters);
//void vTask_SystemTime(void *pvParameters);
//void vTask_RunButton(void *pvParameters);
//void vTask_SDCardDetect(void *pvParameters);

#endif /* _TS_TASK_H_ */
/* End of file */
