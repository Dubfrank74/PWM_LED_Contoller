/********************************************************************************************
*
* Filename: interrupts.c
*
* Description: PRogram for interrupt service routines
*
* Programmer: Frank Carr
*
* Date: 26/4/2021
*
* Version : 1.0
*
************************************************************************************************/

#include <xc.h>         /* XC8 General Include File */
#include "PWM.h"        /* include to use PWM functions */
#include "ADC.h"        /* include to ADC function */

extern unsigned char received_char; /* used to store received data */
extern unsigned char receive_flag;  /* software flag */
extern int ADCval; /* variable to hold ADC reading */


/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* High-priority service */

void __interrupt(high_priority) high_isr(void)


{
    /* this interrupt services the serial communications*/
    if(RCIF == 1){ /* checks if data is received */
        received_char = RCREG; /* assigns the received data to a variable */
        receive_flag = 1; /* set software flag that data has been received */
    }
    
    
}

/* Low-priority interrupt routine */

void __interrupt(low_priority) low_isr(void)

{
        /* If the interrupt was caused by timer0 used by the Motion Detection code  */
            if(TMR0IF == 1) {
                PWM2SetDutyCycle(0); /* if timer has overflowed turn off the light */
                PWM1SetDutyCycle(255); 
                TMR0IF = 0; /* clear the overflow flag */
            }
        /* If the interrupt was caused by timer3 used by the LDR code */    
            if(TMR3IF == 1) {
                ADCval = ADCRead(); /* perform ADC on LDR voltage */
                TMR3IF = 0; /* clear Timer3 interrupt flag */
            }
}
