///*
// * File:   SensorSystem.c
// * Author: JDazogbo
// *
// * Created on April 14, 2024, 7:43 PM
// *
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
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

    /* GPIO Configuration Bits */ //Clear means Output and set is Input
    clearBit(TRISIO, BLUETOOTH_TX_GPIO);
    setBit(TRISIO, BLUETOOTH_RX_GPIO); //Bluetooth RX has to be on GPIO2 for the Interrupt
    clearBit(TRISIO, BMP_SCL_GPIO);
    
    /* Register Configuration Bits */
    ANSEL = 0b00000000; //Sets the analog/digital choice to digital for every pin
    INTCONbits.GIE = 1; //Global Interupt Enable
    INTCONbits.PEIE = 1; //Enables Peripheral Interrupts
    
    //For Bluetooth Interrupts
    INTCONbits.INTE = 1; //Interrupt on GPIO2 Enabled
    INTCONbits.INTF = 0; //Clear GPIO2 interrupt flag bit
    OPTION_REGbits.INTEDG = 0; //Interrupt on Falling Edge
    
    //For BMP I2C Timer Interrupts
    T2CONbits.T2CKPS = 0b11; //Setting the prescaler for the Timer
    T2CONbits.TOUTPS = 0b0; //Setting the Interrupt Post Scaler
    T2CONbits.TMR2ON = 0; //The timer is Off
    PIE1bits.TMR2IE = 1; //Enable Timer 2 Interupts
    PIR1bits.TMR2IF = 0; //Clear Timer 2 Flag bit
    
    
    
    
    /* GPIO Default Values */
    setBit(GPIO, BLUETOOTH_TX_GPIO);
    
    #endif //MICROCONTROLLER
    CONSOLE_PRINT("\033c"); //Clear Screen
    CONSOLE_PRINT("#~~~~~~~~~~~~~~~~~~~~~~~~#\n\r  Weather Sensor Console\n\r#~~~~~~~~~~~~~~~~~~~~~~~~#\r\n");
    pSensorSystem->next_operation = &run_sleep;
}
void run_sleep(SensorSystem* pSensorSystem)
{
    pSensorSystem->current_state = SLEEP;
    CONSOLE_PRINT("\n\rHC-05> ");
    DEBUG_PRINT("\n\rDevice was sent to sleep\n\r");
    SLEEP();
    switch (message_buffer)
    {
        case 'P':
            pSensorSystem->next_operation = &run_report_serial;
            break;
        case 'S':
            startClock();
            SLEEP_FOR_MS(100);
            SLEEP_FOR_MS(100);
            SLEEP_FOR_MS(100);
            SLEEP_FOR_MS(100);
            stopClock();
            pSensorSystem->next_operation = &run_sleep;
            break;
        default:
            CONSOLE_PRINT("\n\rError: Message is not Valid\n\r");
            pSensorSystem->next_operation = &run_sleep;
            break;
    }

}
void run_measure_data(SensorSystem* pSensorSystem)
{
    pSensorSystem->current_state = MEASURE_DATA;
    DEBUG_PRINT("Measuring Data\n\r");
    
    #if MICROCONTROLLER
    startClock();
    stopClock();
    #endif //MICROCONTROLLER

    DEBUG_PRINT("Data Measured\n\r");
    pSensorSystem->next_operation = &run_sleep;
}
void run_report_serial(SensorSystem* pSensorSystem)
{
    pSensorSystem->current_state = REPORT_SERIAL;
    DEBUG_PRINT("Sending Data to HC-05 Bluetooth Sensor\n\r");
    CONSOLE_PRINT("\n\rTemperature: ");
    CONSOLE_PRINT("\n\rPressure: ");
    CONSOLE_PRINT("\n\rHumidity: ");
    CONSOLE_PRINT("\n\r");
    pSensorSystem->next_operation = &run_sleep;
}

int main() {
    SensorSystem sys = {NULL_STATE, &run_boot_up, &message_buffer};
    
    while (1)
    {
        sys.next_operation(&sys);
    }
        

}

#if MICROCONTROLLER

//Interrupt subroutine for the device
void __interrupt() interrupt_subroutine(void)
{
    if (INTCONbits.INTF) //Bluetooth Character is Received
    {
        readChar(&message_buffer);
        INTCONbits.INTF = 0;   
    }
    if (PIR1bits.TMR2IF) //BMP SCL has incremented to the period
    {
        notBit(GPIO, BMP_SCL_GPIO);
        TMR2 = 0;
        PIR1bits.TMR2IF = 0;
    }

}
#endif //MICROCONTROLLER
