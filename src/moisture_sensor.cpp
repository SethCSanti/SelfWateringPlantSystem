// Sensor read + calibration logic
#include <Arduino.h>
#include "config.h"

const int NUM_SAMPLES = 10;

void moistureSensorInit()
{
    analogSetPinAttenuation(MOISTURE_SENSOR_PIN, ADC_11db);
}

int readMoisturePercent()
{
    int samples[NUM_SAMPLES];
    int total = 0;
    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        samples[i] = analogRead(MOISTURE_SENSOR_PIN);
        total += samples[i];
    }
    int avg = total / NUM_SAMPLES;
    int percent = map(avg, ADC_DRY_VALUE, ADC_WET_VALUE, 0, 100);
    return constrain(percent, 0, 100);
}