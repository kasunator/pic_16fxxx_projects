/* 
 * File:   Timer0_driver.h
 * Author: KBeddewela
 *
 * Created on April 23, 2024, 11:05 PM
 */

#ifndef TIMER0_DRIVER_H
#define	TIMER0_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
void Timer0_config();

void inline Timer0_isr();



#ifdef	__cplusplus
}
#endif

#endif	/* TIMER0_DRIVER_H */

