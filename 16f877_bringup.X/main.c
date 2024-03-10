/*
 * File:   main.c
 * Author: KBeddewela
 *
 * Created on February 4, 2024, 1:47 PM
 */

#define XTAL_FREQUENCY 4000000 /* 4 mega HZ */
#include <xc.h>
#include <pic16f877a.h>
#include "System/GPIO_driver.h"
#include "System/Timer_driver.h"

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

void __interrupt() isr(){
     
    PORTB_int_isr();
    
    Timer1_isr();
}


static void PORTA_toggle_RA1()
{
    PORTAbits.RA0 ^= 1;
}

uint8_t read_value = 0;
void main(void) {
    //RP0
    uint8_t timer_hdl_l = ms_timer_init();
    uint8_t timer_hdl_2 = ms_timer_init();
    
    PORTA_config();
    PORTB_config();
    Timer1_config();
    
    //PORTAbits.RA0 = 1;
    //PORTAbits.RA1 = 1;
    //PORTAbits.RA2 = 1;
    //PORTAbits.RA3 = 1;
    //PORTAbits.RA4 = 1;
    //PORTAbits.RA5 = 1;

    
    while (1)
    {
        ms_timer_task();
        //delay();
        if (ms_timer_get(timer_hdl_l) > 100) {
            ms_timer_reset(timer_hdl_l);
            //PORTA ^= 0x3F;/* this is how we toggle */
            PORTA ^= 0x1F; /* we are going to use RA5 as the polling light*/
            /*if (PORTBbits.RB1 == 0) { 
                PORTAbits.RA5 = 1;
            } else {
                PORTAbits.RA5 = 0;
            }*/
        }
        
        if (ms_timer_get(timer_hdl_2) > 3) {
            ms_timer_reset(timer_hdl_2);
            PORTAbits.RA5 ^= 1;
            
        }
    }
}