/********************************************************************************************
*
* Filename: EUSART.c
*
* Description: EUSARTInit() initializes the serial port
*
* Programmer: Frank Carr
*
* Date: 26/4/2021
*
* Version : 1.0
*
************************************************************************************************/


#include <xc.h>         /* XC8 General Include File */

 /* Configure the serial port*/
void EUSARTInit(void){
    TRISC6 = 1; /* RC6 output for TX */
    TRISC7 = 1; /* RC7 input for RX */
    SPBRG = 25; /* Calculated baud rate (1000000/(4(25+1)))= 9615 */
    SYNC = 0; /* select asynchronous mode */
    SPEN = 1; /* enable the serial port */
    RX9 = 0; /* select 8-bit reception */
    TX9 = 0; /* select 8-bit transmission */
    BRGH = 1; /* select high speed baud rate */
    BRG16 = 1; /* Set 16 bit bit baud rate generator bit for 16 generator */
    CREN = 1; /* Enable the receiver circuitry */
    TXEN = 1; /* Enables the transmit register */
    RCIE = 1; /* Enables receive interrupts */ 
    PEIE = 1; /* Enables peripheral interrupts */
    GIE = 1; /* Enables Global interrupts */
            
}



