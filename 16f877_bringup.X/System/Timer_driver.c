/* 
 * File:   Timer_driver.c
 * Author: KBeddewela
 *
 * Created on February 7, 2024, 10:09 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic16f877a.h>

uint16_t load_count = 64636; /* for 1ms 65635 - c +1*/

volatile uint16_t global_time = 0;
volatile uint8_t timer_increment_flg = 0;
static uint8_t last_timer_hndl = 0;

#define TOTAL_TIMER_HANDLES 5

static uint32_t timer_cnt_array[TOTAL_TIMER_HANDLES] = {0};

void Timer1_config()
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
    INTCONbits.GIE = 1;
    /* Now we can start the timer*/
    T1CONbits.TMR1ON = 1;
    
}

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
}


void inline Timer1_isr()
{
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
        //PORTAbits.RA5 ^= 1;
        timer_increment_flg = 1;
        global_time++;
    }
}

uint16_t get_global_time_ms()
{
    return global_time;
}

void reset_global_time()
{
    global_time = 0;
}



uint8_t ms_timer_init()
{
    uint8_t ret_val;
    if (last_timer_hndl < TOTAL_TIMER_HANDLES ) {
        timer_cnt_array[last_timer_hndl] =0;
        ret_val = last_timer_hndl;
        last_timer_hndl++;
        return ret_val;
    } else {
        return 0xFF;
    }
    
}

void ms_timer_reset(uint8_t timer_handle )
{
    timer_cnt_array[timer_handle] =0;
}

uint32_t ms_timer_get(uint8_t timer_handle)
{
    return timer_cnt_array[timer_handle];
}

void ms_timer_task()
{
    int i = 0;
    if (timer_increment_flg > 0) {
        timer_increment_flg = 0;
        for (i = 0 ; i < last_timer_hndl ; i++) {
            timer_cnt_array[i]++;
        } 
    }
}
