/* 
 * File:   Timer0_driver.c
 * Author: KBeddewela
 *
 * Created on April 23, 2024, 11:06 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic16f877a.h>

void Timer0_config()
{
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
    /* clock frequency values: CLKO i.e internal instruction cycle clock is equal to 
     * XTAL_FREQUENCY/ = Fosc/4. 
     * since One instruction cycle consists of four oscillator periods */
    /* we want 1us clock (1 microsecond) going into the timer0 , if XTAL_FREQUENCY is 8Mhz 
     * then CLKO = 2MHz, for 2us(0.5MHz) clock prescaler value should be 4
      that means PS2:PS0 bist of OPTION_REG shouls be = 001*/
    /* Let us first select the correct prescaler value
     for timer0*/
    
    OPTION_REGbits.PS = 0; //clear means prescaler is signed to time0
    OPTION_REGbits.T0CS = 0 ; //clear means CLK0 for timer 0, i.e timer mode
    OPTION_REG &= 0xF9; //to set PS2:PS0 to b001 for prescaler of 4 

    /*start the timer0 interrupt*/
    INTCONbits.T0IF = 0; // clear the flag if already set
    INTCONbits.TMR0IE = 1; //enable the interrupt
   /* enable peripheral interrupts*/
    INTCONbits.PEIE = 1;
    /* enable global interrupts */
    INTCONbits.GIE = 1;
    /*TMR0 is generated when TMR0 overflows form 0xFF to 0x00
    So for 250 clock counts of 2us clock  should be equal to 500us 
     for that TMRO should should me load with value c, where 256- c = 250. 
     So C  = 6 */
    /* start the timer by wrting the value */
    TMR0 = 6;
    
}

void inline Timer0_isr()
{
    INTCONbits.T0IF = 0; 

}