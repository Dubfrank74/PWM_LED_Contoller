/********************************************************************************************
*
* Filename: PIC_LIGHTING_CTRL_Rev15
*
* Description:This program receives inputs from sensors and serial ports and
* and adjusts PWM outputs based on the inputs.
*
* Programmer: Frank Carr
*
* Date: 26/4/2021
*
* Version : 1.0
* 
*  www.best-microcontroller-projects.com/arduino-string.html - used as resource for building & parsing strings 
*
************************************************************************************************/


/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/


#include <xc.h>        /* XC8 General Include File */
#include <stdlib.h>
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "EUSART.h"        /* Parameters for serial comms */
#include "PWM.h"            /* PWM funct/params */
#include "ADC.h"            /* ADC funct/params */
#include "PIR.h"            /* PIR funct/params */
#include "cie1931.h"        /* lookup table for log brighness see header for details */
#include "EEPROM.h"         /* EEPROM funct/params */
#define BUF_LEN 10          /* Serial Buffer length */
#define motionSensor PORTDbits.RD4 /* pin RD4 is connected to PIR module */
/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

unsigned char received_char = 0; /* data from serial port */
unsigned char receive_flag = 0; /* software flag set in EUSART interrupt */
int ADCval;

char state; /* value to store LEDs state */
 
/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp(); /* initializes interrupt priorities */
    PIRInit(); /* initialize PIR input & timer */
    EUSARTInit(); /* initialize serial port */
    PWMInit(); /* initialize PWM */
    ADCInit(); /* initialize ADC */
   

    char sdata[BUF_LEN]; /* character array for serial data */
    unsigned char mode = 0; /*  variable for command mode */
    int i = 0; /* index for array */
    int val1; /* value of Constant Voltage PWM duty cycle */
    int val2; /* value of Constant Current PWM duty cycle */
    ADCval = ADCRead(); /* stores ADC reading */
    
    
  
    
    while(1) /* infinite loop */
   
    {
        while(receive_flag == 1){  /* stay in loop while software flag is set */
          
            sdata[i] = received_char; /*  assign received char to array */
            i++; /* increment array index */
            if(received_char == '\r'){ /* if command received is '\r' don't place in array */
                i--; /* decrement index */
                sdata[i] = '\0'; /* replace \r with \0 at current index */

                
             /* Process command in sdata array */
                
                switch( sdata[0]){ /* switch case on on the first character in the array */
          
                    case 'a':
                        mode = 1; /* set LDR mode */
                        TMR0ON = 0; /* turn off PIR timer */
                        TMR3ON = 1; /* turn on ADC */
                        PWM2SetDutyCycle(0); /* turn lights off */
                        PWM1SetDutyCycle(255); 
                        state = 0;
                        ADCval = ADCRead(); /* stores ADC reading */
                        break;
                    case 'b': 
                        mode = 2; /* set PIR mode */
                        TMR0ON = 1; /* turn on PIR timer */
                        TMR3ON = 0; /* turn off ADC */
                        break;
                    case 'c':
                        mode = 0;
                        TMR0ON = 0; /* turn off PIR timer */
                        TMR3ON = 0; /* turn off ADC */
                        val1 = atoi(&sdata[1]); /* converts the data from index 1 in the array to an integer and assign to val1 */
                        PWM2SetDutyCycle(cie[val1]);     /* set duty cycle to value of val1 */   
                        break;
                    case 'd':
                        mode = 0;
                        TMR0ON = 0; /* turn off PIR timer */
                        TMR3ON = 0; /* turn off ADC */
                        val2 = atoi(&sdata[1]); /* converts the value from index 1 in the array to an integer and assign to val2 */
                        val2 =  MAP(val2,0,255,255,0); /* inverts duty cycle values for constant current driver */
                        PWM1SetDutyCycle(val2);     /* set duty cycle to value of val2 */                       
                        break;
                    case 'e':
                        mode = 3; /* set auto mode */
                        TMR0ON = 1; /* turn on PIR timer */ 
                        TMR3ON = 1;
                        PWM2SetDutyCycle(0); /* turn lights off */
                        PWM1SetDutyCycle(255); 
                        ADCval = ADCRead(); /* stores ADC reading */
                        break; 
                    case 'f':    /* save preset */
                        mode = 0; 
                        TMR0ON = 0; /* turn off PIR timer */
                        TMR3ON = 0; /* turn off ADC */
                        EEPROM_Write(0,(unsigned char)val1); /* save duty cycle value to address 0 */
                        EEPROM_Write(1,(unsigned char)val2);/* save duty cycle value to address 1 */
                        break;
                    case 'g':   /* recall preset */
                        mode = 0;
                        TMR0ON = 0; /* turn off PIR timer */
                        TMR3ON = 0; /* turn off ADC */
                        val1 = EEPROM_Read(0); /* data at address 0 and assign to duty cycle */
                        PWM2SetDutyCycle(cie[val1]); /* set duty cycle */
                        val2 = EEPROM_Read(1); /* data at address 1 and assign to duty cycle */
                        PWM1SetDutyCycle(val2); /* set duty cycle */                       
                        break;
                    case 'h':
                        mode = 0;
                        TMR0ON = 0; /* turn off PIR timer */
                        TMR3ON = 0; /* turn off ADC */
                        break;
                    case 'i': /* manual on */
                        mode = 0;
                        TMR0ON = 0; /* turn off PIR timer */
                        TMR3ON = 0; /* turn off ADC */
                        PWM2SetDutyCycle(255); 
                        PWM1SetDutyCycle(0); 
                        break;
                    case 'j':   /* manual off */
                        mode = 0;
                        TMR0ON = 0; /* turn off PIR timer */
                        TMR3ON = 0; /* turn off ADC */
                        PWM2SetDutyCycle(0); 
                        PWM1SetDutyCycle(255);
                        break;
                }
                for(i=0;i<10;i++){    
                   sdata[i] = '\0';   /* when serial command is processed clear the array */
               }
                i=0;     /* reset array index */
            }
           receive_flag = 0; /* when finished processing serial data clear flag to exit loop */
        } 
        /* Process modes of operation */
      
        if( mode == 1){ /* if in LDR mode do this */    
            if( ADCval>500 && state ==1 ){ /* If change in light level above threshold value and light is on*/
                PWM2SetDutyCycle(0); /* turn lights off */
                PWM1SetDutyCycle(255); 
                state = 0;  /* light is off */          
            }
            if(ADCval<400 && state == 0){ /* if change in light is below threshold value and light is off */        
                PWM2SetDutyCycle(255); /* turn lights on */
                PWM1SetDutyCycle(0);
                state = 1;    /* light is on */
            }
        }
        else if(mode == 2 && motionSensor == 1){ /* if in PIR mode do this */  
            PWM2SetDutyCycle(255);  /* turn on light */
            PWM1SetDutyCycle(0);  /* turn on light */     
            TMR0 = 26474; /* pre-load timer0 for approx 5 second delay */
        }
        else if(mode == 3){  /* call the AUTO mode */ 
            if(ADCval>500){     /* if light level above threshold value and light is on */
                PWM2SetDutyCycle(0); /* turn off the light */
                PWM1SetDutyCycle(255); /* turn off the light */
            }  
            else if (ADCval<400){ /* if light level is below threshold value and light is off */
                if(motionSensor == 1){ /* check if motion is detected */
                    PWM2SetDutyCycle(255);  /* turn on light */
                    PWM1SetDutyCycle(0); /* turn on light */
                    TMR0 = 26474; /* pre-load timer0 for a 5 second delay */                  
               }
            }
        }
    }   
}
   


