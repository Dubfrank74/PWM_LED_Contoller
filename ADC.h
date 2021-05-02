/* Programmer: Frank Carr
* 
*  Filename: ADC.h
*
* Date: 26/4/2021
*  
* This is a driver for the PIC 18 series ADC. */

/* Initialise the ADC.
 * THIS FUNCTION MUST BE CALLED BEFORE ANY OF THE OTHER DRIVER FUNCTIONS. 
 * NOTE the this function makes use of TMR3 */        
void ADCInit(void);

/* Returns a 10-bit ADC output */
int ADCRead(void); /* Returns an 10-bit ADC output */

