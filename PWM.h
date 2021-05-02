/* Programmer: Frank Carr
* 
*  Filename: PWM.h
*
* Date: 26/4/2021
*  
* This is a driver for the PIC 18 series PWM module. */

/* Initialize the PWM module.
 * The PWM frequency is 1kHz Hz.
 * The default duty cycle is 50%.
 * THIS FUNCTION MUST BE CALLED BEFORE setDutyCycle(). */
void PWMInit(void);

/* Use these functions to change the duty
 * cycle.
 * duty must be less than or equal to 255 */
void PWM1SetDutyCycle( unsigned char duty);
void PWM2SetDutyCycle( unsigned char duty);

/* this function re-maps a number from one range to another, a value fromLow gets mapped to toLow and fromHigh to toHigh*
*ww.arduino.cc/reference/en/language/functions/math/map*/

int MAP(int value, int fromLow, int fromHigh, int toLow, int toHigh);