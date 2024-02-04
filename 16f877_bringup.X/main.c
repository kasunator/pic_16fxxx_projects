/*
 * File:   main.c
 * Author: KBeddewela
 *
 * Created on February 4, 2024, 1:47 PM
 */

#include <xc.h>
#include <pic16f877a.h>
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

void delay(){
    int count = 10000;
    while (count) {
        count--;
    }

    
}


static void PORTA_config()
{
    /* first we set all the outptus to 0
     before we configire them, as outputs
    */
    PORTA = 0x00; /* port A is 5 bits long */
    /* Setting '1' a TRISA to make the pin input (defualt on reset)
     * Resetting '0' a TRISA to 0 makes the pin ouput */
    
    //TRISA = 0x1F;/* tris  a is also 5 bits long  we can use 0b11111 notation also*/
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    /* the ADCCON1's bits 0 to 4 handles the ADC configration*/
    ADCON1 = 0x06; /* PCF<3:0> = 0b011x means all are DIGITAL pins*/ 
    
}

static void PORTA_toggle_RA1()
{
    PORTAbits.RA0 ^= 1;
}

uint8_t read_value = 0;
void main(void) {
    //RP0
   
    PORTA_config();
    PORTAbits.RA0 = 1;
    PORTAbits.RA1 = 1;
    
    
    while (1)
    {
        delay();
        PORTA ^= 0x03;
        //PORTA = 0x01;
        //PORTA_toggle_RA1();
       /* read_value = PORTA;
        PORTAbits.RA0 = 1;
        PORTAbits.RA1 = 1; 
        delay();
        read_value = PORTA;
        PORTAbits.RA0 = 0;
        PORTAbits.RA1 = 0; */
    }
}