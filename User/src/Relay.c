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
void RelaySet( uint8_t *relayField, char *relayList )
{
    uint8_t relay = 0;
    
    while ( *relayList )
    {
        if ( isdigit( *relayList ) )
        {
            relay = strtol( relayList, &relayList, 10 );
            if ( relay <= ( RELAY_FIELD_LENGTH * RELAY_COUNT_PER_BANK ) && relay > 0)
            {
                relayField[ ( relay - 1 ) / RELAY_COUNT_PER_BANK ] |= ( 0x01 << ( ( ( relay - 1 ) % RELAY_COUNT_PER_BANK ) + 1 ) );
            }
        }
        else
        {
            relayList++;
        }
    }
}


// Clear specific lisf of relays in relay field
void RelayClear( uint8_t *relayField, char *relayList )
{
    uint8_t relay = 0;
    
    while ( *relayList )
    {
        if ( isdigit( *relayList ) )
        {
            relay = strtol( relayList, &relayList, 10 );
            if ( relay <= ( RELAY_FIELD_LENGTH * RELAY_COUNT_PER_BANK ) && relay > 0 )
            {
                relayField[ ( relay - 1 ) / RELAY_COUNT_PER_BANK ] &= ~( 0x01 << ( ( ( relay - 1 ) % RELAY_COUNT_PER_BANK ) + 1 ) );
            }
        }
        else
        {
            relayList++;
        }
    }
}


// Clear all relays in relay field
void RelayClearAll( uint8_t *relayField, uint8_t len )
{
    int32_t i = 0;

    for ( i = 0; i < len; i++ )
    {
        relayField[ i ] = 0x00;
    }
}


/* End of file */
