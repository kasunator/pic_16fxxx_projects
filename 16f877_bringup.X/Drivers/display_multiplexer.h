/* 
 * File:   display_multiplexer.h
 * Author: KBeddewela
 *
 * Created on March 10, 2024, 6:53 PM
 */


#ifndef DISPLAY_MULTIPLEXER_H
#define	DISPALY_MULTIPLEXER_H

#ifdef	__cplusplus
extern "C" {
#endif

void display_multiplexer_set_red_array(uint8_t data_buffer[]);

void display_multiplexer_set_green_array(uint8_t data_buffer[]);

uint8_t get_frame_complete_flag();

void reset_frame_complete_flag();
    
void display_multiplexer_task();



#ifdef	__cplusplus
}
#endif

#endif	/* DISPALY_MULTIPLEXER_H */

