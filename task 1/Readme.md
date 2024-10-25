
# ECG Data Acquisition and Analysis

## Statement
The objective of this project is to acquire ECG data using an ECG sensor or by simulating the ECG circuit. The program calculates the heart rate, determines whether the heart rhythm is regular or irregular, explains the rhythm analysis reasoning, and calculates any errors. Additionally, the ECG signal is visualized and analyzed.

## Hardware Requirements
- **Pulse Sensor**: Connected to Analog Pin A1
- **Arduino**: Arduino board with LED indicator on pin 13

## Variables Used in the Code
- **PulseSensorPurplePin** (`A1`): Analog pin where the ECG or pulse sensor is connected.
- **LED13** (`13`): On-board LED that indicates a heartbeat.
- **Signal** (`int`): Stores incoming raw data from the sensor.
- **Threshold** (`int`): The signal threshold value set to `650`. Signal values above this threshold count as heartbeats.

### Heartbeat Detection
The code detects a heartbeat based on whether the signal value exceeds the `Threshold` of 650, counting it as a pulse when the threshold is crossed. Using this data, we can calculate the heart rate over time by counting beats per minute (BPM) based on the sampling rate.

## Analyzing Rhythm Regularity
To determine if the rhythm is regular or irregular:
1. **Regular Rhythm**: If the time intervals between beats are consistent (low variance), the rhythm is considered regular.
2. **Irregular Rhythm**: High variance between intervals indicates an irregular rhythm, which might signal arrhythmias.

### Calculating Error
Error in this analysis could stem from:
- Sensor noise or incorrect threshold setting.
- Inaccurate signal-to-noise calibration.
- To reduce error, calibrate the threshold and signal filtering to improve rhythm accuracy.

## Running the Code
1. Connect the ECG sensor to the Arduino, with the signal pin connected to `A1` and the on-board LED wired to pin 13.
2. Upload the code to the Arduino.
3. Open the Serial Plotter (set to `115200` baud) to visualize the ECG signal.
4. Observe the LED blink with each detected heartbeat.

