/* Programmer: Frank Carr
* 
*  Filename: EUSART.h
*
* Date: 26/4/2021
*  
* This is a driver for the PIC 18 series EUSART. *//* Initialize the EUSART module.
* The Baud rate is 9600.
* 
* THIS FUNCTION MUST BE CALLED BEFORE USING SERIAL COMMS.
* NOTE the this function makes use of TMR2 */

void EUSARTInit(void);
 



