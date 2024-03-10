/* 
 * File:   GPIO_driver.c
 * Author: KBeddewela
 *
 * Created on February 7, 2024, 9:47 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic16f877a.h>

void PORTA_config()
{
    /* first we set all the outputs to 0
     before we configure them, as outputs
    */
    PORTA = 0x00; /* port A is 5 bits long */
    /* Setting '1' a TRISA to make the pin input (default on reset)
     * Resetting '0' a TRISA to 0 makes the pin output
     * 
     *  */
    
    //TRISA = 0x1F;/* tris  a is also 5 bits long  we can use 0b11111 notation also*/
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA3 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    
    /* the ADCCON1's bits 0 to 4 handles the ADC configration*/
    ADCON1 = 0x06; /* PCF<3:0> = 0b011x means all are DIGITAL pins*/ 
   
    /* TODO: PORTA 4, aka RA4 pin need configuration 
     * of the CMCON and CVRCON  registers  also 
     The RA4 pin is open drain only output so you will not be able
     to turn on LEDS on the QLS board */
    
    /* TODO: PORTA 5, aka RA5 pin need configuration 
     * of the CMCON and CVRCON  registers  also */
    
    /* The CMCON ( the comparator controller register's ) 
     * CM2:CM0 bits are 111 at default reset so that means they
     * do not effect the output of the RA4 and RA5 pins*/
}


void PORTB_config()
{
    /* we want to configure POTB as inputs*/
    /* only RB4 to RB7 configured as inputs only 
     * support change comparison interrupts */
    /* The weak pull up can be enabled or disabled
     in the OPTION_REGs RBPU bit, 0 means disabled , 1 to enable*/
    OPTION_REGbits.nRBPU = 1;
    
    /* configure the PORTB pins as inputs*/ 
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    TRISBbits.TRISB3 = 1;
    
    /* we want to turn RB4 to RB7 
     * interrupts off by making them outputs (they are default inputs)*/
    TRISBbits.TRISB4 = 0; 
    TRISBbits.TRISB5 = 1;
    TRISBbits.TRISB6 = 0; 
    TRISBbits.TRISB7 = 0; 
    /* RBIF flag is set in the INTCON register, RBIE interrupt flag */
    /*first clear the RBIF flag before enabling the interrupt*/
    INTCONbits.RBIF = 0;
    INTCONbits.RBIE = 1;
    
    INTCONbits.GIE = 1;
    
}


void inline PORTB_int_isr()
{
    int8_t dummy_read =0;
    if (INTCONbits.RBIF == 1) {
        /* To clear the interrupt first read the PORTB
         then clear the RBIF flag */
        
        dummy_read = PORTB;
        INTCONbits.RBIF = 0;   
    }
}

