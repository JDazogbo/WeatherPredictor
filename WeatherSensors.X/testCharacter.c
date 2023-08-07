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



void main(void)
{
    TRIS = 0b0010;
    setBit(GPIObits.GP0, BLUETOOTH_TX_GPIO);
    unsigned char temp;
    while(1)
    {
        if (GPIObits.GP1 == 0)
        {
            readChar(&temp);
            sendChar(temp);
            __delay_ms(10);
        }

    }


    return;
}
