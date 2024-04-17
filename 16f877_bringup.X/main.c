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
#include "Drivers/button_inputs.h"
#include "Drivers/display_multiplexer.h"



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
     
    PORTB_int_isr();
    
    Timer1_isr();
}


static void PORTA_toggle_RA1()
{
    PORTAbits.RA0 ^= 1;
}

uint8_t read_value = 0;
uint8_t button_press = 0;
uint8_t reset_flag = 0;
uint8_t clk_flag = 0;
uint8_t timer_active = 0;
void main(void) {

    /* system level init*/
    PORTA_config();
    PORTB_config();
    PORTC_config();
    PORTD_config();
    PORTE_config();
    
    reset_clk_1();
    reset_clk_2();
    reset_clk_3();
    reset_clk_4();
    
    Timer1_config();
    
    uint8_t timer_hdl_l = ms_timer_init();
    uint8_t timer_hdl_2 = ms_timer_init();

    
    while (1)
    {
        ms_timer_task();
        //delay();
        /*if (ms_timer_get(timer_hdl_l) > 100) {
            ms_timer_reset(timer_hdl_l);
            if ()
        }*/
        
        /*if (ms_timer_get(timer_hdl_2) > 100) {
            ms_timer_reset(timer_hdl_2);
            reset_reset_matrix();
        }*/
        
        if (button_A() == 1 )
        {
            reset_flag =1;
        }
        
        if (button_B() == 1 )
        {
            clk_flag =1;
        }
        
        
        if (clk_flag == 1) {                
            clk_flag = 0;
            set_row_pattern(0xFF);
            set_clk_3();
            timer_active = 1;
            ms_timer_reset(timer_hdl_l);
        }
        
        if (reset_flag == 1) {
            reset_flag = 0;
            set_reset_matrix();
            timer_active = 1;
            ms_timer_reset(timer_hdl_l);
        }
        

        if (ms_timer_get(timer_hdl_l) > 100 && timer_active == 1) {
           // ms_timer_reset(timer_hdl_l);
            timer_active = 0;
            reset_clk_3();
            reset_reset_matrix();
        }
        
    }
}