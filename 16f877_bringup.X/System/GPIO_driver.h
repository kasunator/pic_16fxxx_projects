/* 
 * File:   GPIO_driver.h
 * Author: KBeddewela
 *
 * Created on February 7, 2024, 9:49 PM
 */

#ifndef GPIO_DRIVER_H
#define	GPIO_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

void PORTA_config();

void PORTB_config();

void PORTD_config();

void inline PORTB_int_isr();


#ifdef	__cplusplus
}
#endif

#endif	/* GPIO_DRIVER_H */

