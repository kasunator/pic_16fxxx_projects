/* 
 * File:   screen_buffer.c
 * Author: KBeddewela
 *
 * Created on May 27, 2024, 1:40 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic16f877a.h>
#include <string.h>
#include "System/GPIO_driver.h"
#include "System/Timer1_driver.h"
#include "System/Timer0_driver.h"
#include "Drivers/button_inputs.h"
#include "Drivers/display_multiplexer.h"



uint8_t green_array_ping[16] = {};
uint8_t red_array_ping[16] = {};

uint8_t red_array_pong[16] = {};
uint8_t green_array_pong[16] = {};

uint8_t* red_array;
uint8_t* green_array; 
uint8_t state = 0;
uint8_t state_changed_flag = 0;
uint8_t buffer_update_flag = 0;

static void frame_cmplt_cb_func();

/*
 * 
 */
void screen_buffer_init(){
    memset(&red_array_ping, 0, 16 );
    memset(&green_array_ping, 0, 16 );
    
    memset(&red_array_pong, 0, 16);
    memset(&green_array_pong, 0, 16);
    set_frame_cmplt_cb(&frame_cmplt_cb_func);
    display_multiplexer_set_red_array(&red_array_ping[0]);
    display_multiplexer_set_green_array(&green_array_ping[0]);

}

void screen_overlay_bitfield_sprite_red( uint8_t* buffer, uint8_t start_byte,
                                         uint8_t length, uint8_t circular){ 
    uint8_t i =0;
    buffer_update_flag =1;
    if (state == 0) {
        //write to pong, ping being used
        for(i = 0 ; i < length ; i++){
            if (i +start_byte < sizeof(red_array_pong)) {
                red_array_pong[i + start_byte]|= buffer[i];
            } else if (circular) {
                red_array_pong[i + start_byte -sizeof(red_array_pong)]|= buffer[i];
            }
        }
    } else {
        //write to ping, pind being used
        for(i = 0 ; i < length ; i++){
            if (i +start_byte < sizeof(red_array_ping)) {
                red_array_ping[i +start_byte]|= buffer[i];
            } else if(circular){
                red_array_ping[i +start_byte-sizeof(red_array_ping)]|= buffer[i];
            }
        }
    }
}

void screen_clear_bitfield_sprite_red( uint8_t* buffer, uint8_t start_byte,
                                       uint8_t length, uint8_t circular){
    uint8_t i =0;
    buffer_update_flag = 1;
    if (state == 0) {
        //write to pong, ping being used
        for(i = 0 ; i < length ; i++){
            if (i + start_byte< sizeof(red_array_pong)) {
                red_array_pong[i+start_byte] &= ~buffer[i];
            } else if (circular){
                red_array_pong[i +start_byte -sizeof(red_array_pong)] &= ~buffer[i];
            }
        }
    } else {
        //write to ping, pind being used
        for(i = 0 ; i < length ; i++){
            if (i +start_byte < sizeof(red_array_ping)) {
                red_array_ping[i +start_byte]&= ~buffer[i];
            } else if (circular) {
                red_array_ping[i +start_byte-sizeof(red_array_ping)] &= ~buffer[i];
            }
        }
    }
}

void screen_overlay_bitfield_sprite_green( uint8_t* buffer, uint8_t start_byte,
                                            uint8_t length, uint8_t circular){
    uint8_t i =0;
    buffer_update_flag = 1;
    if (state == 0) {
        //write to pong, ping being used
        for(i = 0 ; i < length ; i++){
            if (i +start_byte < sizeof(green_array_pong)) {
                green_array_pong[i +start_byte]|=buffer[i];
            } else if (circular){
                green_array_pong[i +start_byte-sizeof(green_array_pong)]|=buffer[i];
            }
        }
    } else {
        //write to ping, pind being used
        for(i = 0 ; i < length ; i++){
            if (i +start_byte < sizeof(green_array_ping)) {
                green_array_ping[i +start_byte]|=buffer[i];
            } else if (circular){
               green_array_ping[i +start_byte-sizeof(green_array_ping)]|=buffer[i]; 
            }
        }
    }
}

void screen_clear_bitfield_sprite_green( uint8_t* buffer, uint8_t start_byte,
                                         uint8_t length, uint8_t circular){
    uint8_t i =0;
    buffer_update_flag = 1;
    if (state == 0) {
        //write to pong, ping being used
        for(i = 0 ; i < length ; i++){
            if (i +start_byte < sizeof(green_array_pong)) {
                green_array_pong[i +start_byte]&= ~buffer[i];
            } else if(circular){
                green_array_pong[i +start_byte-sizeof(green_array_pong)]&= ~buffer[i];
            }
        }
    } else {
        //write to ping, pind being used
        for(i = 0 ; i < length ; i++){
            if (i +start_byte < sizeof(green_array_ping)) {
                green_array_ping[i +start_byte] &= ~buffer[i];
            } else if(circular) {
                green_array_ping[i +start_byte-sizeof(green_array_ping)] &= ~buffer[i];
            }
        }
    }
}

void screen_reset_buffer_red( uint8_t start_byte, uint8_t length,
                                                  uint8_t circular){
    uint8_t i =0;
    buffer_update_flag = 1;
    if (state == 0) {
        //write to pong, ping being used
        for(i = 0 ; i < length ; i++){
            if (i +start_byte < sizeof(red_array_pong)) {
                red_array_pong[i +start_byte] = 0;
            } else if(circular) {
                red_array_pong[i +start_byte-sizeof(red_array_pong)] = 0;
            }
        }
    } else {
        //write to ping, pind being used
        for(i = 0 ; i < length ; i++){
            if (i + start_byte < sizeof(red_array_ping)) {
                red_array_ping[i +start_byte] = 0;
            } else if(circular) {
                red_array_ping[i +start_byte - sizeof(red_array_ping)] = 0;
            }
        }
    }
}

void screen_reset_buffer_green( uint8_t start_byte, uint8_t length,
                                                        uint8_t circular){
    uint8_t i =0;
    buffer_update_flag = 1;
    if (state == 0) {
        //write to pong, ping being used
        for(i = 0 ; i < length ; i++){
            if (i + start_byte < sizeof(green_array_pong)) {
                green_array_pong[i +start_byte] = 0;
            } else if (circular){
                green_array_pong[i +start_byte- sizeof(green_array_pong)] = 0;
            }
        }
    } else {
        //write to ping, pind being used
        for(i = 0 ; i < length ; i++){
            if (i +start_byte < sizeof(green_array_ping)) {
                green_array_ping[i +start_byte] = 0;
            } else if(circular) {
                green_array_ping[i +start_byte - sizeof(green_array_ping)] = 0;
            }
        }
    }
}

void screen_set_pixel_green( uint8_t x, uint8_t y){

    buffer_update_flag = 1;
    if (state == 0) {
        //write to pong, ping being used
        green_array_pong[y] |= 1<<(7-x);
    } else {
        green_array_ping[y] |= 1<<(7-x);
    }   

}

void screen_reset_pixel_green( uint8_t x, uint8_t y){

    buffer_update_flag = 1;
    if (state == 0) {
        //write to pong, ping being used
        green_array_pong[y] &= ~(1<<(7-x));
    } else {
        green_array_ping[y] &= ~(1<<(7-x));
    }   

}


void screen_set_pixel_red( uint8_t x, uint8_t y){

    buffer_update_flag = 1;
    if (state == 0) {
        //write to pong, ping being used
        red_array_pong[y] |= 1<<(7-x);
    } else {
        red_array_ping[y] |= 1<<(7-x);
    }   
}

void screen_reset_pixel_red( uint8_t x, uint8_t y){

    buffer_update_flag = 1;
    if (state == 0) {
        //write to pong, ping being used
        red_array_pong[y] &= ~(1<<(7-x));
    } else {
        red_array_ping[y] &= ~(1<<(7-x));
    }   

}


void screen_flush_red_buffer(){
    uint8_t i =0;
    if (state == 0) {
        //write to pong, ping being used
        memset(red_array_pong,0,sizeof(red_array_pong));
    } else {
        memset(red_array_ping,0,sizeof(red_array_ping));
    }
}

void screen_flush_green_buffer(){
    uint8_t i =0;
    if (state == 0) {
        //write to pong, ping being used
        memset(green_array_pong,0,sizeof(green_array_pong));
    } else {
        memset(green_array_pong,0,sizeof(green_array_pong));
    }
}

/*
 * ====================================
 * |          FRAME START              |
 * |red_array_1 = red_array_1_next     |
 * |green_array_1 = green_array_1_next |
 * ====================================
                 |
 *               V
 * ====================================
 * |          frame_complete_cb()      |
 * |This is where we should            |
 * | assign a new buffer               |
 * |                                   |
 * ====================================
 */

static void frame_cmplt_cb_func(){
    if (buffer_update_flag == 1) {
        buffer_update_flag = 0;
        if (state == 0){
            state = 1;
            red_array = &red_array_pong;
            green_array = &green_array_pong;
        } else if (state == 1) {
            state = 0;
            red_array = &red_array_ping;
            green_array = &green_array_ping;
        }
        display_multiplexer_set_red_array(red_array);
        display_multiplexer_set_green_array(green_array);
        state_changed_flag = 1;
    }
    
}


void screen_buffer_task(){

    /* The sole purpose of this part of the code is to clear one of the 
     * ping pong buffers that is not currently used*/
    if (state_changed_flag == 1) {
        state_changed_flag =0;
        if (state == 0) {
            //memset(&red_array_pong, 0, sizeof(red_array_pong));
            //memset(&green_array_pong, 0, sizeof(green_array_pong));
            memcpy(&red_array_pong, &red_array_ping, sizeof(red_array_pong));
            memcpy(&green_array_pong, &green_array_ping, sizeof(green_array_pong));
        } else if (state == 1) {
            //memset(&red_array_ping, 0, sizeof(red_array_ping));
            //memset(&green_array_ping, 0, sizeof(green_array_ping));
            memcpy(&red_array_ping, &red_array_pong, sizeof(red_array_ping));
            memcpy(&green_array_ping,&green_array_pong, sizeof(green_array_ping));
        }
    }
}