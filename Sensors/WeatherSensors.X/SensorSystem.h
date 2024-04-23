/* 
 * File:   SensorSystem.h
 * Author: JDazogbo
 *
 * Created on April 13, 2024, 6:30 PM
 */

#ifndef SENSORSYSTEM
#define	SENSORSYSTEM

/* Includes Statements Dependent */
#include "Typedefs.h"
#include "BitMacros.h"

#if WINDOWS
#include <stdio.h>
#endif //WINDOWS

#if MICROCONTROLLER
#include <xc.h>
#include "HC05.h"
#endif //MICROCONTROLLER


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
    NULL_MESSAGE = 0,
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
    volatile message* message_buffer; 
    uint8 measurements[NUMBER_OF_MEASUREMENTS];
};

/* State Functions for The system */

void run_boot_up(SensorSystem* pSensorSystem);
void run_sleep(SensorSystem* pSensorSystem);
void run_measure_data(SensorSystem* pSensorSystem);
void run_report_serial(SensorSystem* pSensorSystem);

/* Print Macros for Execution */
#if MICROCONTROLLER

#define CONSOLE_PRINT(string) sendString(string) //Prints to HC-05 module
#define DEBUG_PRINT(string) DEBUG_MODE ? sendString(string) : 0 //Prints to HC-05 module if debug mode is enabled

#endif	//MICROCONTROLLER

#if WINDOWS

#define CONSOLE_PRINT(string) printf(string) //Prints to Command Prompt
#define DEBUG_PRINT(string) DEBUG_MODE ? printf(string) : 0 //Prints to Command Prompt if debug mode is enabled

#endif //WINDOWS

/* Sleep Commands */
#if MICROCONTROLLER

#define SLEEP() asm("sleep") //Places the board to sleep and waits for an interrupt
#define SLEEP_FOR_MS(time) __delay_ms(time) //Places the board in sleep for a certain ammount of miliseconds

#endif	//MICROCONTROLLER

#if WINDOWS

#define SLEEP() 0 //Empty instruction on windows
#define SLEEP_FOR_MS(time) 0 //Empty instruction on windows

#endif //WINDOWS

#endif //SENSORSYSTEM

