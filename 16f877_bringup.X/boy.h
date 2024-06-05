/* 
 * File:   boy.h
 * Author: KBeddewela
 *
 * Created on May 27, 2024, 1:15 AM
 */

#ifndef BOY_H
#define	BOY_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t x:4;
    uint8_t y:4;
}dot_location_t;    
    
 dot_location_t boy_location;   
    
void boy_init();

void boy_task();


#ifdef	__cplusplus
}
#endif

#endif	/* BOY_H */

