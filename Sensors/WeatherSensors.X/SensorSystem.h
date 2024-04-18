/* 
 * File:   SensorSystem.h
 * Author: Josue
 *
 * Created on April 13, 2024, 6:30 PM
 */

#ifndef SENSORSYSTEM
#define	SENSORSYSTEM


#include "Typedefs.h"
#include "BitMacros.h"

#if WINDOWS
#include <stdio.h>
#endif //WINDOWS

#if MICROCONTROLLER
#include <xc.h>
#endif //MICROCONTROLLER

/* Main System Configuration Components */
#define _XTAL_FREQ 8000000//Clock frequency of the uC

/* Bluetooth Sensor Define Statements */
#define BAUD_RATE 38400
#define BAUD_EXTRA_DELAY 2
#define BAUD_DELAY_TX 1000000/BAUD_RATE + BAUD_EXTRA_DELAY //This value in seconds might be higher than the theoretical value. Check with tests value to validate.
#define BAUD_DELAY_RX BAUD_DELAY_TX//The Delay is considered to be slightly lower than the TX value. Play with these values for optimal performance
#define BLUETOOTH_TX_GPIO 0//Pin that transmits info to the HC-05 module
#define BLUETOOTH_RX_GPIO 1//Pin that receives signals from HC-05 module


/* Measurement Define Statements */
#define TEMPERATURE_INDEX 0
#define PRESSURE_INDEX 1
#define HUMIDITY_INDEX 2
#define NUMBER_OF_MEASUREMENTS 3

/* Data Types Used in System */
typedef struct SensorSystem SensorSystem;
typedef void (*operation)(SensorSystem*);

typedef enum state
{
    NULL_STATE,
    BOOT_UP,
    SLEEP,
    MEASURE_DATA,
    REPORT_SERIAL
} state;

typedef enum message
{
    NULL_MESSAGE,
    //Data Measurement Messages
    UPDATE_TEMPERATURE,
    UPDATE_HUMIDITY,
    UPDATE_PRESSURE,
    RETURN_TEMPERATURE,
    RETURN_HUMIDITY,
    RETURN_PRESSURE
    //Error Messages
} message;


struct SensorSystem
{
    state current_state;
    operation next_operation;
    message message_buffer; 
    uint8 measurements[NUMBER_OF_MEASUREMENTS];
};

/* State Functions for The system */

void run_boot_up(SensorSystem* pSensorSystem);
void run_sleep(SensorSystem* pSensorSystem);
void run_measure_data(SensorSystem* pSensorSystem);
void run_report_serial(SensorSystem* pSensorSystem);

/* Print Macros for Execution */
#if MICROCONTROLLER

#define CONSOLE_PRINT(string) sendString(string)
#define DEBUG_PRINT(string) DEBUG_MODE ? sendString(string) : 0

#endif	//MICROCONTROLLER

#if WINDOWS

#define CONSOLE_PRINT(string) printf(string)
#define DEBUG_PRINT(string) DEBUG_MODE ? printf(string) : 0

#endif //WINDOWS

#endif //SENSORSYSTEM

