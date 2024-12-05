# Hemodialysis Prototype ReadMe

## Project Overview

This project is a **Hemodialysis Prototype** designed to enhance patient safety during hemodialysis treatment. The system monitors multiple parameters such as temperature, flow rate, air bubbles in the circuit, blood leaks, and sudden patient movements using an Inertial Measurement Unit (IMU). If a sudden movement or abnormal conditions are detected, the system halts the dialysis circuit and raises an alert.

![hemodialysis circuit](<hemodialysis circuit.jpg>)

### Key Features:
1. **IMU-based Sudden Movement Detection**:
   - Uses an ADXL345 accelerometer to detect sudden movements, ensuring the system stops if patient motion poses a risk.

2. **Temperature Monitoring**:
   - Tracks fluid temperature using a Dallas DS18B20 sensor. If the temperature exceeds the set threshold (30°C), the system triggers an alarm.

3. **Flow Rate Monitoring**:
   - Employs a flow meter to monitor the blood flow rate. An alert is triggered if the flow rate drops below 7.3 L/min.

4. **Air-in-Line Detection**:
   - An LDR sensor identifies air bubbles in the circuit.

5. **Blood Leak Detection**:
   - Uses an RGB color sensor to detect unusual blood leakage in the circuit.

6. **Integrated Alarm System**:
   - Activates a buzzer and halts the pump in response to critical situations.

---

## Components Used

### Hardware:
- **Dallas DS18B20 Temperature Sensor**: Monitors the fluid temperature.
- **ADXL345 Accelerometer**: Detects sudden movements.
- **Flow Meter**: Measures blood flow rate.
- **RGB Color Sensor**: Detects blood leaks.
- **LDR Sensor**: Identifies air in the circuit.
- **Relay Module**: Controls the pumps.
- **Buzzer**: Provides audible alarms.
- **One meter tube**: Contains the fluids. 

### Software:
- Arduino IDE with libraries:
  - **DallasTemperature**: For DS18B20 temperature sensor.
  - **Wire**: For I2C communication with ADXL345.
  - **OneWire**: For communication with 1-Wire devices.

---

## How It Works

1. **System Initialization**:
   - Initializes all sensors and components, including the accelerometer and relay module.
   - Outputs initial status messages to the serial monitor.

2. **Real-Time Monitoring**:
   - Continuously monitors:
     - Sudden movements using the IMU.
     - Temperature via DS18B20.
     - Flow rate from the flow meter.
     - Air in the line using the LDR sensor.
     - Blood leaks with the RGB color sensor.

3. **Safety Measures**:
   - If any threshold is exceeded or a sudden movement is detected:
     - Activates the buzzer to alert.
     - Stops the pump relay to pause dialysis.
     - Outputs diagnostic messages to the serial monitor.

---

## Setup Instructions

### Hardware Setup:
1. **Connect Sensors**:
   - Wire the DS18B20 sensor to pin `A5` (analog pin).
   - Connect the flow meter pulse output to pin `5`.
   - Attach the LDR sensor to pin `A0`.
   - Connect the ADXL345 accelerometer to the I2C bus.
   - Wire the RGB sensor as per module documentation to pins `8-12`.

2. **Relay and Buzzer**:
   - Attach the relay control to pin `2`.
   - Connect the buzzer to pin `7`.

### Software Setup:
1. Install required libraries:
   - DallasTemperature
   - OneWire
2. Upload the code to the Arduino board using the Arduino IDE.

3. Open the Serial Monitor to observe system diagnostics and status.

---

## Calibration

1. **Movement Sensitivity**:
   - Adjust `MOVEMENT_THRESHOLD` to tune the sensitivity of sudden movement detection.

2. **Temperature**:
   - Modify `tempThreshold` for the maximum allowable temperature.

3. **Flow Rate**:
   - Update `flowRateThreshold` for the minimum safe flow rate.

4. **LDR Threshold**:
   - Change `ldrThreshold` for air-in-line detection sensitivity.

---

## Usage

1. **Power On**:
   - Ensure all components are connected and powered.
   - Begin dialysis simulation with the system powered on.

2. **Monitoring**:
   - Allow the system to monitor continuously.
   - Respond to any alarms promptly.

3. **Emergency Stop**:
   - The system will automatically stop the pump and alert when any unsafe condition arises.

---

## Troubleshooting

- **No Temperature Reading**:
  - Check the DS18B20 connections and ensure the sensor is operational.
- **No Movement Detection**:
  - Verify the I2C connections to the ADXL345 accelerometer.
- **Inaccurate Flow Rates**:
  - Recalibrate the flow meter or inspect for blockages.

---
