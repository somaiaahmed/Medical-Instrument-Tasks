

# Infant Incubator Monitoring System
## Project Overview
This project involves designing a model of an infant incubator that monitors and displays temperature, humidity, and heart rate. The system includes:
- **Temperature Monitoring**: Triggers an alarm if temperature falls below the desired threshold.
- **Humidity and Heart Rate Monitoring**: Displays real-time values for infant monitoring.
- **Jaundice Detection**: Utilizes a color sensor to detect jaundice symptoms.
- **Bonus Features**:
  - Mobile notifications for abnormal conditions.
  - Additional sensors for monitoring other critical parameters (e.g., oxygen or CO₂ levels).


![incubator](<assets/infant incubator.jpg>)

## Hardware Requirements
- **Pulse Sensor**: Connected to analog pin `A1`.
- **Arduino Board**: For processing and display.
- **LED**: Pin 13, used for heartbeat indication.
- **Color Sensor**: For jaundice detection (specific pin connections vary by model).
- **Temperature and Humidity Sensors**: DHT11 or similar sensors.
- **Alarm**: Buzzer or speaker connected to a digital pin for temperature alerts.


## Running the System
1. **Connect Sensors**: Ensure proper wiring for all sensors and actuators.
2. **Upload Code**: Flash the Arduino with the provided code.
3. **Monitor Serial Output**: Use the Serial Monitor or Plotter to view heart rate and other data.
4. **Observe LED Blinking**: LED on pin 13 indicates heartbeat detection.

## Bonus Features
1. **Mobile Application Notification**: Implement an IoT connection (e.g., via Wi-Fi module) to send real-time alerts to a mobile application if the incubator environment exceeds safe limits.

![mobile app screenshot](<assets/mobile app screenshot.jpg>)
