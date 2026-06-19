# 🌱 Self-Watering Plant System

An embedded automated irrigation system using an **ESP32** and capacitive soil moisture sensing to control a water pump via real-time threshold-based feedback. Built in C++ (Arduino/ESP32 framework), with an optional IoT monitoring upgrade via WiFi/MQTT.

---

## 🎯 Project Goal

Build a fully autonomous plant watering system that:
- Reads soil moisture levels via an analog capacitive sensor
- Triggers a mini submersible water pump when moisture drops below a threshold
- Runs reliably on an ESP32 microcontroller with no manual intervention
- (Optional) Reports live data to a cloud dashboard over WiFi

---

## 🔩 Hardware Components

| Component | Part | Specs |
|---|---|---|
| **Microcontroller** | LAFVIN ESP32 Starter Kit (ESP-32S) | WiFi + Bluetooth, Arduino IDE compatible |
| **Soil Moisture Sensor** | DIYables Capacitive Soil Moisture Sensor (×4) | TLC555I chip, 3.3–5.5V, corrosion-resistant |
| **Water Pump** | SIPYTOPF DC 3–5V Mini Submersible Pump (×4) | 80–120 L/H flow rate, max 110cm lift, brushless DC |
| **Tubing** | Clear PVC Vinyl Tubing (×2, 1M each) | Included with pump kit, 7.5mm OD / 4.5mm ID outlet |
| **Power Supply** | TBD (batteries or USB) | Must supply 3–5V to pump; 3.3V to sensor |
| **Switching Element** | Relay module or transistor (TBD) | To switch pump power from ESP32 GPIO signal |
| **Water Reservoir** | TBD (container/bottle) | Holds water supply for the pump |

> **Note:** The ESP32 GPIO pins cannot directly drive the pump at the required current (150–250mA). A relay module or MOSFET transistor is required between the GPIO output and the pump.

---

## 📁 Repository Structure

```
self-watering-plant/
├── src/
│   ├── main.cpp              # Entry point, main loop
│   ├── moisture_sensor.cpp   # Sensor read + calibration logic
│   ├── moisture_sensor.h
│   ├── pump_control.cpp      # Pump on/off control via GPIO
│   ├── pump_control.h
│   └── config.h              # Thresholds, pin definitions, constants
├── docs/
│   ├── wiring_diagram.png    # Circuit schematic
│   └── calibration_notes.md  # Sensor dry/wet value readings
├── README.md
└── platformio.ini            # (or Arduino sketch config)
```

---

## ⚙️ System Architecture

```
[Soil Moisture Sensor]
        |
        | Analog voltage (ADC)
        ▼
    [ESP32]
        |
        | GPIO digital out → [Relay/Transistor]
        |                           |
        |                    [Water Pump] ← [Reservoir]
        |                           |
        |                        [Tubing]
        |                           |
        |                       [Plant Pot]
        |
        | (Optional) WiFi → [MQTT Broker / Cloud Dashboard]
```

---

## 🏗️ Part 1: Physical / Hardware

Everything needed to assemble the circuit and physical setup.

### To-Do

- [ ] **Identify switching component** — decide between a relay module or MOSFET transistor for pump control (relay is simpler; MOSFET is faster/quieter)
- [ ] **Choose a power source** — USB power bank, wall adapter, or battery pack capable of sustaining 3–5V at ~250mA for the pump
- [ ] **Build wiring diagram** — document all connections: sensor VCC/GND/AOUT → ESP32, ESP32 GPIO → relay/transistor → pump, power rails
- [ ] **Set up the reservoir** — select a container, position the pump inside, and route tubing to the plant
- [ ] **Mount/position the moisture sensor** — insert sensor prongs into soil at root depth; keep the circuit board (top portion) above soil/water level to avoid damage
- [ ] **Verify sensor operating voltage** — sensor runs 3.3–5.5V; confirm which ESP32 pin is used for VCC (3.3V rail recommended for ESP32 compatibility)
- [ ] **Test pump manually** — connect pump directly to a power source to confirm it works before integrating with ESP32
- [ ] **Verify pump lift height** — pump max lift is ~110cm; ensure the reservoir-to-plant height is within range
- [ ] **Waterproof/insulate connections** — any connections near water should be protected (heat shrink, electrical tape, etc.)

---

## 💻 Part 2: Firmware / Code (C++)

All logic running on the ESP32. Language: **C++** (Arduino framework).

### To-Do

#### Setup & Configuration
- [ ] **Set up development environment** — install Arduino IDE or PlatformIO, add ESP32 board support package
- [ ] **Define pin constants in `config.h`** — moisture sensor ADC pin, pump control GPIO pin, threshold values
- [ ] **Confirm ADC configuration for ESP32** — the ESP32 ADC requires 11dB attenuation to handle the sensor's full 3.3V output range (see DIYables sensor note)

#### Sensor Module (`moisture_sensor.cpp/.h`)
- [ ] **Read raw ADC value** — use `analogRead()` on the sensor's AOUT pin
- [ ] **Calibrate the sensor** — record ADC values in dry air and fully saturated soil; map raw value to a 0–100% moisture percentage
- [ ] **Implement averaging** — take multiple ADC samples per reading and average them to reduce noise
- [ ] **Document calibration values** in `docs/calibration_notes.md`

#### Pump Control Module (`pump_control.cpp/.h`)
- [ ] **Implement `pumpOn()` / `pumpOff()` functions** — write HIGH/LOW to the GPIO pin controlling the relay/transistor
- [ ] **Add a minimum run duration** — run the pump for a fixed duration (e.g., 3–5 seconds) per trigger rather than continuously
- [ ] **Add a cooldown period** — prevent the pump from retriggering immediately after watering (debounce / delay loop)

#### Main Control Loop (`main.cpp`)
- [ ] **Implement the feedback control loop** — read moisture → compare to threshold → trigger pump if dry → wait → repeat
- [ ] **Set and tune the moisture threshold** — define a `DRY_THRESHOLD` value in `config.h`; adjust based on plant species and sensor calibration
- [ ] **Add serial logging** — print moisture readings and pump state to Serial Monitor for debugging
- [ ] **Handle edge cases** — sensor disconnected, pump stuck on, reservoir empty (detect via run-time limits)

#### Testing
- [ ] **Unit test sensor reads** — verify ADC outputs sensible values across dry/wet conditions
- [ ] **Test pump trigger logic** — confirm pump activates only below threshold and shuts off correctly
- [ ] **End-to-end test** — run full system in a real pot and observe one complete dry → water → recover cycle

---

## 🌐 Part 3: IoT Upgrade (Optional)

Extend the system with WiFi reporting using the ESP32's built-in wireless capability.

### To-Do

- [ ] **Connect to WiFi** — use `WiFi.h` to connect ESP32 to a local network
- [ ] **Choose a protocol** — MQTT (lightweight, good for IoT) or HTTP REST (simpler)
- [ ] **Set up a broker / backend** — options include a local Mosquitto MQTT broker, AWS IoT Core, or Firebase
- [ ] **Publish sensor data** — send moisture %, pump state, and timestamp on each reading cycle
- [ ] **Build or connect a dashboard** — Node-RED, Grafana, or a simple web page to visualize readings over time
- [ ] **Add remote threshold control** — subscribe to an MQTT topic to update the moisture threshold without reflashing
- [ ] **Handle WiFi reconnection** — add logic to reconnect if the connection drops

---

## 📋 Concepts Demonstrated

- Analog sensor reading via ADC
- GPIO output control (sensor-actuator loop)
- Threshold-based feedback control systems
- Embedded decision-making and automation
- (Optional) Device-to-cloud IoT communication

---

## 📚 Resources

- [ESP32 Arduino Core Docs](https://docs.espressif.com/projects/arduino-esp32/en/latest/)
- [DIYables Soil Moisture Sensor Tutorial](https://www.amazon.com/dp/B0D2K9YP1K) — search "DIYables Soil Moisture Sensor" for official tutorials
- [LAFVIN ESP32 Starter Kit Tutorial](https://www.amazon.com/dp/B0BVZBTP8V) — tutorial download included with kit
- [SIPYTOPF Pump Specs](https://www.amazon.com/dp/B0CJFQ5KDT) — DC 3–5V, 80–120 L/H, max 110cm lift

---

## 📝 Notes

- Do **not** bury the circuit board portion of the moisture sensor in soil or water — only the prongs go in
- Do **not** use pure/distilled water for testing the sensor; it won't conduct electricity and will give inaccurate readings
- The pump is rated for ≥200 continuous hours but is **not** recommended for truly uninterrupted operation — the duty-cycle approach (short bursts) in this design is intentional
- Sensor ADC readings vary based on probe insertion depth, soil composition, supply voltage, and ADC reference — calibration per deployment is important
