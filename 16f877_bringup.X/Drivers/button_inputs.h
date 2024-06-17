/* 
 * File:   button_inputs.h
 * Author: KBeddewela
 *
 * Created on March 10, 2024, 6:51 PM
 */

#ifndef BUTTON_INPUTS_H
#define	BUTTON_INPUTS_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <xc.h>
#include <pic16f877a.h>

typedef struct {
    uint8_t up:1;
    uint8_t down:1;
    uint8_t left:1;
    uint8_t right:1;
    uint8_t btn_A:1;
    uint8_t btn_B:1;
}btn_bit_field_t;

typedef struct {
    uint8_t scan_counter;
    uint8_t up:1;
    uint8_t down:1;
    uint8_t left:1;
    uint8_t right:1;
    uint8_t btn_A:1;
    uint8_t btn_B:1;
}btn_repeat_bit_field_t;

btn_bit_field_t btn_bit_field;

btn_repeat_bit_field_t btn_repeat_bit_field;

    
inline uint8_t  button_up();

inline uint8_t  button_down();


inline uint8_t  button_left();

inline uint8_t  button_right();


inline uint8_t  button_A();

inline uint8_t  button_B();

void button_inputs_init();

void button_input_task();

#ifdef	__cplusplus
}
#endif

#endif	/* BUTTON_INPUTS_H */

