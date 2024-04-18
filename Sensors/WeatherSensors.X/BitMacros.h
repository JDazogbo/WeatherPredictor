/* 
 * File:   BitMacros.h
 * Author: JDazogbo

 * Created on April 17, 2024, 10:46 AM
 * Macros Used All throughout the Programs
 * 
 */


//Usefull Macros
#define setBit(variable, position) ((variable) |= 1 << (position))
#define clearBit(variable, position) ((variable) &= ~(1 << position))
#define notBit(variable, position) ((variable) ^= 1UL << (position))
#define checkBit(variable, position) ((variable>>position)&(1UL) == 1UL)
#define checkLSB(variable) (variable & 1UL)
#define checkMSB (variable) (variable<<8)