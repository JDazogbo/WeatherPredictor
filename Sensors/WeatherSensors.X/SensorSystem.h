/* 
 * File:   SensorSystem.h
 * Author: JDazogob
 *
 * Created on April 13, 2024, 6:30 PM
 */

#ifndef SENSORSYSTEM_H
#define	SENSORSYSTEM_H

/* Main System Configuration Components */
#define _XTAL_FREQ 8000000//Clock frequency of the uC

/* Bluetooth Sensor Define Statements */
#define BAUD_RATE 38400
#define BAUD_EXTRA_DELAY 2
#define BAUD_DELAY_TX 1000000/BAUD_RATE//This value in seconds might be higher than the theoretical value. Check with tests value to validate.
#define BAUD_DELAY_RX 1000000/(BAUD_RATE)-15//The Delay is considered to be slightly lower than the TX value. Play with these values for optimal performance

#define BLUETOOTH_TX_GPIO 0//Pin that transmits info to the HC-05 module
#define BLUETOOTH_RX_GPIO 2//Pin that receives signals from HC-05 module





#endif	/* SENSORSYSTEM_H */

