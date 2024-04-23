///*
// * File:   SensorSystem.c
// * Author: JDazogbo
// *
// * Created on April 14, 2024, 7:43 PM
// *
#pragma config FOSC = INTOSCCLK // Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select bit (MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Detect (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)

#include "SensorSystem.h"

#define DEBUG_MODE 1 //Toggle for Debug Prints and Commands

message message_buffer = NULL_MESSAGE;

void run_boot_up(SensorSystem* pSensorSystem)
{
    pSensorSystem->current_state = BOOT_UP;
    
    #if MICROCONTROLLER

    /* Register Configuration Bits */
    TRISIO = 0b0100; //Sets GP0 -> Output, GP2 -> Input 
    ANSEL = 0b00000000; //Sets the analog/digital choice to digital for every pin
    INTCONbits.INTF = 0; //Clear interrupt bit
    OPTION_REGbits.INTEDG = 0; //Interrupt on Falling Edge
    INTCONbits.GIE = 1; //Global Interupt Enable
    INTCONbits.INTE = 1; //Interrupt on GPIO2 Enabled
    
    /* GPIO Default Values */
    setBit(GPIO, BLUETOOTH_TX_GPIO);
    
    #endif //MICROCONTROLLER
    CONSOLE_PRINT("\033c"); //Clear Screen
    SLEEP_FOR_MS(100);
    CONSOLE_PRINT("####\n\rWeather Sensor Console\n\r####\r\n");
    pSensorSystem->next_operation = &run_sleep;
}
void run_sleep(SensorSystem* pSensorSystem)
{
    pSensorSystem->current_state = SLEEP;
    DEBUG_PRINT("Device was sent to sleep\n\r");
    SLEEP();
    pSensorSystem->next_operation = &run_measure_data;
}
void run_measure_data(SensorSystem* pSensorSystem)
{
    pSensorSystem->current_state = MEASURE_DATA;
    DEBUG_PRINT("Measuring Data\n\r");
    DEBUG_PRINT("Data Measured\n\r");
    pSensorSystem->next_operation = &run_report_serial;
}
void run_report_serial(SensorSystem* pSensorSystem)
{
    pSensorSystem->current_state = REPORT_SERIAL;
    DEBUG_PRINT("Sending Data to HC-05 Bluetooth Sensor\n\r");
    pSensorSystem->next_operation = &run_sleep;
}

int main() {
    SensorSystem sys = {NULL_STATE, &run_boot_up, &message_buffer};
    
    for (uint8 i = 0; i < 30; i++ )
    {
        sys.next_operation(&sys);
    }
    return 0;
}

#if MICROCONTROLLER

//Interrupt subroutine for the HC-05 Module
void __interrupt() received_character(void)
{   
    readChar(&message_buffer);
    INTCONbits.INTF = 0;   
}
#endif //MICROCONTROLLER
