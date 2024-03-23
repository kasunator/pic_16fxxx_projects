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

void PORTC_config();

void PORTD_config();

void PORTE_config();

void inline set_PORTA_pins(uint8_t bit_field);
void inline set_PORTB_pins(uint8_t bit_field);
void inline set_PORTC_pins(uint8_t bit_field);
void inline set_PORTD_pins(uint8_t bit_field);
void inline set_PORTE_pins(uint8_t bit_field);

void inline clear_PORTA_pins(uint8_t bit_field);
void inline clear_PORTB_pins(uint8_t bit_field);
void inline clear_PORTC_pins(uint8_t bit_field);
void inline clear_PORTD_pins(uint8_t bit_field);
void inline clear_PORTE_pins(uint8_t bit_field);

void inline toggle_PORTA_pins(uint8_t bit_field);
void inline toggle_PORTB_pins(uint8_t bit_field);
void inline toggle_PORTC_pins(uint8_t bit_field);
void inline toggle_PORTD_pins(uint8_t bit_field);
void inline toggle_PORTE_pins(uint8_t bit_field);

void inline PORTB_int_isr();


#ifdef	__cplusplus
}
#endif

#endif	/* GPIO_DRIVER_H */

