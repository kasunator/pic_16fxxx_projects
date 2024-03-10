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

/* PORT A pin assignments 
 * RA0 ANLG_X1 analog stick X1 of JOY1
 * RA1 ANLG_Y1 analog stick Y1 of JOY1
 * RA2 ANLG_X2 analog stick X2 of JOY2
 * RA3 ANLG_Y2 analog stick Y2 of JOY2
 * 
 * RA4 clk3 we made big mistake the RA4 only supports pulldown, we forgot to put
 * a pullup resostor for clock 3
 * RA5 CS or SS of SPI in communication header J1
 */

/* PORT B pin assignments 
 * PB0 BUTTON UP
 * PB1 BUTTON DOWN
 * PB2 BUTTON LEFT
 * PB3 BUTTON RIGHT
 * PB4 BUTTON A
 * PB5 BUTTON B
 * PB6 
 * PB7 THUMB BUTTON
 * 
 */

/* PORT C pin assignment 
 * RC0 Clk4
 * RC1 BUZZER1
 * RC2 BUZZER2
 * RC3 SCL
 * RC4 SDA
 * RC5 SDO
 * RC6 TX_UART
 * RC7 RX_UART
 */

/*PORT D pin assignment 
 * RE0 Row1
 * RE1 Row2
 * RE2 Row3
 * RE3 Row4
 * RE4 Row5
 * RE5 Row6
 * RE6 Row7
 * Re7 Row8
 */
/* PORT E pin assignment
 * RE0 clk1
 * RE1 clk2
 * RE2 reset
 */
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
    TRISAbits.TRISA0 = 1; /* TODO:analog input */
    TRISAbits.TRISA1 = 1; /* TODO:analog input */
    TRISAbits.TRISA2 = 1; /* TODO:analog input*/
    TRISAbits.TRISA3 = 1; /* TODO:analog input */
    TRISAbits.TRISA4 = 0; /* digital output clk3 */
    TRISAbits.TRISA5 = 0; /*TODO digital out SPI CS */
    
    /* the ADCCON1's bits 0 to 4 handles the ADC configration*/
    /* PCF<3:0> = 0b011x means all are DIGITAL pins*/
    ADCON1 = 0x06;  /* TODO: we change this when we start work on the joy stick*/
   
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

