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
#include "BluetoothUART.h"

#define _XTAL_FREQ 4000000

//BAUD RATE IS WAY TO HIGH (currently set up at 38400) REDUCE OR PERFORMANCE ISSUES ARE BOUND TO HAPPEND
//The Putty Interpreter is in UTF8 but when using the Char from the pic compiler, the characters will be transformed with
//  the ASCII conversion

void main(void)
{
    initialize();
    for (unsigned char i = 0; 1; i++)
    {
        sendChar(0b10100110);
        __delay_ms(10);
    }


    return;
}
