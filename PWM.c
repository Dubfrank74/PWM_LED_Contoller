/********************************************************************************************
*
* Filename: PWM.c
*
* Description: PWMInit() initializes CCPM1 and CCPM2 for PWM operation, they will
* operate at a frequency of 1KHz with an 8 bit resolution. 
* 
* PWMSetDutyCycle() are used to set the duty cycle for the PWM modules
* 
* the map function re-maps a number from one range to another, a value fromLow gets mapped to toLow, and fromHigh to toHigh.
* www.arduino.cc/reference/en/language/functions/math/map
*
* Programmer: Frank Carr
*
* Date: 26/4/2021
*
* Version : 1.0
*
************************************************************************************************/

#include <xc.h>
 /* Configure CCP1 and CCP2 for PWM operation */
void PWMInit(void){
    
    TRISCbits.TRISC2 = 0; /* PWM pin using CCP1/P1A RC2 set as output */
    TRISCbits.TRISC1 = 0; /* PWM pin using CCP2 RC1 set as output */
    T2CKPS1 = 0; /* TIMER 2 Pre-scaler is 1 */
    T2CKPS0 = 0;
    TMR2ON = 1; /* TIMER 2 is on */
    P1M1 = 0;  /* configure ECCP module for single output mode */
    PR2 = 249; /* Timer 2 Period register = 250 counts for a 1KHz PWM frequency */
    CCPR1L = 0x7d; /* initialize duty cycle at 50 %, The 8 MSbs are 0x7d */
    CCP1CON = 0b00001100; /* DB1B the 2 LSbs are 0b00, and CCP1Mx = 1100 for PWM */
    CCPR2L = 0x7d; /* initialize duty cycle at 50 %, The 8 MSbs are 0x7d */
    CCP2CON = 0b00001100; /* DB1B the 2 LSbs are 0b00, and CCP2Mx = 1100 for PWM */
    
}

         
/* Function for setting duty cycle between 0 and 255 */
void PWM1SetDutyCycle(unsigned char duty){    
    long tenBitValue;
    tenBitValue = (PR2+1) << 2;   /* multiply (PR2+1) by 4 */
    tenBitValue = tenBitValue * duty; /* multiply by duty */
    tenBitValue = tenBitValue/256;
    CCP1CONbits.DC1B = tenBitValue & 0b11;  /* store the first two bits */
    CCPR1L = tenBitValue >> 2; /* store the remaining bits */
  
}
void PWM2SetDutyCycle(unsigned char duty){    
    long tenBitValue;
    tenBitValue = (PR2+1) << 2;   /* multiply (PR2+1) by 4 */
    tenBitValue = tenBitValue * duty; /* multiply by duty */
    tenBitValue = tenBitValue/256;
    CCP2CONbits.DC2B = tenBitValue & 0b11;  /* store the first two bits */
    CCPR2L = tenBitValue >> 2; /* store the remaining bits */
  
}
/* this function re-maps a number from one range to another, a value fromLow
 *  gets mapped to toLow and fromHigh to toHigh
 this is necessary to invert the duty-cycle for the constant current driver */
int MAP(int value, int fromLow, int fromHigh, int toLow, int toHigh)
{
    return ((((value - fromLow)*(toHigh - toLow))/(fromHigh - fromLow)) + toLow);
}