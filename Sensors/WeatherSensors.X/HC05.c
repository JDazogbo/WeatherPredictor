/* 
 * File:   HC05.c
 * Author: JDazogbo
 *
 * Created on April 23, 2024, 8:08 AM
 */

#include "HC05.h"

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
    *pResult = 0;
    __delay_us(BAUD_DELAY_RX/2);
    for (unsigned char i = 0; i<8; i++)
    {
        __delay_us(BAUD_DELAY_RX); //NOTE: The delay here seems to be lower than the actual send rate delay. Play with values to get a correct output.
        *pResult |= checkBit(GPIO, BLUETOOTH_RX_GPIO);
        *pResult = *pResult<<1;
    }
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