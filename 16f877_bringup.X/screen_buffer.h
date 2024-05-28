/* 
 * File:   screen_buffer.h
 * Author: KBeddewela
 *
 * Created on May 27, 2024, 1:40 AM
 */

#ifndef SCREEN_BUFFER_H
#define	SCREEN_BUFFER_H

#ifdef	__cplusplus
extern "C" {
#endif

void screen_buffer_init();

void screen_overlay_bitfield_sprite_red( uint8_t* buffer, uint8_t start_byte,
                                         uint8_t length, uint8_t circular);

void screen_clear_bitfield_sprite_red( uint8_t* buffer, uint8_t start_byte, 
                                               uint8_t length, uint8_t circular);

void screen_overlay_bitfield_sprite_green( uint8_t* buffer, uint8_t start_byte,
                                                uint8_t length, uint8_t circular);

void screen_clear_bitfield_sprite_green( uint8_t* buffer, uint8_t start_byte,
                                                uint8_t length, uint8_t circular);

void screen_reset_buffer_red( uint8_t start_byte, uint8_t length, uint8_t circular);

void screen_reset_buffer_green( uint8_t start_byte, uint8_t length, uint8_t circular);

void screen_buffer_task();


#ifdef	__cplusplus
}
#endif

#endif	/* SCREEN_BUFFER_H */

