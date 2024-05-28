/* 
 * File:   boy.c
 * Author: KBeddewela
 *
 * Created on May 27, 2024, 1:15 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic16f877a.h>

typedef struct {
    uint8_t x:4;
    uint8_t y:4;
}dot_location_t;

dot_location_t boy_location;

void boy_init(){
    boy_location.x = 4;
    boy_location.y = 0;
}