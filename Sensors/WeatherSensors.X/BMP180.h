/* 
 * File:   BMP180.h
 * Author: JDazogbo
 *
 * Created on April 25, 2024, 6:41 AM
 */

#ifndef BMP180_H
#define	BMP180_H

#include <xc.h>
#include "Typedefs.h"
#include "BitMacros.h"
#include "SystemConfiguration.h"

#define startClock() setBit(T2CON, 2) //Bit 2 of T2CON is TMR2ON
#define stopClock() clearBit(T2CON, 2)


#endif	/* BMP180_H */

