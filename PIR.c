/********************************************************************************************
*
* Filename: PIR.c
*
* Description: PIRInit() initializes Timer0 used for the motion detection timer 
*
* Programmer: Frank Carr
*
* Date: 26/4/2021
*
* Version : 1.0
*
************************************************************************************************/

#include <xc.h>

void PIRInit(void){
       
  
    TRISD4 = 1; /* configure RD4 as an input for PIR */
    
        /* Configure timer 0 for PIR timeout */
    T08BIT = 0; /* 16-bit mode */
    T0CS = 0; /* make timer 0 an interval timer */
    PSA = 0;  /* assign pre-scaler to timer 0 */
    T0PS2 = 1; /* pre-scaler of 1:32, giving a step every 128us */
    T0PS1 = 0;
    T0PS0 = 0;
    TMR0IE = 1; /* enable timer 0 interrupt */
    TMR0IF = 0; /* clear the timer 0 interrupt flag */
    TMR0ON = 0; /* timer 0 is off */
    GIE = 1; /* set global interrupt enable bit */

}

