/* Programmer: Frank Carr
* 
*  Filename: EEPROM.h
*
* Date: 26/4/2021
*  
* This is a driver for the PIC 18 series EEPROM module. */


/* writes data to an address in EEPROM memory */
void EEPROM_Write(unsigned char address,unsigned char data);


/* reads data from an address in EEPROM memory */
char EEPROM_Read(unsigned char address);

