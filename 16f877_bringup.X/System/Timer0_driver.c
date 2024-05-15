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
#include "GPIO_driver.h"

volatile uint8_t timer0_flag = 1;
void Timer0_config()
{
    
   /*
    When the prescaler is assigned to the Timer0 module, any
write to the TMR0 register will immediately update the TMR0 register and clear the prescaler. The
incrementing of Timer0 (TMR0 and Prescaler) will also be inhibited 2 instruction cycles (TCY). So
if the prescaler is configured as 2, then after a write to the TMR0 register TMR0 will not increment
for 4 Timer0 clocks (Figure 11-3). After that, TMR0 will increment every prescaler number of
clocks later.*/ 
    
    
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
     * XTAL_FREQUENCY/4 = Fosc/4. 
     * since One instruction cycle consists of four oscillator periods
     * So CLK0 = 2MHz ,
     * 
     * so for prescaler of 2 input clock 1Mhz(1us period) , max delay for 8 bit 256 us 
     * for prescaler of 4 input clock 0.5MHz(2us perios) , max delay for 8 bit  512 us
      for prescaler of 8 input clock 0.25MHz (4 us period), max delay for 8 bit 1ms */
    
        /*TMR0 is generated when TMR0 overflows form 0xFF to 0x00
    Ex 1: So for 250 clock counts of 2us clock  should be equal to 500us 
     for that TMRO should should me load with value c, where 256- c = 250
    Ex 2: For 125 clock counts of 2us clock should be equal to 250us
     for that TMRO should should me load with value c, where 256- c = 125
     So C = 131  */
    
    /* If we want 0.5us clock (2 MHz) going into the timer0 , if XTAL_FREQUENCY is 8Mhz 
     * then CLKO = 2MHz, for 2us(0.5MHz) clock prescaler value should be 4
      that means PS2:PS0 bits of OPTION_REG should be = 001*/
    /* Let us first select the correct prescaler value
     for timer0*/
    
    //OPTION_REGbits.PSA = 0; //clear means prescaler is signed to time0
    //OPTION_REGbits.T0CS = 0 ; //clear means CLK0 for timer 0, 
    //OPTION_REG &= 0xF9; //to set PS2:PS0 to b001 for prescaler of 4 

    /*start the timer0 interrupt*/
    INTCONbits.T0IF = 0; // clear the flag if already set
    INTCONbits.TMR0IE = 1; //enable the interrupt
    /* enable peripheral interrupts*/
    INTCONbits.PEIE = 1;
    /* enable global interrupts */
    INTCONbits.GIE = 1;
    TMR0 = 6;
    /* writing to TMR0 when prescaler is assigned to TMR0 will clear
    * the prescaler count so now we should update the prescaler after 
     */
    //uint8_t my_options = (OPTION_REG & 0xF8) ;
    /* writing TMR0 */
    //OPTION_REG = my_options | 0x02; //to set PS2:PS0 to b001 for prescaler of 4
    OPTION_REG = 0xC1; 
    

    /* start the timer by writing the value */
    //TMR0 = 131; 
    

    
}

void inline Timer0_isr()
{
    if (INTCONbits.T0IF == 1) {
        INTCONbits.T0IF = 0;
        //TMR0 = 0;
        TMR0 = 6;
        /* writing to TMR0 when prescaler is assigned to TMR0 will clear
         * the prescaler count so now we should update the prescaler after 
         * writing TMR0 */
        //OPTION_REG &= 0xF9; //to set PS2:PS0 to b001 for prescaler of 4
        toggle_PORTE_pins(0x04);
        timer0_flag = 1;
    }

}

uint8_t inline get_timer0_flag(){
    return timer0_flag;
}


void inline reset_timer0_flag(){
    timer0_flag = 0;
}