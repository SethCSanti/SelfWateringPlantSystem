// Thresholds, pin definitions, constants
#pragma once
 // -- Pin assignments --
const int MOISTURE_SENSOR_PIN = 34;
const int RELAY_PIN = 26;

// -- Moisture threshold --
const int DRY_THRESHOLD = 30; // percent (0-100), placeholder until calibrated

// -- Timing --
const unsigned long PUMP_RUN_DURATION_MS = 4000; // placeholder
const unsigned long PUMP_COOLDOWN_MS = 60000; // placeholder

const int ADC_DRY_VALUE = 0;  // raw reading in dry air
const int ADC_WET_VALUE = 0;  // raw reading fully submerged in water

const int RELAY_ON = HIGH;   // flip to LOW if relay is active-low
const int RELAY_OFF = LOW;   // flip to HIGH if relay is active-low

const int MOISTURE_CHECK_INTERVAL_MS = 120000;