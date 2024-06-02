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
#include"screen_buffer.h"

typedef struct {
    uint8_t x:4;
    uint8_t y:4;
}dot_location_t;

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


void boy_init(){
    boy_location.x = 4;
    boy_location.y = 0;
}


void boy_task(){
    
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
    
    if (btn_bit_field.left ==1) {
        btn_bit_field.left = 0;
        
        if (boy_location.x > 0){
            boy_location.x--;
            screen_flush_green_buffer();
        }
    }
    
    if (btn_bit_field.right ==1) {
        btn_bit_field.right= 0;
        
        if (boy_location.x <8){
            boy_location.x++;
            screen_flush_green_buffer();

        }
        
    }
}