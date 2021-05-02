/********************************************************************************************
*
* Filename: ADC.c
*
* Description: ADCinit() initializes the PIC's ADC,
* ADCRead() performs an ADC and returns a 10 bit value
*
* Programmer: Frank Carr
*
* Date: 26/4/2021
*
* Version : 1.0
*
************************************************************************************************/

#include <xc.h>  /* XC8 General Include File */

void ADCInit(void) {

    /* Configure the ADC - input to ADC is AN0 (PORTA.0)*/
    CHS3 = 0; /* Select channel 0 (AN0) by configuring the CHS bits of the ADCON0 register as per the data sheet */
    CHS2 = 0;
    CHS1 = 0;
    CHS0 = 0;
    TRISA0 = 1; /* configure PORTA.0 as an input */
    ADON = 1; /* enable ADC */
    ADCON1 = 0; /* reference voltages are internal and ports are Analog inputs */
    ADFM = 1; /* Right justify the result by setting the ADFM bit of the ADCON2 register */
    ACQT2 = 0; /* Use an acquisition time of 12 by configuring the ACQT bits of the ADCON2 register as per the data sheet */
    ACQT1 = 0; 
    ACQT0 = 0;
    ADCS2 = 0; /* Use a clock source of FRC by configuring the ADCS bits of the ADCON2 register as per the data sheet */
    ADCS1 = 1;
    ADCS0 = 1;
    ADIF = 0; /* clear the ADC conversion complete interrupt flag */
    ADIE = 0; /* disable ADC interrupt */
    
        /* Configure Timer 3 - when enabled it used to perform an ADC after a period of time has elapsed */
    TMR3CS = 0;  // make timer 3 an interval timer
    T3CKPS1 = 1; // pre-scaler of 1:8, giving step every 32us and interrupt every 2.09 seconds
    T3CKPS0 = 1; 
    TMR3IE = 1; // enable Timer 3 interrupts
    TMR3IF = 0; // Clear the Timer 3 interrupt flag
    TMR3ON = 0; // Timer 3 is off
    
    
    
    PEIE = 1; /* set the global peripheral interrupt enable bit */
    GIE = 1; /* set the global interrupt enable bit */
    
}

int ADCRead(void) {
     
    int temp = 0; /* variable to hold conversion result */
    GO = 1; /* start the conversion */
    while( GO == 1){} /* wait until conversion is complete */
    temp = ((ADRESH<<8)+ADRESL); /* assign conversion value to temp */
    return temp;  /* return ADC conversion */
    
}
        



