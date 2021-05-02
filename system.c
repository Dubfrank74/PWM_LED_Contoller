/*
* File:   system.c
*/


#include <xc.h>         /* XC8 General Include File */
#include "system.h"

/* Refer to the device data sheet for information about available
oscillator configurations. */
void ConfigureOscillator(void)
{
    IRCF2 = 1; /* FOSC =  1MHz */
    IRCF1 = 0;
    IRCF0 = 0;
}
