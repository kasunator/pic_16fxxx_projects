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
#include <string.h>



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

uint8_t read_value = 0;
uint8_t btn_A_flag = 0;
uint8_t btn_B_flag = 0;


/*uint8_t k_array[] = { 0x7F, 0x08, 0x14, 0x22, 0x41}; */

const uint8_t k_array[] = { 0x00, 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41, 0x00,
                      0x00, 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41, 0x00};

const uint8_t k_upper[] = { 0x00, 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint8_t k_lower[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x7F, 0x08, 0x14, 0x22, 0x41, 0x00};

const uint8_t blank_array[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint8_t A[] = {0x18, 0x24, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x00};
const uint8_t B[] =  {0x3E, 0x42, 0x42, 0x3E, 0x42, 0x42, 0x3E, 0x00};
const uint8_t C[] = {0x00, 0x3E, 0x41, 0x41, 0x41, 0x22, 0x00, 0x00}; 
const uint8_t K[] = {0x42, 0x22, 0x12, 0x0E, 0x12, 0x22, 0x42, 0x00};

uint8_t green_array[16] = {};
uint8_t red_array[16] = {};

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
    Timer0_config();
    Timer1_config();
   
    memcpy(&red_array, &B, sizeof(B));
    memset(&red_array+8, 0, 8 );
    
    memcpy(&green_array, &B, sizeof(B));
    memcpy(&green_array+8, &K, sizeof(K));
    
    //memset(&green_array, 0, 8);
    
   //display_multiplexer_set_red_array(k_array);
   //display_multiplexer_set_green_array(blank_array);
   display_multiplexer_set_red_array(&red_array);
   display_multiplexer_set_green_array(&green_array);
    
    while (1)
    {
        ms_timer_task();
        display_multiplexer_task();
        
        if (button_A() == 1 )
        {
            btn_A_flag =1;
        }
        
        if (button_B() == 1 )
        {
            btn_B_flag =1;
        }
        
        
        
    }
}