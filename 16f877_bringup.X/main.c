/*
 * File:   main.c
 * Author: KBeddewela
 *
 * Created on February 4, 2024, 1:47 PM
 */

#define XTAL_FREQUENCY 8000000 /* 4 mega HZ */
#include <xc.h>
#include <pic16f877a.h>
#include "System/GPIO_driver.h"
#include "System/Timer1_driver.h"
#include "System/Timer0_driver.h"
#include "Drivers/button_inputs.h"
#include "Drivers/display_multiplexer.h"
#include "marquee.h"
#include "screen_buffer.h"
#include <string.h>
#include "boy.h"



#pragma config FOSC = HS        // Oscillator Selection bits (XT oscillator)
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
     
    Timer0_isr();
    PORTB_int_isr();
    
    Timer1_isr();
    
}


static void PORTA_toggle_RA1()
{
    PORTAbits.RA0 ^= 1;
}



uint8_t buffer_ready_flag = 0;

void main(void) {

    /* system level init*/
    PORTA_config();
    PORTB_config();
    PORTC_config();
    PORTD_config();
    PORTE_config();
    
    //reset_clk_1();
    //reset_clk_2();
    //reset_clk_3();
    //reset_clk_4();
    Timer0_config();
    Timer1_config();
    screen_buffer_init();
    marquee_init();
    boy_init();
    
    while (1)
    {
        ms_timer_task();
        display_multiplexer_task();
        

        screen_buffer_task();
        marquee_task();
        
        
        /*
        if (buffer_ready_flag == 1 && get_frame_complete_flag() == 1 ) {
            buffer_ready_flag = 0;
            display_multiplexer_set_red_array(&red_array);
            display_multiplexer_set_green_array(&green_array);
            
        } */

        
    }

   
}