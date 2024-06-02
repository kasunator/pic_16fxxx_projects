/* 
 * File:   display_multiplexer.h
 * Author: KBeddewela
 *
 * Created on March 10, 2024, 6:53 PM
 */


#ifndef DISPLAY_MULTIPLEXER_H
#define	DISPLAY_MULTIPLEXER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <pic16f877a.h>
    
    
void display_multiplexer_set_red_array(uint8_t data_buffer[]);

void display_multiplexer_set_green_array(uint8_t data_buffer[]);

inline uint8_t get_frame_complete_flag();

inline void reset_frame_complete_flag();
    
void display_multiplexer_task();

void show_Test_line();

typedef void (*frame_cmplt_cb_t)();

void set_frame_cmplt_cb(frame_cmplt_cb_t cb);

//static inline void set_row_pattern(uint8_t pattern);

//static inline void set_reset_matrix();

//static inline void reset_reset_matrix();

//static inline void set_clk_1();

//static inline void reset_clk_1();

//static inline void set_clk_2();

//static inline void reset_clk_2();

//static inline void set_clk_3();

//static inline void reset_clk_3();

//static inline void set_clk_4();

//static inline void reset_clk_4();


#ifdef	__cplusplus
}
#endif

#endif	/* DISPALY_MULTIPLEXER_H */

