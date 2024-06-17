/* 
 * File:   newmain.c
 * Author: KBeddewela
 *
 * Created on March 10, 2024, 6:49 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic16f877a.h>
#include "../System/Timer1_driver.h"
#include "button_inputs.h"

#define TWO_HUNDRED_MS 200
#define FIVE_HUNDRED_MS 500


btn_bit_field_t btn_bit_field = {0};

btn_repeat_bit_field_t btn_repeat_bit_field = {0};

uint8_t button_timer = 0xFF;

/* button UP PORTB 0*/
inline uint8_t  button_up()
{
    return PORTBbits.RB0;
}

/* button Down PORTB 1*/
inline uint8_t  button_down()
{
    return PORTBbits.RB1;
}

/* button Left PORTB 2*/
inline uint8_t  button_left()
{
    return PORTBbits.RB2;
}


/* button Right PORTB 3*/
inline uint8_t  button_right()
{
    return PORTBbits.RB3;
}

/* button A PORTB 4*/
inline uint8_t  button_A()
{
    return PORTBbits.RB4;
}

/* button B PORTB 5*/
inline uint8_t  button_B()
{
    return PORTBbits.RB5;
}



void button_inputs_init(){
    button_timer = ms_timer_init();
}

void button_input_task(){
    if ( ms_timer_get(button_timer)> TWO_HUNDRED_MS) {
        ms_timer_reset(button_timer);
        if (btn_repeat_bit_field.scan_counter < 2) {
            btn_repeat_bit_field.scan_counter++;
        } //else {
            //btn_repeat_bit_field.scan_counter=0;
            /* we have completed a repeat 1 repeat scan period*/
        //}
        
        if (btn_repeat_bit_field.scan_counter == 2) {
            /* we have completed a repeat 1 repeat period lets scan again*/
            if (btn_repeat_bit_field.btn_A == 1) {
                btn_bit_field.btn_A =1;
            } else if (btn_repeat_bit_field.btn_B == 1) {
                btn_bit_field.btn_B =1;
            } else if (btn_repeat_bit_field.up == 1) {
                btn_bit_field.up =1;
            } else if (btn_repeat_bit_field.down == 1) {
                btn_bit_field.down  =1;
            } else if (btn_repeat_bit_field.left == 1) {
                btn_bit_field.left =1;
            }else if (btn_repeat_bit_field.right == 1) {
                btn_bit_field.right =1;
            }
        }
        
        
        if (button_A() == 1 && btn_repeat_bit_field.btn_A == 0){
            btn_bit_field.btn_A =1;
            btn_repeat_bit_field.scan_counter=0;
        } else {
            btn_repeat_bit_field.btn_A  = 0;
        }  
        
        if (button_B() == 1 && btn_repeat_bit_field.btn_B == 0 ){
            btn_bit_field.btn_B =1;
            btn_repeat_bit_field.scan_counter=0;
        } else {
            btn_repeat_bit_field.btn_B  = 0;
        }

        if (button_up() == 1 && btn_repeat_bit_field.up == 0){
            btn_bit_field.up = 1;
            btn_repeat_bit_field.scan_counter=0;
        }else {
            btn_repeat_bit_field.up  = 0;
        }

        if (button_down() == 1 && btn_repeat_bit_field.down == 0) {
            btn_bit_field.down = 1;
            btn_repeat_bit_field.scan_counter=0;
        } else {
            btn_repeat_bit_field.down  = 0;
        }

        if (button_left() == 1 && btn_repeat_bit_field.left == 0) {
            btn_bit_field.left =1;
            btn_repeat_bit_field.scan_counter=0;
        } else {
            btn_repeat_bit_field.left  = 0;
        }

        if( button_right() == 1 && btn_repeat_bit_field.right == 0) {
            btn_bit_field.right = 1; 
            btn_repeat_bit_field.scan_counter=0;
        } else {
            btn_repeat_bit_field.right  = 0;
        }
    }
}