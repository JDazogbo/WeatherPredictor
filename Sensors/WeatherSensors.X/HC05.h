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
    __delay_us(BAUD_DELAY_RX/2);
    unsigned char temp;
    for (unsigned char i = 0; i<8; i++)
    {
        __delay_us(BAUD_DELAY_RX); //NOTE: The delay here seems to be lower than the actual send rate delay. Play with values to get a correct output.
        checkBit(GPIO, BLUETOOTH_RX_GPIO)
    }
    
    
    
    for (unsigned char i = 8; i>0; i--)
    {
        __delay_us(BAUD_DELAY_RX); //NOTE: The delay here seems to be lower than the actual send rate delay. Play with values to get a correct output.
        checkBit(GPIO, BLUETOOTH_RX_GPIO)? setBit(*pResult, i): clearBit(*pResult, i);
        setBit(GPIO, BLUETOOTH_TX_GPIO);
        clearBit(GPIO, BLUETOOTH_TX_GPIO);
        
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
    clearBit(GPIO, BLUETOOTH_TX_GPIO); 
    __delay_us(BAUD_DELAY_TX);
    
    //Change the GPIO depending on the bit
    for (uint8 i = 8; i>0; i--)
    {
        
        checkBit(character, i-1)? setBit(GPIO, BLUETOOTH_TX_GPIO): clearBit(GPIO, BLUETOOTH_TX_GPIO);
        __delay_us(BAUD_DELAY_TX);
    }
    
    //Set the end bit
    __delay_us(BAUD_DELAY_TX);
    setBit(GPIO, BLUETOOTH_TX_GPIO);
    
}
void sendString(unsigned char str[])
{
    unsigned char i = 0;
    while (str[i] != '\0')
    {
        sendChar(str[i]);
        i = i+1;
    }
}


#ifdef	__cplusplus
extern "C" {
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* HC05_H */

