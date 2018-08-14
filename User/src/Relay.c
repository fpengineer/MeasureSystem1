/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Voltmeter functions

*******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "Relay.h"


void RelaySet(uint8_t *relayField, enum relay relay)
{
    relayField[(relay + 1) / 8] |= 0x01 << (((relay + 1) % 8) + 1);
}


void RelayClear(uint8_t *relayField, enum relay relay)
{
    relayField[(relay + 1) / 8] &= ~(0x01 << (((relay + 1) % 8) + 1));
}


void RelayClearAll(uint8_t *relayField)
{
    int32_t i = 0;

    for (i = 0; i < sizeof(relayField); i++)
    {
        relayField[i] = 0x00;
    }
}


/* End of file */
