/*****************************************************************************************************

    
    
    
    Author: Filipp Popov

    Overview: 

*******************************************************************************************************/


#ifndef _RELAY_H_
#define _RELAY_H_

#include <stdint.h>

#define RELAY_FIELD_LENGTH         5
#define RELAY_BANK_SIZE            8
#define RELAY_COUNT_PER_BANK       ( RELAY_BANK_SIZE - 1 ) 

// Define common number relays
#define POS_RELAY_K1        0x02
#define POS_RELAY_K2        0x04
#define POS_RELAY_K3        0x08
#define POS_RELAY_K4        0x10
#define POS_RELAY_K5        0x20
#define POS_RELAY_K6        0x40
#define POS_RELAY_K7        0x80

#define POS_RELAY_K8        0x02
#define POS_RELAY_K9        0x04
#define POS_RELAY_K10       0x08
#define POS_RELAY_K11       0x10
#define POS_RELAY_K12       0x20
#define POS_RELAY_K13       0x40
#define POS_RELAY_K14       0x80

#define POS_RELAY_K15       0x02
#define POS_RELAY_K16       0x04
#define POS_RELAY_K17       0x08
#define POS_RELAY_K18       0x10
#define POS_RELAY_K19       0x20
#define POS_RELAY_K20       0x40
#define POS_RELAY_K21       0x80

#define POS_RELAY_K22       0x02
#define POS_RELAY_K23       0x04
#define POS_RELAY_K24       0x08
#define POS_RELAY_K25       0x10
#define POS_RELAY_K26       0x20
#define POS_RELAY_K27       0x40
#define POS_RELAY_K28       0x80

#define POS_RELAY_K29       0x02
#define POS_RELAY_K30       0x04
#define POS_RELAY_K31       0x08
#define POS_RELAY_K32       0x10
#define POS_RELAY_K33       0x20
#define POS_RELAY_K34       0x40
#define POS_RELAY_K35       0x80



#define CONTACT_MOTOR           "K21, "
#define HOLD_UP                 "K26, "
#define HOLD_DOWN               "K22, "
#define VIBRATION_MOTOR         "K28, "
#define SORTING_SHADE           "K24, "


// Define specific relays
#define MY_SPECIFIC_RELAY       POS_RELAY_Kn



enum relay {
    RELAY_K1 = 0x01,       // rename relays for custom application if needed
    RELAY_K2,   
    RELAY_K3,
    RELAY_K4,
    RELAY_K5,
    RELAY_K6,
    RELAY_K7,
    RELAY_K8,
    RELAY_K9,
    RELAY_K10,
    RELAY_K11,
    RELAY_K12,
    RELAY_K13,
    RELAY_K14,
    RELAY_K15,
    RELAY_K16,
    RELAY_K17,
    RELAY_K18,
    RELAY_K19,
    RELAY_K20,
    RELAY_K21,
    RELAY_K22,
    RELAY_K23,
    RELAY_K24,
    RELAY_K25,
    RELAY_K26,
    RELAY_K27,
    RELAY_K28,
    RELAY_K29,
    RELAY_K30,
    RELAY_K31,
    RELAY_K32,
    RELAY_K33,
    RELAY_K34,
    RELAY_K35
};


void RelaySet(uint8_t *relayField, char *relayList);
void RelayClear(uint8_t *relayField, char *relayList);
void RelayClearAll(uint8_t *relayField, uint8_t len);


#endif /* _RELAY_H_ */
/* End of file */
