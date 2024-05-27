/* 
 * File:   display_multiplexer.c
 * Author: KBeddewela
 *
 * Created on March 10, 2024, 6:48 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "../System/Timer1_driver.h"
#include "../System/GPIO_driver.h"
#include "../System/Timer0_driver.h"
#include "display_multiplexer.h"

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

#define LINE_PERIOD 1 /*20 ms this would be equivalen to horizontal frequency of Tv*/
//#define MINIMUM_PULSE_WIDTH 4 /* one milli second */
#define MINIMUM_PULSE_WIDTH 4

#define  TOTAL_HORIZONTAL 32
//#define  TOTAL_HORIZONTAL 16
#define TOTAL_LINES_PER_COLOR 16
#define CLK3_BOUNDRY 7
#define CLK4_BOUNDRY 15
#define CLK1_BOUNDRY 23 
#define CLK2_BOUNDRY 31 
/*4017 minimum reset pulse width 260 ns, removal time 400ns */

#define RESET_MATRIX_PIN_BITFIELD  0x04//RE2 
#define CLK3_PIN_BITFIELD 0x10  //RA4
#define CLK4_PIN_BITFIELD 0x01//RC0
#define CLK1_PIN_BITFIELD 0x01//RE0
#define CLK2_PIN_BITFIELD  0x02//RE1

typedef enum{
    INIT,
    RESET_STATE,
    INITIAL_RESET,
    FRAME_START,
    NEXT_COLUMN,
    CLOCK_HIGH_DELAY,
    LED_DELAY,
    RESET_HIGH_DELAY
}enum_mltplxr_state;
/*
uint8_t ms_timer_init();
void ms_timer_reset(uint8_t timer_handle);
uint32_t ms_timer_get(uint8_t timer_handle);
*/
static uint8_t mltplxr_state = 0;
static uint8_t timer_handle = 0xFF;
static uint8_t pulse_timer_handle = 0xFF;




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
static uint8_t reset_pulse_flag = 0;

void display_multiplexer_set_red_array(uint8_t data_buffer[])
{
    red_array_1_next = data_buffer;
}

void display_multiplexer_set_green_array(uint8_t data_buffer[])
{
    green_array_1_next = data_buffer;
}

inline uint8_t get_frame_complete_flag()
{
    return frame_complete_flag;
}
inline void reset_frame_complete_flag()
{
    frame_complete_flag = 0;
}

inline void set_row_pattern(uint8_t pattern){
    set_PORTD_pins(pattern);
}



static inline void set_reset_matrix()
{
    set_PORTE_pins(RESET_MATRIX_PIN_BITFIELD);
}

static inline void reset_reset_matrix()
{
    clear_PORTE_pins(RESET_MATRIX_PIN_BITFIELD);
}

static inline void set_clk_1()
{
    set_PORTE_pins(CLK1_PIN_BITFIELD);
}

static inline void reset_clk_1()
{
    clear_PORTE_pins(CLK1_PIN_BITFIELD);
}

static inline void set_clk_2()
{
    set_PORTE_pins(CLK2_PIN_BITFIELD);
}

static inline void reset_clk_2()
{
    clear_PORTE_pins(CLK2_PIN_BITFIELD);
}
/* clk3 is port RA4 which has only internal pull down, 
 * so we have to put and external pull up resistor
 * so set and reset is inverted i.e we have to clear the GPIO to
 * make the clk go high and set the gpio high to  make the clk go low    */
static inline void set_clk_3()
{
    //clear_PORTA_pins(CLK3_PIN_BITFIELD);
    set_PORTA_pins(CLK3_PIN_BITFIELD);
}

static inline void reset_clk_3()
{
    //set_PORTA_pins(CLK3_PIN_BITFIELD);
    clear_PORTA_pins(CLK3_PIN_BITFIELD);
}

static inline void set_clk_4()
{
    set_PORTC_pins(CLK4_PIN_BITFIELD);
}

static inline void reset_clk_4()
{
    clear_PORTC_pins(CLK4_PIN_BITFIELD);
}
/*void display_multiplexer_set_red_2_array(uint8_t data_buffer[])
{
    red_array_2_next = data_buffer;
}*/

/*void display_multiplexer_set_green_2_array(uint8_t data_buffer[])
{
    green_array_2_next = data_buffer;
}*/


#if 0
void display_multiplexer_task()
{
    switch(mltplxr_state){
    case INIT:
        //timer_handle = ms_timer_init();
        //pulse_timer_handle = ms_timer_init();
        /* reset all the lines */
        reset_clk_1();
        reset_clk_2();
        reset_clk_3();
        reset_clk_4();
        mltplxr_state = RESET_STATE;
        break;
    case RESET_STATE:
        set_reset_matrix();
        reset_pulse_flag = 1;
        /* wait for clock high delay for the reset line*/
        mltplxr_state = CLOCK_HIGH_DELAY;
        break;
    case FRAME_START:
        horizontal_index = 0;
        red_index = 0;
        green_index = 0;
        red_array_1 = red_array_1_next; 
        green_array_1 = green_array_1_next;
        set_row_pattern(red_array_1[(TOTAL_LINES_PER_COLOR-1) - red_index]);
        red_index++;
        horizontal_index++;
        //ms_timer_reset(pulse_timer_handle);
        reset_timer0_flag();
        set_clk_3();
        mltplxr_state = CLOCK_HIGH_DELAY;
        break;
    case NEXT_COLUMN:
        //if (ms_timer_get(timer_handle) >LINE_PERIOD) {
        //    ms_timer_reset(timer_handle);
        //    ms_timer_reset(pulse_timer_handle);
        if (get_timer0_flag() == 1) {
            reset_timer0_flag();
            if (horizontal_index < TOTAL_HORIZONTAL) {
                /* if the horizontal index in odd then 
                * we should show green, else red 
                */
#if 0
                if (horizontal_index & 0x01) {
                    /* show green*/
                    set_row_pattern(green_array_1[(TOTAL_LINES_PER_COLOR-1) - green_index]);
                    green_index++;
                } else { /* show red */
                    set_row_pattern(red_array_1[(TOTAL_LINES_PER_COLOR-1) - red_index]);
                    red_index++;
                }
#endif 
                
                if ( horizontal_index > 0 && horizontal_index <= CLK3_BOUNDRY) {
                    //set clk 3
                    set_clk_3();
                } else if (horizontal_index == CLK3_BOUNDRY + 1){
                    /* we have to make clk3 go and park at 9*/
                    set_clk_3(); 
                }
                
                
                if (horizontal_index > CLK3_BOUNDRY && horizontal_index <= CLK4_BOUNDRY ) {
                    //set clk 4
                    set_clk_4();
                } else if (horizontal_index == CLK4_BOUNDRY + 1) {
                    /* we have to make clk4 go and park at 9*/
                    set_clk_4(); 
                }
                
                
                if (horizontal_index > CLK4_BOUNDRY && horizontal_index <= CLK1_BOUNDRY) {
                    //set clk 1
                    set_clk_1();
                } else if (horizontal_index == CLK1_BOUNDRY + 1) {
                    /* we have to make clk1 go and park at 9*/
                    set_clk_1(); 
                } 
                
                
                if (horizontal_index > CLK1_BOUNDRY && horizontal_index <= CLK2_BOUNDRY) {
                    //set clk 2
                    set_clk_2();
                } else if (horizontal_index == CLK2_BOUNDRY + 1) {
                    /* we have to make clk2 go and park at 9*/
                    set_clk_2();
                }
                
                horizontal_index++; /*increment the horizontal index */
                mltplxr_state = CLOCK_HIGH_DELAY;
            } else {
                frame_complete_flag  = 1;
                set_reset_matrix();
                reset_pulse_flag = 1;
                mltplxr_state = CLOCK_HIGH_DELAY;
            }
        }
        break;
    case CLOCK_HIGH_DELAY:
        //if (ms_timer_get(pulse_timer_handle) >MINIMUM_PULSE_WIDTH ){
        if (get_timer0_flag() == 1) {
            reset_timer0_flag();
            
            if (horizontal_index & 0x01) {
                    /* show green*/
                    set_row_pattern(green_array_1[(TOTAL_LINES_PER_COLOR-1) - green_index]);
                    green_index++;
            } else { /* show red */
                    set_row_pattern(red_array_1[(TOTAL_LINES_PER_COLOR-1) - red_index]);
                    red_index++;
            }
                  
            reset_reset_matrix();
            reset_clk_1();
            reset_clk_2();
            reset_clk_3();
            reset_clk_4();
            if (reset_pulse_flag == 1) {
                reset_pulse_flag = 0;
                mltplxr_state = FRAME_START;
            } else {
                mltplxr_state = NEXT_COLUMN;
            }
            //ms_timer_reset(timer_handle);
        }
    break;
    }
}
#endif 

void display_multiplexer_task()
{
    switch(mltplxr_state){
    case INIT:
        //timer_handle = ms_timer_init();
        //pulse_timer_handle = ms_timer_init();
        /* reset all the lines */
        reset_clk_1();
        reset_clk_2();
        reset_clk_3();
        reset_clk_4();
        mltplxr_state = RESET_STATE;
        break;
    case RESET_STATE:
        set_reset_matrix();
        /* wait for clock high delay for the reset line*/
        reset_timer0_flag();
        mltplxr_state = INITIAL_RESET;
        break;
    case INITIAL_RESET:
        if (get_timer0_flag() == 1) {
            reset_reset_matrix();
            /* wait for clock high delay for the reset line*/
            mltplxr_state = FRAME_START;
        }
        break;
    case FRAME_START:
        horizontal_index = 0;
        red_index = 0;
        green_index = 0;
        red_array_1 = red_array_1_next; 
        green_array_1 = green_array_1_next;
        //set_row_pattern(red_array_1[(TOTAL_LINES_PER_COLOR-1) - red_index]);
        //red_index++;
        //horizontal_index++;
        //ms_timer_reset(pulse_timer_handle);
        reset_timer0_flag();
        set_clk_3();
        mltplxr_state = CLOCK_HIGH_DELAY;
        break;
    case LED_DELAY:
        if (get_timer0_flag() == 1) {
            reset_timer0_flag();
            //reset_reset_matrix();
           // reset_clk_1();
           // reset_clk_2();
           // reset_clk_3();
           // reset_clk_4();
            mltplxr_state = NEXT_COLUMN;
        }
        break;
    case NEXT_COLUMN:
        //if (ms_timer_get(timer_handle) >LINE_PERIOD) {
        //    ms_timer_reset(timer_handle);
        //    ms_timer_reset(pulse_timer_handle);
        if (get_timer0_flag() == 1) {
            reset_timer0_flag();
            if (horizontal_index < TOTAL_HORIZONTAL) {
                /* blank first*/
                 set_row_pattern(0x00);
                /* if the horizontal index in odd then 
                * we should show green, else red 
                */
                if ( horizontal_index > 0 && horizontal_index <= CLK3_BOUNDRY) {
                    //set clk 3
                    set_clk_3();
                } else if (horizontal_index == CLK3_BOUNDRY + 1){
                    /* we have to make clk3 go and park at 9*/
                    set_clk_3(); 
                }

                if (horizontal_index > CLK3_BOUNDRY && horizontal_index <= CLK4_BOUNDRY ) {
                    //set clk 4
                    set_clk_4();
                } else if (horizontal_index == CLK4_BOUNDRY + 1) {
                    /* we have to make clk4 go and park at 9*/
                    set_clk_4(); 
                }

                if (horizontal_index > CLK4_BOUNDRY && horizontal_index <= CLK1_BOUNDRY) {
                    //set clk 1
                    set_clk_1();
                } else if (horizontal_index == CLK1_BOUNDRY + 1) {
                    /* we have to make clk1 go and park at 9*/
                    set_clk_1(); 
                } 

                if (horizontal_index > CLK1_BOUNDRY && horizontal_index <= CLK2_BOUNDRY) {
                    //set clk 2
                    set_clk_2();
                } else if (horizontal_index == CLK2_BOUNDRY + 1) {
                    /* we have to make clk2 go and park at 9*/
                    set_clk_2();
                }

                //horizontal_index++; /*increment the horizontal index */
                mltplxr_state = CLOCK_HIGH_DELAY;
            } else {
                set_row_pattern(0x00);
                frame_complete_flag  = 1;
                set_reset_matrix();
                reset_pulse_flag = 1;
                mltplxr_state = RESET_HIGH_DELAY;
            }
        }
        break;
    case CLOCK_HIGH_DELAY:
        //if (ms_timer_get(pulse_timer_handle) >MINIMUM_PULSE_WIDTH ){
        if (get_timer0_flag() == 1) {
            reset_timer0_flag();
            
            if (horizontal_index & 0x01) {
                    /* show green*/
                    set_row_pattern(green_array_1[(TOTAL_LINES_PER_COLOR-1) - green_index]);
                    green_index++;
            } else { /* show red */
                    set_row_pattern(red_array_1[(TOTAL_LINES_PER_COLOR-1) - red_index]);
                    red_index++;
            }
            horizontal_index++;    
            reset_reset_matrix();
            reset_clk_1();
            reset_clk_2();
            reset_clk_3();
            reset_clk_4();
            
            //if (reset_pulse_flag == 1) {
            //   reset_pulse_flag = 0;
            //   mltplxr_state = FRAME_START;
            //} else {
            //    mltplxr_state = NEXT_COLUMN;
            //}
            //ms_timer_reset(timer_handle);
           mltplxr_state = LED_DELAY;
        }
        break;
    case RESET_HIGH_DELAY:
        if (get_timer0_flag() == 1) {
            reset_timer0_flag();
            reset_reset_matrix();
            mltplxr_state = FRAME_START;
        }
        break;
    }
}


void show_Test_line()
{
    set_row_pattern(0xFF);
}

void reset_lines(){
    reset_reset_matrix();
}