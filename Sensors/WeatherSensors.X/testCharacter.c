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

unsigned char charBuffer;
unsigned long long temp;

void main(void)
{
    TRISIO = 0b0100;
    
    //Lookup how to clear interrupt flags
    ANSEL = 0b00000000; //Sets the analog/digital choice to digital for every pin
    INTCONbits.INTF = 0; //Clear interrupt bit for good measure
    OPTION_REGbits.INTEDG = 0; //Interrupt on Falling Edge
    INTCONbits.GIE = 1;
    INTCONbits.INTE = 1; //Interrupt on Change Enable
    
    setBit(GPIO, BLUETOOTH_TX_GPIO);
    charBuffer = 0b01010101;
    while(1)
    {
//        sendChar(charBuffer);
        __delay_us(250);
    }
    
    


    return;
}

//Interrupt subroutine
void __interrupt() interrupt_service_routine(void)
{   
    setBit(GPIO, BLUETOOTH_TX_GPIO);
    clearBit(GPIO, BLUETOOTH_TX_GPIO);
    readChar(&charBuffer);
    INTCONbits.INTF = 0;
}