/*
 * File:   testCharacter.c
 * Author: JDazogbo
 *
 * Created on July 28, 2023, 4:07 PM
 */


// CONFIG
#pragma config WDTE = OFF       // Watchdog Timer (WDT disabled)
#pragma config CP = OFF         // Code Protect (Code protection off)
#pragma config MCLRE = ON      // Master Clear Enable (GP3/MCLR pin fuction is digital I/O, MCLR internally tied to VDD)
#include <xc.h>

#include "SensorSystem.h"
#include "HC05.h"

#define PIC12F683

void main(void)
{
    TRISIO = 0b0010;
    setBit(GPIO, BLUETOOTH_TX_GPIO);    
    unsigned char temp;
    while(1)
    {

        for (unsigned char i = 48; i<123; i++)
        {
            sendChar(i);
            __delay_ms(200);
        }
    }


    return;
}
