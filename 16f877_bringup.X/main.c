/*
 * File:   main.c
 * Author: KBeddewela
 *
 * Created on February 4, 2024, 1:47 PM
 */

#define XTAL_FREQUENCY 4000000 /* 4 mega HZ */
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

uint16_t load_count = 64636; /* for 1ms 65635 - c +1*/

void delay(){
    int count = 10000;
    while (count) {
        count--;
    }

    
}

void __interrupt() isr(){
    uint8_t dummy_read;
     
    /* Check if port B change comparison interrupt*/
    if (INTCONbits.RBIF == 1) {
        /* To clear the interrupt first read the PORTB
         then clear the RBIF flag */
        
        dummy_read = PORTB;
        INTCONbits.RBIF = 0;   
    }
    /* check for TIMER 1 interrupt */
    if (PIR1bits.TMR1IF == 1){
        /* clear the flag*/
        PIR1bits.TMR1IF = 0;
        /* stop the running timer*/
        T1CONbits.TMR1ON = 0;
        /* reload the Timer*/
        TMR1H = (uint8_t)(load_count >> 8);
        TMR1L = (uint8_t)load_count;
        /* start the timer again*/
        T1CONbits.TMR1ON = 1;
        /* toggle gpio for debugging*/
        PORTAbits.RA5 ^= 1;
    }
}

static void Timer0_config(){
 /*   Timer mode is selected by clearing bit T0CS
    (OPTION_REG<5>). 
  In Timer mode, the Timer0
module will increment every instruction cycle (without prescaler). 
  * If the TMR0 register is written, the increment is inhibited for the following two instruction cycles.
  The user can work around this by writing an adjusted
    value to the TMR0 register
  * 
  * The TMR0 interrupt is generated when the TMR0
    register overflows from FFh to 00h. This overflow sets
    bit TMR0IF (INTCON<2>). The interrupt can be
    masked by clearing bit TMR0IE (INTCON<5>). Bit
    TMR0IF must be cleared in software by the Timer0
    module Interrupt Service Routine before re-enabling
    this interrupt. 
  */
}
static void Timer1_config()
{
   /* The TMR1 register pair
        (TMR1H:TMR1L) increments from 0000h to FFFFh
        and rolls over to 0000h. The TMR1 interrupt, if enabled,
        is generated on overflow which is latched in interrupt
        flag bit, TMR1IF (PIR1<0>). This interrupt can be
        enabled/disabled by setting/clearing TMR1 interrupt
    enable bit, TMR1IE (PIE1<0>). 
    
    The operating mode is determined by the clock select
    bit, TMR1CS (T1CON<1>). = 0 means timer i.e driven by Fosc/4
    
    Timer1 can be enabled/disabled by setting/clearing
    control bit, TMR1ON (T1CON<0>).*/
    
    /* calculating the timer1 count for 1ms delay
     * 
     * XTAL_FREQUENCY/4 = Timer1_freq = 1x10^6
        clock period Ts = 1/Timer1_freq = 1x10^-6 
     *  let count for 1ms delay be C:
     * then C x Ts = 1x10^-3 ( 1ms) 
     *  C = 1x10^-3/Ts = 1000.
     *  C = 1000
     * so the load value should be 65,535 - C + 1 
     * because the interrupt happens @ 65,535 to 0
     */
    /* disable interrupts first*/
    PIE1bits.TMR1IE = 0;
    /* reset the TMR1, TODO: calculate the suitable value to load the timer*/
    TMR1H = (uint8_t)(load_count >> 8);
    TMR1L = (uint8_t)load_count;
    /* clear interrupt flag before enabling if pending*/
    PIR1bits.TMR1IF = 0;
    /* enable the timer interrupt */
    PIE1bits.TMR1IE = 1;
    /* enable peripheral interrupts*/
    INTCONbits.PEIE = 1;
    /* enable global interrupts */
    INTCONbits.PEIE = 1;
    /* Now we can start the timer*/
    T1CONbits.TMR1ON = 1;
    
    
}

static void PORTA_config()
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

static void PORTB_config()
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



static void PORTA_toggle_RA1()
{
    PORTAbits.RA0 ^= 1;
}

uint8_t read_value = 0;
void main(void) {
    //RP0
   
    PORTA_config();
    PORTB_config();
    Timer1_config();
    
    PORTAbits.RA0 = 1;
    PORTAbits.RA1 = 1;
    PORTAbits.RA2 = 1;
    PORTAbits.RA3 = 1;
    PORTAbits.RA4 = 1;
    PORTAbits.RA5 = 1;
    
    while (1)
    {
        delay();

        //PORTA ^= 0x3F;/* this is how we toggle */
        PORTA ^= 0x1F; /* we are going to use RA5 as the polling light*/
        /*if (PORTBbits.RB1 == 0) { 
            PORTAbits.RA5 = 1;
        } else {
            PORTAbits.RA5 = 0;
        }*/
    }
}