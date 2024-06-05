/* 
 * File:   boy.c
 * Author: KBeddewela
 *
 * Created on May 27, 2024, 1:15 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic16f877a.h>
#include "Drivers/button_inputs.h"
#include "System/Timer1_driver.h"
#include "screen_buffer.h"
#include "boy.h"


typedef struct {
    uint8_t up:1;
    uint8_t down:1;
    uint8_t left:1;
    uint8_t right:1;
    uint8_t btn_A:1;
    uint8_t btn_B:1;
}btn_bit_field_t;

dot_location_t boy_location;

btn_bit_field_t btn_bit_field = {0};

uint8_t button_timer = 0xFF;

void boy_init(){
    boy_location.x = 4;
    boy_location.y = 15;
    button_timer = ms_timer_init();
}



void boy_task(){
    if ( ms_timer_get(button_timer)> 500) {
        ms_timer_reset(button_timer);
        if (button_A() == 1 ){
            btn_bit_field.btn_A =1;
        }
        if (button_B() == 1 ){
            btn_bit_field.btn_B =1;
        }

        if (button_up() == 1){
            btn_bit_field.up = 1;
        }

        if (button_down() == 1) {
            btn_bit_field.down = 1;
        }

        if (button_left() == 1) {
            btn_bit_field.left =1;
        }

        if( button_right() == 1) {
            btn_bit_field.right = 1; 
        }
    }
    
    if (btn_bit_field.left ==1) {
        btn_bit_field.left = 0;
        
        if (boy_location.x < 7){
            boy_location.x++;
            //screen_flush_green_buffer();
           // screen_set_pixel_green(boy_location.x, boy_location.y);
        }
    }
    
    if (btn_bit_field.right ==1) {
        btn_bit_field.right= 0;
        
        if (boy_location.x > 0){
            boy_location.x--;
            //screen_flush_green_buffer();
            //screen_set_pixel_green(boy_location.x, boy_location.y);
        }
    }
}