/* 
 * File:   HC05.h
 * Author: JDazogbo

 * Created on July 29, 2023, 7:11 PM
 * 
 * NOTE: The HC-05 Module sends the bits in REVERSE ORDER of what they truly are. Reverse the byte's order (Msb becomes lsb and vice-versa)
 *       to correctly interpret what the message is truly saying. This is true when a byte is read and when a byte is sent.
 */

#ifndef HC05
#define	HC05

//Imports
#include <xc.h>
#include "Typedefs.h"
#include "BitMacros.h"
#include "SensorSystem.h"

void reverseByte(uint8 *pByte)
{
    //Code that reverses the character before sending it to the GPIO.
    uint8 temp = 0;
    uint8 temp2 = *pByte;
    for (uint8 i = 8; i>0; i--)
    {
        temp = checkLSB(temp2)? temp*2+1: temp*2;
        temp2 = temp2>>1;
        
    }
    *pByte = temp;
}


void readChar(uint8 *pResult)
{
    //Add a delay for the first initial bit. This delay is useless for the pic10f200 as the pic is too slow
    
    //Reads a bit at a time and waits for the value.
    for (uint8 i = 8; i>0; i--)
    {
        
        checkBit(GPIO, BLUETOOTH_RX_GPIO)? setBit(*pResult, i): clearBit(*pResult, i);
        __delay_us(BAUD_DELAY_RX); //NOTE: The delay here seems to be lower than the actual send rate delay. Play with values to get a correct output.
    }
    //Reverses the byte when the value is known
    reverseByte(pResult);
}

void sendChar(uint8 character)
{
    //Version of the Code that is optimized for space. Use delay of 50 for baud rate 9600 on PIC10F200
    
    //Reverse the byte to begin with
    reverseByte(&character);
    
    //Start with the Start bit. This value indicates when the communication starts
    clearBit(GPIObits.GP0, BLUETOOTH_TX_GPIO); 
    __delay_us(BAUD_DELAY_TX);
    
    //Change the GPIO depending on the bit
    for (uint8 i = 8; i>0; i--)
    {
        
        checkBit(character, i-1)? setBit(GPIObits.GP0, BLUETOOTH_TX_GPIO): clearBit(GPIObits.GP0, BLUETOOTH_TX_GPIO);
        __delay_us(BAUD_DELAY_TX);
    }
    
    //Set the end bit
    __delay_us(BAUD_DELAY_TX+30); //We add a constant delay to take into account the time it takes to run the for loop instruction
    setBit(GPIObits.GP0, BLUETOOTH_TX_GPIO);
    __delay_us(BAUD_DELAY_TX);
    
}


#endif	/* HC05 */

