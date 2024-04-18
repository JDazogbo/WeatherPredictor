#include "SensorSystem.h"

#define DEBUG_MODE 1

void run_boot_up(SensorSystem* pSensorSystem)
{
    pSensorSystem->current_state = BOOT_UP;
    DEBUG_PRINT("Booting Up Device\n");
    DEBUG_PRINT("Device Was Boot\n");
    pSensorSystem->next_operation = &run_sleep;
}
void run_sleep(SensorSystem* pSensorSystem)
{
    pSensorSystem->current_state = SLEEP;
    DEBUG_PRINT("Device was sent to sleep\n");
    pSensorSystem->next_operation = &run_measure_data;
    
}
void run_measure_data(SensorSystem* pSensorSystem)
{
    pSensorSystem->current_state = MEASURE_DATA;
    DEBUG_PRINT("Measuring Data\n");
    DEBUG_PRINT("Data Measured\n");
    pSensorSystem->next_operation = &run_report_serial;
}
void run_report_serial(SensorSystem* pSensorSystem)
{
    pSensorSystem->current_state = REPORT_SERIAL;
    DEBUG_PRINT("Sending Data to HC-05 Bluetooth Sensor\n");
    DEBUG_PRINT("\n");
    pSensorSystem->next_operation = &run_sleep;
}

int main() {
    SensorSystem sys = {NULL_STATE, &run_boot_up, NULL_MESSAGE};
    
    for (uint8 i = 0; i < 30; i++ )
    {
        sys.next_operation(&sys);
    }
    return 0;
}