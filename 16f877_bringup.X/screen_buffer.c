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
uint8_t buffer_timer;
uint8_t buffer_update_flag = 0;
/*
 * 
 */
void screen_buffer_init(){
    memset(&red_array_ping, 0, 16 );
    memset(&green_array_ping, 0, 16 );
    
    memset(&red_array_pong, 0, 16);
    memset(&green_array_pong, 0, 16);
   
    //display_multiplexer_set_red_array(&red_array_ping[0]);
    //display_multiplexer_set_green_array(&green_array_ping[0]);
    display_multiplexer_set_red_array(&red_array_pong[0]);
    display_multiplexer_set_green_array(&green_array_pong[0]);
    buffer_timer = ms_timer_init();
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



void screen_buffer_task(){

    if (ms_timer_get(buffer_timer) >= 100) {
        ms_timer_reset(buffer_timer);

        if (state == 0 && buffer_update_flag ==1){
            buffer_update_flag = 0;
            //memcpy(&red_array_pong, &red_array_ping, sizeof(red_array_ping));
            //memcpy(&green_array_pong, &green_array_ping, sizeof(green_array_ping));
            //memcpy(&red_array_ping, &red_array_pong, sizeof(red_array_ping));
            //memcpy(&green_array_ping, &green_array_pong, sizeof(green_array_ping));
            red_array = &red_array_pong;
            green_array = &green_array_pong;
            state = 1;
        } else if (state == 1 && buffer_update_flag == 1) {
            buffer_update_flag = 0;
            //memcpy(&red_array_ping, &red_array_pong, sizeof(red_array_ping));
            //memcpy(&green_array_ping, &green_array_pong, sizeof(green_array_ping));
            //memcpy(&red_array_pong, &red_array_ping, sizeof(red_array_ping));
            //memcpy(&green_array_pong, &green_array_ping, sizeof(green_array_ping));
            red_array = &red_array_ping;
            green_array = &green_array_ping;
            state = 0;
        }

        //display_multiplexer_set_red_array(&red_array[0]);
        //display_multiplexer_set_green_array(&green_array[0]);
        display_multiplexer_set_red_array(red_array);
        display_multiplexer_set_green_array(green_array);
    }

}