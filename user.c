/********************************************************************************************
*
* Filename: user.c
*
* InitApp(); 
* 
*
* Programmer: Frank Carr
*
* Date: 26/4/2021
*
* Version : 1.0
*
************************************************************************************************/


#include <xc.h>         /* XC8 General Include File */


void InitApp(void)
{ 
    IPEN = 1; /* interrupt priority enable bit */
    RCIP = 1; /* EUSART interrupt is high priority */
    TMR0IP = 0; /* Timer0 interrupt is low priority */
    TMR3IP = 0; /* Timer3 interrupt is low priority */
}



