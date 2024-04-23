/* 
 * File:   SystemConfiguration.h
 * Author: JDazogbo
 *
 * Created on April 23, 2024, 7:47 AM
 */

#ifndef SYSTEMCONFIGURATION_H
#define	SYSTEMCONFIGURATION_H

/* Main System Configuration Components */
#define _XTAL_FREQ 8000000//Clock frequency of the uC

/* Bluetooth Sensor Define Statements */
#define BAUD_RATE 9600
#define BAUD_EXTRA_DELAY 15
#define BAUD_DELAY_TX 27//This value in seconds might be higher than the theoretical value. Check with tests value to validate.
#define BAUD_DELAY_RX 27//The Delay is considered to be slightly lower than the TX value. Play with these values for optimal performance

#define BLUETOOTH_TX_GPIO 0//Pin that transmits info to the HC-05 module
#define BLUETOOTH_RX_GPIO 2//Pin that receives signals from HC-05 module

#endif	/* SYSTEMCONFIGURATION_H */

