/********************************************************************************************
*
* Filename: EEPROM.c
*
* Description: EEPROM_Write() writes data to an address in EEPROM,
* EEPROM_Read() reads data from an address in EEPROM
* 
*https//www.electronicwings.com/pic/pic18f4550-on-chip-eeprom used for reference
*
* Programmer: Frank Carr
*
* Date: 26/4/2021
*
* Version : 1.0
*
************************************************************************************************/

#include <xc.h>  /* XC8 General Include File */

void EEPROM_Write(unsigned char address,unsigned char data)
{
    /*Write Operation*/
    EEADR=address;               /* Write address to the EEADR register */
    EEDATA=data;                 /* write data to the EEDATA register for write to EEPROM location */
    EECON1bits.EEPGD=0;          /* access data EEPROM memory */
    EECON1bits.CFGS=0;           /* access flash program or data memory */
    EECON1bits.WREN=1;           /* enable write to the memory, set to enable write */
    INTCONbits.GIE=0;            /* disable global interrupt
                                  interrupts should be disabled during write operation*/
    
    /*below sequence in EECON2 Register is necessary to write data to EEPROM memory
     * see section 7.4 of data sheet */
    EECON2=0x55;
    EECON2=0xaa;
    
    EECON1bits.WR=1;             /* Start writing data to EEPROM memory */
    INTCONbits.GIE=1;            /* Enable interrupt */
    
    while(PIR2bits.EEIF==0);     /* EEIF bit is set when write operation is completed */
                                 /* so wait for write operation to complete */  
    PIR2bits.EEIF=0;             /* Reset EEIF for further write operation */
    
}


char EEPROM_Read(unsigned char address)
{
    /*Read operation*/
    EEADR=address;               /* write the address to the EEADR register */
    EECON1bits.WREN=0;           /* WREN bit is cleared for Read operation */  
    EECON1bits.EEPGD=0;          /* access data EEPROM memory*/
    EECON1bits.RD=1;             /* to Read data of EEPROM memory set RD */
    return(EEDATA);              /* return the data */
}
