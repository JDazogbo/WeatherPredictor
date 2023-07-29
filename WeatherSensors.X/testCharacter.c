/*
 * File:   main.c
 * Author: Josue
 *
 * Created on July 28, 2023, 4:07 PM
 */


// CONFIG
#pragma config WDTE = OFF       // Watchdog Timer (WDT disabled)
#pragma config CP = OFF         // Code Protect (Code protection off)
#pragma config MCLRE = ON      // Master Clear Enable (GP3/MCLR pin fuction is digital I/O, MCLR internally tied to VDD)
#include <xc.h>

#define _XTAL_FREQ 4000000
#define BAUD_DELAY 15

//BAUD RATE IS WAY TO HIGH (currently set up at 38400) REDUCE OR PERFORMANCE ISSUES ARE BOUND TO HAPPEND

void main(void)
{
    TRIS = 0b0000;
    GPIObits.GP0 = 1;
    while (1)
    {
        GPIObits.GP0 = 1;
        __delay_ms(100);
        GPIObits.GP0 = 0;
        __delay_us(4*BAUD_DELAY);
        
        for (unsigned char i = 0; i<8; i++)
        {
            switch (i)
            {
            case 0:
                GPIObits.GP0 = 1;
                break;
            case 1:
                GPIObits.GP0 = 0;
                break;
            case 2:
                GPIObits.GP0 = 0;
                break;
            case 3:
                GPIObits.GP0 = 0;
                break;
            case 4:
                GPIObits.GP0 = 0;
                break;
            case 5:
                GPIObits.GP0 = 0;
                break;
            case 6:
                GPIObits.GP0 = 1;
                break;
            case 7:
                GPIObits.GP0 = 0;
                break;
            }
            __delay_us(4*BAUD_DELAY);
        }
                 
    }


    return;
}
