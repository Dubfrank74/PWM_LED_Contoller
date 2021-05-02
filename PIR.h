/* Programmer: Frank Carr
* 
*  Filename: PIR.h
*
* Date: 26/4/2021
*  
* This is a driver for the PIC 18 series PIR it initializes Timer0. */

/* Initialize the PIR.
 * THIS FUNCTION MUST BE CALLED BEFORE ANY OF THE OTHER DRIVER FUNCTIONS.
 * Note the PIR function makes use of TMR0 */

void PIRInit(void);
