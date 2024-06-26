/* 
 * File:   Timer_driver.h
 * Author: KBeddewela
 *
 * Created on February 7, 2024, 10:10 PM
 */

#ifndef TIMER1_DRIVER_H
#define	TIMER1_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <xc.h>
    
void Timer1_config();

void inline Timer1_isr();

uint16_t get_global_time_ms();

void reset_global_time();

uint8_t ms_timer_init();

void ms_timer_reset(uint8_t timer_handle);

uint32_t ms_timer_get(uint8_t timer_handle);

void ms_timer_task();

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER1_DRIVER_H */

