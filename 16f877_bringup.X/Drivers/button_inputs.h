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
    
inline uint8_t  button_up();

inline uint8_t  button_down();


inline uint8_t  button_left();

inline uint8_t  button_right();


inline uint8_t  button_A();

inline uint8_t  button_B();


#ifdef	__cplusplus
}
#endif

#endif	/* BUTTON_INPUTS_H */

