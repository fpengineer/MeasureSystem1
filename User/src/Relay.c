/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Voltmeter functions

*******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "Relay.h"

// Set specific lisf of relays in relay field
void RelaySet(uint8_t *relayField, char *relayList)
{
    uint8_t relay = 0;
    
    while (*relayList)
    {
        if (isdigit(*relayList))
        {
            relay = strtol(relayList, &relayList, 10);
            relayField[(relay + 1) / 8] |= 0x01 << (relay % 7);
        }
        else
        {
            relayList++;
        }
    }
}


// Clear specific lisf of relays in relay field
void RelayClear(uint8_t *relayField, char *relayList)
{
    uint8_t relay = 0;
    
    while (*relayList)
    {
        if (isdigit(*relayList))
        {
            relay = strtol(relayList, &relayList, 10);
            relayField[(relay + 1) / 8] &= ~(0x01 << (relay % 7));
        }
        else
        {
            relayList++;
        }
    }
}


// Clear all relays in relay field
void RelayClearAll(uint8_t *relayField)
{
    int32_t i = 0;

    for (i = 0; i < sizeof(relayField); i++)
    {
        relayField[i] = 0x00;
    }
}


/* End of file */
