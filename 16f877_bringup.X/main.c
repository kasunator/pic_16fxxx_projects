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

uint8_t scroll_timer = 0;

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

uint8_t green_array_ping[16] = {};
uint8_t red_array_ping[16] = {};

uint8_t red_array_pong[16] = {};
uint8_t green_array_pong[16] = {};

uint8_t* red_array;
uint8_t* green_array; 

uint8_t scroll_index = 0;
uint8_t i = 0;
uint8_t temp1 =0;
uint8_t temp2 =0;
uint8_t state = 0;
uint8_t buffer_ready_flag = 0;

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
   
    memcpy(&red_array_ping, &B, sizeof(B));
    memset(&red_array_ping+8, 0, 8 );
    memset(&green_array_ping, 0, 16);
    
    //memcpy(&green_array, &B, sizeof(B));
    //memcpy(&green_array+8, &K, sizeof(K));
    
    
    //memset(&red_array, 0, 16);
    memset(&red_array_pong, 0, 16);
    memset(&green_array_pong, 0, 16);
    
   //display_multiplexer_set_red_array(k_array);
   //display_multiplexer_set_green_array(blank_array);
   display_multiplexer_set_red_array(&red_array_ping);
   display_multiplexer_set_green_array(&green_array_ping);
   scroll_timer = ms_timer_init();
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
      
        if (ms_timer_get(scroll_timer) >= 1000) {
            ms_timer_reset(scroll_timer);
            scroll_index++;
            reset_frame_complete_flag();
            if (state == 0){
                memcpy(&red_array_pong, &red_array_ping, sizeof(red_array_ping));
                memcpy(&green_array_pong, &green_array_ping, sizeof(green_array_ping));
                red_array = &red_array_pong;
                green_array = &green_array_pong;
                state = 1;
            } else {
                
                memcpy(&red_array_ping, &red_array_pong, sizeof(red_array_ping));
                memcpy(&green_array_ping, &green_array_pong, sizeof(green_array_ping));
                red_array = &red_array_ping;
                green_array = &green_array_ping;
                state = 0;
            }
            
            temp1 = red_array[0];
            for (i =1 ; i<16; i++) {
                temp2 = red_array[i];
                red_array[i] = temp1;
                temp1 = temp2;
            }
            red_array[0]= temp1;
            //memset(&red_array, 0, sizeof(red_array));
            //memcpy(&red_array + scroll_index, &B, sizeof(B));
            //memcpy(&red_array + scroll_index, &B, sizeof(B));
            if (scroll_index >= 16) {
                scroll_index = 0;
            }
            buffer_ready_flag = 1;
            //display_multiplexer_set_red_array(&red_array[0]);
            //display_multiplexer_set_green_array(&green_array[0]);
            display_multiplexer_set_red_array(red_array);
            display_multiplexer_set_green_array(green_array);
        }
        /*
        if (buffer_ready_flag == 1 && get_frame_complete_flag() == 1 ) {
            buffer_ready_flag = 0;
            display_multiplexer_set_red_array(&red_array);
            display_multiplexer_set_green_array(&green_array);
            
        } */

        
    }

   
}