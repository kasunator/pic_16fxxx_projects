/* 
 * File:   display_multiplexer.c
 * Author: KBeddewela
 *
 * Created on March 10, 2024, 6:48 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "../System/Timer_driver.h"
#include "../System/GPIO_driver.h"

/*
 ------- clk2 end ------
 * matrix 2 is called U1 in hardware
 matrix 2 col 8 green         green_array_1[15]
 matrix 2 col 8 red           red_array_1[15]
 
 matrix 2 col 5 green       green_array_1[12]
 matrix 2 col 5 red         red_array_1[12]
-------clk2 start-------
--------clk1 end--------
 matrix 2 col 4 green  green_array_1[11]
 matrix 2 col 4 red    red_array_1[11]
 .
 matrix 2 col 1 green   green_array_1[8]
 matrix 2 col 1 red     red_array_1[8]
 ------- clk1 start------
 ========================
 -----clk4 end ----------
 *matrix 1 is called U2 in hardware
 matrix 1  col 8 green  green_array_1[7]   
 matrix 1 col 8 red     red_array_1[7]
 
 matrix 1 col 5 green   green_array_1[4]
 matrix 1 col 5 red     red_array_1[4]
 -------clk4 start--------
--------clk3 end----------
 matrix 1 col 4 green   green_array_1[3]
 matrix 1 col 4 red     red_array_1[3]
 .
 matrix 1 col 1 green green_array_1[0]
 matrix 1 col 1 red   red_array_1[0]   
 clk3 start 
 */

#define LINE_PERIOD 20 /*20 ms this would be equivalen to horizontal frequency of Tv*/
#define  TOTAL_HORIZONTAL 32
#define TOTAL_LINES_PER_COLOR 16
#define CLK3_BOUNDRY 7
#define CLK4_BOUNDRY 15
#define CLK1_BOUNDRY 23 
#define CLK2_BOUNDRY 31 

typedef enum{
    INIT,
    RESET_STATE,
    RUN_STATE
}enum_mltplxr_state;
/*
uint8_t ms_timer_init();
void ms_timer_reset(uint8_t timer_handle);
uint32_t ms_timer_get(uint8_t timer_handle);
*/
static uint8_t mltplxr_state = 0;
static uint8_t timer_handle = 0xFF;


static void set_row_pattern(uint8_t *pattern){
    set_PORTD_pins(*pattern);
}

static uint8_t* red_array_1;
static uint8_t* green_array_1;
//static uint8_t* red_array_2;
//static uint8_t* green_array_2;

static uint8_t* red_array_1_next;
static uint8_t* green_array_1_next;
//static uint8_t* red_array_2_next;
//static uint8_t* green_array_2_next;

static uint8_t horizontal_index =0;
static uint8_t red_index = 0;
static uint8_t green_index = 0;
static uint8_t frame_complete_flag = 0;

void display_multiplexer_set_red_array(uint8_t data_buffer[])
{
    red_array_1_next = data_buffer;
}

void display_multiplexer_set_green_array(uint8_t data_buffer[])
{
    green_array_1_next = data_buffer;
}

uint8_t get_frame_complete_flag()
{
    return frame_complete_flag;
}
void reset_frame_complete_flag()
{
    frame_complete_flag = 0;
}

/*void display_multiplexer_set_red_2_array(uint8_t data_buffer[])
{
    red_array_2_next = data_buffer;
}*/

/*void display_multiplexer_set_green_2_array(uint8_t data_buffer[])
{
    green_array_2_next = data_buffer;
}*/

void display_multiplexer_task()
{
    switch(mltplxr_state){
    case INIT:
        timer_handle = ms_timer_init();
        ms_timer_reset(timer_handle);
        mltplxr_state = RUN_STATE;
        break;
    case RESET_STATE:
        ms_timer_reset(timer_handle);
        horizontal_index = 0;
        red_index = 0;
        green_index = 0;
        red_array_1 = red_array_1_next; 
        green_array_1 = green_array_1_next;
        mltplxr_state = RUN_STATE;
        break;
    case RUN_STATE:
        if (ms_timer_get(timer_handle) >LINE_PERIOD) {
            ms_timer_reset(timer_handle);

            
            if (horizontal_index < TOTAL_HORIZONTAL) {
                /* if the horizontal index in odd then 
                * we should show green, else red 
                */
                if (horizontal_index & 0x01) { /* show green*/
                    set_row_pattern(green_array_1[TOTAL_LINES_PER_COLOR - green_index]);
                    green_index++;
                } else { /* show red */
                    set_row_pattern(red_array_1[TOTAL_LINES_PER_COLOR -  red_index]);
                    red_index++;
                }
                if ( horizontal_index > 0 && horizontal_index <= CLK3_BOUNDRY) {
                    //toggle clk 3
                } else if (horizontal_index <= CLK4_BOUNDRY ) {
                    //toggle clk 4
                } else if (horizontal_index <= CLK1_BOUNDRY) {
                    //toggle clk 1
                } else if (horizontal_index <= CLK2_BOUNDRY) {
                    //toggle clk 2
                } 
                
                horizontal_index++; /*increment the horizontal index */
            } else {
                frame_complete_flag  = 1;
                mltplxr_state = RESET_STATE;
            }
        }
        break;
    }
}