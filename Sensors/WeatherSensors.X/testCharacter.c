///*
// * File:   testCharacter.c
// * Author: JDazogbo
// *
// * Created on July 28, 2023, 4:07 PM
// */
//
//
//// CONFIG
//#pragma config FOSC = INTOSCCLK // Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
//#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
//#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
//#pragma config MCLRE = OFF      // MCLR Pin Function Select bit (MCLR pin function is digital input, MCLR internally tied to VDD)
//#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
//#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
//#pragma config BOREN = OFF      // Brown Out Detect (BOR disabled)
//#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode is disabled)
//#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
//
//#include <xc.h>
//#include "SensorSystem.h"
//
//#define PIC12F683
//
//unsigned char charBuffer;
//unsigned long long temp;
//
//void main(void)
//{
//    TRISIO = 0b0100; //Sets GP0 -> Output, GP2 -> Input 
//    ANSEL = 0b00000000; //Sets the analog/digital choice to digital for every pin
//    INTCONbits.INTF = 0; //Clear interrupt bit
//    OPTION_REGbits.INTEDG = 0; //Interrupt on Falling Edge
//    INTCONbits.GIE = 1; //Global Interupt Enable
//    INTCONbits.INTE = 1; //Interrupt on GPIO2 Enabled
//    
//    setBit(GPIO, BLUETOOTH_TX_GPIO);
//    charBuffer = 0b01010101;
//    while(1)
//    {
//        asm("sleep");
//    }
//    
//    
//
//
//    return;
//}
//
////Interrupt subroutine
//void __interrupt() interrupt_service_routine(void)
//{   
//    readChar(&charBuffer);
//    sendChar(charBuffer);
//    INTCONbits.INTF = 0;
//    
//}