/*****************************************************************************************************

    
    
    
    Author: Filipp Popov

    Overview: Project defines

*******************************************************************************************************/


#ifndef _PROJECT_DEFS_H_
#define _PROJECT_DEFS_H_

#include <stdint.h>
#include "stm32f2xx.h"

// Define MCU pins
// PORTD
#define PORT_START_BUTTON               GPIOD
#define GPIO_START_BUTTON               GPIO_PIN_10

#define PORT_STOP_BUTTON                GPIOD
#define GPIO_STOP_BUTTON                GPIO_PIN_11

#define PORT_ENCODER_BUTTON             GPIOD
#define GPIO_ENCODER_BUTTON             GPIO_PIN_14

#define PORT_SD_CARD_DETECT             GPIOD
#define GPIO_SD_CARD_DETECT             GPIO_PIN_15

// PORTE
#define PORT_MODE_BUTTON                GPIOE
#define GPIO_MODE_BUTTON                GPIO_PIN_10

// PORTA
#define PORT_MENUX_BUTTON               GPIOA
#define GPIO_MENU1_BUTTON               GPIO_PIN_12
#define GPIO_MENU2_BUTTON               GPIO_PIN_11
#define GPIO_MENU3_BUTTON               GPIO_PIN_10
#define GPIO_MENU4_BUTTON               GPIO_PIN_9


#endif /* _PROJECT_DEFS_H_ */
/* End of file */
