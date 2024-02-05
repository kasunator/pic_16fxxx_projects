/*
 * File:   main.c
 * Author: KBeddewela
 *
 * Created on February 4, 2024, 1:47 PM
 */

#include <xc.h>
#include <pic16f877a.h>
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

void delay(){
    int count = 10000;
    while (count) {
        count--;
    }

    
}


static void PORTA_config()
{
    /* first we set all the outptus to 0
     before we configire them, as outputs
    */
    PORTA = 0x00; /* port A is 5 bits long */
    /* Setting '1' a TRISA to make the pin input (defualt on reset)
     * Resetting '0' a TRISA to 0 makes the pin ouput */
    
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

static void PORTB_config()
{
    /* we want to configure POTB as inputs*/

    /* The weak pull up can be enabled or disabled
     in the OPTION_REGs RBPU bit, 0 means disabled , 1 to enable*/
    OPTION_REGbits.nRBPU = 1;
    
    /* RBIF flag is set in the INTCON register, RBIE interrupt flag */
    /*first clear the RBIF flag before enabling the interrupt*/
    //INTCONbits.RBIF = 0;
    //INTCONbits.RBIE = 1;
    
    /* now change */
    
    //INTCONbits.GIE = 1;
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    
}



static void PORTA_toggle_RA1()
{
    PORTAbits.RA0 ^= 1;
}

uint8_t read_value = 0;
void main(void) {
    //RP0
   
    PORTA_config();
    PORTB_config();
    
    PORTAbits.RA0 = 1;
    PORTAbits.RA1 = 1;
    PORTAbits.RA2 = 1;
    PORTAbits.RA3 = 1;
    PORTAbits.RA4 = 1;
    PORTAbits.RA5 = 1;
    
    while (1)
    {
        //delay();

        //PORTA ^= 0x3F;/* this is how we toggle */
        PORTA ^= 0x1F; /* we are going to use RB5 as the polling light*/
        if (PORTBbits.RB1 == 0) { /* we are polling */
            PORTAbits.RA5 = 1;
        } else {
            PORTAbits.RA5 = 0;
        }
    }
}