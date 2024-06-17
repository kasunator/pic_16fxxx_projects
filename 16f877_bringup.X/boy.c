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



dot_location_t boy_location;







void boy_init(){
    boy_location.x = 4;
    boy_location.y = 15;
    
    screen_set_pixel_green(boy_location.x, boy_location.y);
}



void boy_task(){

        
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