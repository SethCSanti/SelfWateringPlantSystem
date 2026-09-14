// Entry point, main loop
#include <Arduino.h>
#include "config.h"
#include "moisture_sensor.h"
#include "pump_control.h"

void setup()
{
    Serial.begin(115200);
    moistureSensorInit();
    pumpControlInit();
}
void loop()
{
    int moisture = readMoisturePercent();
    Serial.println(moisture);

    if (moisture < DRY_THRESHOLD)
    {
        pumpOn();
        delay(PUMP_RUN_DURATION_MS);
        pumpOff();
        delay(PUMP_COOLDOWN_MS);
    } else
    {
        delay(MOISTURE_CHECK_INTERVAL_MS);
    }
}