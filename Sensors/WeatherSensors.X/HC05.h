/* 
 * File:   HC05.h
 * Author: JDazogbo

 * Created on July 29, 2023, 7:11 PM
 * 
 * NOTE: The HC-05 Module sends the bits in REVERSE ORDER of what they truly are. Reverse the byte's order (Msb becomes lsb and vice-versa)
 *       to correctly interpret what the message is truly saying. This is true when a byte is read and when a byte is sent.
 */

#ifndef HC05_H
#define	HC05_H

//Imports
#include <xc.h>
#include "Typedefs.h"
#include "BitMacros.h"
#include "SystemConfiguration.h"

void reverseByte(uint8 *pByte);
void readChar(uint8 *pResult);
void sendChar(uint8 character);
void sendString(uint8 str[]);
char decodeInt(uint8 integer);

#endif	/* HC05_H */

