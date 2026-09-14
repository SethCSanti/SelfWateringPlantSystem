// Pump on/off control via GPIO
#include <Arduino.h>
#include "pump_control.h"

#include "config.h"

void pumpControlInit()
{
    pinMode(RELAY_PIN, OUTPUT);
    pumpOff();
}

void pumpOn()
{
    digitalWrite(RELAY_PIN, RELAY_ON);
}

void pumpOff()
{
    digitalWrite(RELAY_PIN, RELAY_OFF);
}