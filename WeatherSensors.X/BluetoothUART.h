/* 
 * File:   BluetoothUART.h
 * Author: Josue
 *
 * Created on July 29, 2023, 7:11 PM
 */

#ifndef BLUETOOTHUART_H
#define	BLUETOOTHUART_H

//Imports
#include <xc.h>


//Parameter Variables
#define BAUD_DELAY 85 //This value in seconds might be lower than the theoretical value. Check with tests value to validate. 
#define BLUETOOTH_TX_GPIO 0//Pin that transmits info to the HC-05 module
#define _XTAL_FREQ 4000000

//Usefull Macros
#define setBit(variable, position) ((variable) |= 1 << (position))
#define clearBit(variable, position) ((variable) &= ~(1 << position))
#define notBit(variable, position) ((variable) ^= 1UL << (position))
#define checkBit(variable, position) ((variable>>position)&(1UL) == 1UL)
#define checkLSB(variable) (variable & 1UL)
#define checkMSB (variable) (variable<<8)

void initialize()
{
    TRIS = 0b0000;
    setBit(GPIObits.GP0, BLUETOOTH_TX_GPIO);
}


void sendChar(unsigned char character)
{
//    //Start with the Start bit. This value indicates when the communication starts
//    clearBit(GPIObits.GP0, BLUETOOTH_TX_GPIO); 
//    __delay_us(BAUD_DELAY);
//    for (unsigned char i = 8; i>0; i--)
//    {
//        
//        checkBit(character, i-1)? setBit(GPIObits.GP0, BLUETOOTH_TX_GPIO): clearBit(GPIObits.GP0, BLUETOOTH_TX_GPIO);
//        __delay_us(BAUD_DELAY);
//    }
//    __delay_us(BAUD_DELAY/2);
//    setBit(GPIObits.GP0, BLUETOOTH_TX_GPIO);
//    __delay_us(BAUD_DELAY);
    
    //Version of the code that sends the byte with greater precision but looks uglier

    unsigned char temp = 0;
    unsigned char temp2 = character;
    for (unsigned char i = 8; i>0; i--)
    {
        temp = checkLSB(temp2)? temp*2+1: temp*2;
        temp2 = temp2>>1;
        
    }
    character = temp;
    GPIObits.GP0 = 0;
    __delay_us(BAUD_DELAY);
    GPIObits.GP0 = checkLSB(character);
    character = character>>1;
    __delay_us(BAUD_DELAY);
    GPIObits.GP0 = checkLSB(character);
    character = character>>1;
    __delay_us(BAUD_DELAY);
    GPIObits.GP0 = checkLSB(character);
    character = character>>1;
    __delay_us(BAUD_DELAY);
    GPIObits.GP0 = checkLSB(character);
    character = character>>1;
    __delay_us(BAUD_DELAY);
    GPIObits.GP0 = checkLSB(character);
    character = character>>1;
    __delay_us(BAUD_DELAY);
    GPIObits.GP0 = checkLSB(character);
    character = character>>1;
    __delay_us(BAUD_DELAY);
    GPIObits.GP0 = checkLSB(character);
    character = character>>1;
    __delay_us(BAUD_DELAY);
    GPIObits.GP0 = checkLSB(character);
    character = character>>1;
    __delay_us(BAUD_DELAY);
    setBit(GPIObits.GP0, BLUETOOTH_TX_GPIO);
    __delay_us(BAUD_DELAY);
    
}



#ifdef	__cplusplus
extern "C" {
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* BLUETOOTHUART_H */

