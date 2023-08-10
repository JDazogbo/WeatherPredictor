/* 
 * File:   BluetoothUART.h
 * Author: JDazogbo

 * Created on July 29, 2023, 7:11 PM
 * 
 * NOTE: The HC-05 Module sends the bits in REVERSE ORDER of what they truly are. Reverse the byte's order (Msb becomes lsb and vice-versa)
 *       to correctly interpret what the message is truly saying. This is true when a byte is read and when a byte is sent.
 */

#ifndef BLUETOOTHUART_H
#define	BLUETOOTHUART_H

//Imports
#include <xc.h>


//Parameter Variables
#define BAUD_DELAY_TX 50 //This value in seconds might be lower than the theoretical value. Check with tests value to validate.
#define BAUD_DELAY_RX BAUD_DELAY_TX-5
#define BLUETOOTH_TX_GPIO 0//Pin that transmits info to the HC-05 module
#define BLUETOOTH_RX_GPIO 1//Pin that receives signals from HC-05 module
#define _XTAL_FREQ 4000000

//Usefull Macros
#define setBit(variable, position) ((variable) |= 1 << (position))
#define clearBit(variable, position) ((variable) &= ~(1 << position))
#define notBit(variable, position) ((variable) ^= 1UL << (position))
#define checkBit(variable, position) ((variable>>position)&(1UL) == 1UL)
#define checkLSB(variable) (variable & 1UL)
#define checkMSB (variable) (variable<<8)


void reverseByte(unsigned char *pByte)
{
    //Code that reverses the character before sending it to the GPIO
    unsigned char temp = 0;
    unsigned char temp2 = *pByte;
    for (unsigned char i = 8; i>0; i--)
    {
        temp = checkLSB(temp2)? temp*2+1: temp*2;
        temp2 = temp2>>1;
        
    }
    *pByte = temp;
}


void readChar(unsigned char *pResult)
{
//    __delay_us(BAUD_DELAY/2); //We add a constant delay to take into account the time it takes to run the for loop instruction
    for (unsigned char i = 8; i>0; i--)
    {
        
        checkBit(GPIO, BLUETOOTH_RX_GPIO)? setBit(*pResult, i): clearBit(*pResult, i);
        __delay_us(BAUD_DELAY_RX); //NOTE: The delay here seems to be lower than the actual send rate delay. Play with values to get a correct output.
    }
    //Code that reverses the character before sending it to the GPIO
    reverseByte(pResult);
}

void sendChar(unsigned char character)
{
    //Version of the Code that is optimized for space. Use delay of 50 for baud rate 9600 on PIC10F200
    //Start with the Start bit. This value indicates when the communication starts
    //Code that reverses the character before sending it to the GPIO

    reverseByte(&character);
    clearBit(GPIObits.GP0, BLUETOOTH_TX_GPIO); 
    __delay_us(BAUD_DELAY_TX);
    for (unsigned char i = 8; i>0; i--)
    {
        
        checkBit(character, i-1)? setBit(GPIObits.GP0, BLUETOOTH_TX_GPIO): clearBit(GPIObits.GP0, BLUETOOTH_TX_GPIO);
        __delay_us(BAUD_DELAY_TX);
    }
    
    __delay_us(BAUD_DELAY_TX+30); //We add a constant delay to take into account the time it takes to run the for loop instruction
    setBit(GPIObits.GP0, BLUETOOTH_TX_GPIO);
    __delay_us(BAUD_DELAY_TX);

    
    
    
    
//    //Version of the code that respects the baud rate more but looks uglier. Use this if higher baud rate is required. Use delay of 85 for baud 9600 on PIC10F200.
//  
//    //Code that reverses the character before sending it to the GPIO
//    unsigned char temp = 0;
//    unsigned char temp2 = character;
//    for (unsigned char i = 8; i>0; i--)
//    {
//        temp = checkLSB(temp2)? temp*2+1: temp*2;
//        temp2 = temp2>>1;
//        
//    }
//    character = temp;
    
//    //Code that actually sends the signal
//    
//    GPIObits.GP0 = 0;
//    __delay_us(BAUD_DELAY_TX);
//    GPIObits.GP0 = checkLSB(character);
//    character = character>>1;
//    __delay_us(BAUD_DELAY_TX);
//    GPIObits.GP0 = checkLSB(character);
//    character = character>>1;
//    __delay_us(BAUD_DELAY_TX);
//    GPIObits.GP0 = checkLSB(character);
//    character = character>>1;
//    __delay_us(BAUD_DELAY_TX);
//    GPIObits.GP0 = checkLSB(character);
//    character = character>>1;
//    __delay_us(BAUD_DELAY_TX);
//    GPIObits.GP0 = checkLSB(character);
//    character = character>>1;
//    __delay_us(BAUD_DELAY_TX);
//    GPIObits.GP0 = checkLSB(character);
//    character = character>>1;
//    __delay_us(BAUD_DELAY_TX);
//    GPIObits.GP0 = checkLSB(character);
//    character = character>>1;
//    __delay_us(BAUD_DELAY_TX);
//    GPIObits.GP0 = checkLSB(character);
//    character = character>>1;
//    __delay_us(BAUD_DELAY_TX);
//    setBit(GPIObits.GP0, BLUETOOTH_TX_GPIO);
//    __delay_us(BAUD_DELAY_TX);
    
    
}




#ifdef	__cplusplus
extern "C" {
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* BLUETOOTHUART_H */

