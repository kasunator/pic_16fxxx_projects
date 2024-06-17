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
#define TWO_HUNDRED_MS 200
#define FIVE_HUNDRED_MS 500
typedef struct {
    uint8_t up:1;
    uint8_t down:1;
    uint8_t left:1;
    uint8_t right:1;
    uint8_t btn_A:1;
    uint8_t btn_B:1;
}btn_bit_field_t;

typedef struct {
    uint8_t scan_counter;
    uint8_t up:1;
    uint8_t down:1;
    uint8_t left:1;
    uint8_t right:1;
    uint8_t btn_A:1;
    uint8_t btn_B:1;
}btn_repeat_bit_field_t;


dot_location_t boy_location;

btn_bit_field_t btn_bit_field = {0};

btn_repeat_bit_field_t btn_repeat_bit_field = {0};



uint8_t button_timer = 0xFF;

void boy_init(){
    boy_location.x = 4;
    boy_location.y = 15;
    button_timer = ms_timer_init();
    screen_set_pixel_green(boy_location.x, boy_location.y);
}



void boy_task(){
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
        
    if (btn_bit_field.left ==1 ) {
        btn_bit_field.left = 0;
        
        if (boy_location.x < 7){
            screen_reset_pixel_green(boy_location.x, boy_location.y);
            boy_location.x++;
            //screen_flush_green_buffer();
            screen_set_pixel_green(boy_location.x, boy_location.y);
        }
    }
    
    if (btn_bit_field.right ==1) {
        btn_bit_field.right= 0;
        
        if (boy_location.x > 0){
            screen_reset_pixel_green(boy_location.x, boy_location.y);
            boy_location.x--;
            //screen_flush_green_buffer();
            screen_set_pixel_green(boy_location.x, boy_location.y);
        }
    }
    
    if (btn_bit_field.down ==1) {
        btn_bit_field.down = 0;
        
        if (boy_location.y < 15){
            screen_reset_pixel_green(boy_location.x, boy_location.y);
            boy_location.y++;
            //screen_flush_green_buffer();
            screen_set_pixel_green(boy_location.x, boy_location.y);
        }
    }
    
    if (btn_bit_field.up ==1) {
        btn_bit_field.up = 0;
        
        if (boy_location.y > 0){
            screen_reset_pixel_green(boy_location.x, boy_location.y);
            boy_location.y--;
            //screen_flush_green_buffer();
            screen_set_pixel_green(boy_location.x, boy_location.y);
        }
    }
    
    if (btn_bit_field.btn_A ==1) {
        btn_bit_field.btn_A = 0;
    }
    
    if (btn_bit_field.btn_B ==1) {
        btn_bit_field.btn_B = 0;
    }
    //screen_set_pixel_green(boy_location.x, boy_location.y);
}