/* 
 * File:   newmain.c
 * Author: KBeddewela
 *
 * Created on March 10, 2024, 6:49 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic16f877a.h>

/* button UP PORTB 0*/
inline uint8_t  button_up()
{
    return PORTBbits.RB0;
}

/* button Down PORTB 1*/
inline uint8_t  button_down()
{
    return PORTBbits.RB1;
}

/* button Left PORTB 2*/
inline uint8_t  button_left()
{
    return PORTBbits.RB2;
}


/* button Right PORTB 3*/
inline uint8_t  button_right()
{
    return PORTBbits.RB3;
}

/* button A PORTB 4*/
inline uint8_t  button_A()
{
    return PORTBbits.RB4;
}

/* button B PORTB 5*/
inline uint8_t  button_B()
{
    return PORTBbits.RB5;
}