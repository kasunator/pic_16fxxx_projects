/* 
 * File:   mraquee.c
 * Author: KBeddewela
 *
 * Created on March 24, 2024, 11:50 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Drivers/display_multiplexer.h"
#include <xc.h>
#include <pic16f877a.h>
#include <string.h>
#include "System/Timer1_driver.h"
#include "marquee.h"
#include "screen_buffer.h"
#include "boy.h"

const uint8_t A[] = {0x18, 0x24, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x00};
const uint8_t B[] =  {0x3E, 0x42, 0x42, 0x3E, 0x42, 0x42, 0x3E, 0x00};
const uint8_t C[] = {0x00, 0x3E, 0x41, 0x41, 0x41, 0x22, 0x00, 0x00}; 
const uint8_t K[] = {0x42, 0x22, 0x12, 0x0E, 0x12, 0x22, 0x42, 0x00};





uint8_t scroll_timer = 0;

uint8_t scroll_index = 0;
uint8_t i = 0;

#if 0
uint8_t temp1 =0;
uint8_t temp2 =0;

uint8_t temp_g_1 = 0;
uint8_t temp_g_2 = 0;
uint8_t state = 0;
#endif 


void marquee_init(){
    

   screen_clear_bitfield_sprite_red(B, 0, sizeof(B), 1);
   scroll_timer = ms_timer_init();


}


#if 0
void marquee_task(){
    
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
        temp_g_1 = green_array[0];

        for (i =1 ; i<16; i++) {
            temp2 = red_array[i];
            temp_g_2 = green_array[i];
            red_array[i] = temp1;
            green_array[i] = temp_g_1;
            temp1 = temp2;
            temp_g_1 = temp_g_2;
        }
        red_array[0]= temp1;
        green_array[0] = temp_g_1;
        
        if (scroll_index >= 16) {
            scroll_index = 0;
        }

        //display_multiplexer_set_red_array(&red_array[0]);
        //display_multiplexer_set_green_array(&green_array[0]);
        display_multiplexer_set_red_array(red_array);
        display_multiplexer_set_green_array(green_array);
    }
}

void screen_overlay_bitfield_sprite_red( uint8_t* buffer,
                                           uint8_t start_byte, uint8_t length);

void screen_clear_bitfield_sprite_red( uint8_t* buffer, uint8_t start_byte, 
                                                               uint8_t length);
#endif 
uint8_t done= 0;
void marquee_task(){
    
    boy_task();
    
    if (ms_timer_get(scroll_timer) >= 1000 && done == 0) {
        
        //done =1;
        ms_timer_reset(scroll_timer);
        //screen_clear_bitfield_sprite_red(B, scroll_index, sizeof(B), 1);
        screen_reset_buffer_red(scroll_index, sizeof(B), 1);
        //screen_flush_red_buffer();
        scroll_index++;
        if (scroll_index > 15) {
            scroll_index = 0;
        }
        screen_overlay_bitfield_sprite_red(B, scroll_index, sizeof(B), 1);
        //screen_set_pixel_green(boy_location.x, boy_location.y);
    }
}