#include "DallasTemperature.h"
#include "OneWire.h"

// Define to which pin of the Arduino the 1-Wire bus is connected:
#define ONE_WIRE_BUS 5

// Create a new instance of the OneWire class to communicate with any OneWire device:
OneWire oneWire(ONE_WIRE_BUS);

// Pass the OneWire reference to DallasTemperature library:
DallasTemperature sensors(&oneWire);


// Pin definitions
const int pumpRelayPin = 2; // Relay control for both pumps
const int buzzerPin = 7;

const int tempSensorPin = A5;
const int flowMeterPin = 5; // Flowmeter pulse input
const int ldrPin = A0;
int  Red=0, Blue=0, Green=0;  //RGB values 


// ADXL345 I2C address
#define ADXL345_ADDR 0x53

// Threshold for sudden movement (adjust based on sensitivity)
#define MOVEMENT_THRESHOLD 2.0

#define s0 8       //Module pins wiring
#define s1 9
#define s2 10
#define s3 11
#define out 12

int data=0;        //This is where we're going to stock our values

// Thresholds and constants
const int tempThreshold = 30; // Maximum temperature in °C
const int ldrThreshold = 300; // LDR threshold for air detection
const float flowRateThreshold = 7.3; // Minimum flow rate (L/min)

// Variables
volatile unsigned int flowPulseCount = 0;
float flowRate = 0.0;
unsigned long previousMillis = 0;
const unsigned long interval = 1000; // 1-second interval

// Function prototypes
void flowMeterISR();
void checkSensors();
void triggerAlarm(const char* message);

void setup() {
  // Serial communication for debugging
  Serial.begin(9600);
  Wire.begin();

  // Initialize ADXL345
  Wire.beginTransmission(ADXL345_ADDR);
  Wire.write(0x2D); // Power control register
  Wire.write(0x08); // Enable measurement mode

  pinMode(s0,OUTPUT);    //pin modes
   pinMode(s1,OUTPUT);
   pinMode(s2,OUTPUT);
   pinMode(s3,OUTPUT);
   pinMode(out,INPUT);

   digitalWrite(s0,HIGH);  
   digitalWrite(s1,HIGH); 
   
  // Set up pins
  pinMode(pumpRelayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  pinMode(flowMeterPin, INPUT_PULLUP);
  pinMode(ldrPin, INPUT);

  // Attach interrupt for flow meter
  attachInterrupt(digitalPinToInterrupt(flowMeterPin), flowMeterISR, RISING);

  // Initialize relay and buzzer off
  digitalWrite(pumpRelayPin, LOW);
  digitalWrite(buzzerPin, LOW);
  Wire.endTransmission();

  Serial.println("Hemodialysis Simulation Started");
}

void loop() {
  Serial.print("somaia test ");

  float ax, ay, az;

  sensors.requestTemperatures();
    checkTemperature();


  // Read acceleration data
  ax = readAxis(0x32); // X-axis
  ay = readAxis(0x34); // Y-axis
  az = readAxis(0x36); // Z-axis

  // Calculate total acceleration magnitude
  float totalAccel = sqrt(ax * ax + ay * ay + az * az);
  
  Serial.print("Total Accel: ");
  Serial.println(az);
  Serial.println(ax);
  Serial.println(ay);
  // Detect sudden movement
  if (totalAccel > MOVEMENT_THRESHOLD) {
    Serial.println("Sudden movement detected!");
  }

  // Calculate flow rate every second
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Calculate flow rate
    noInterrupts();
    flowRate = random(700, 801) / 100.0; 
    interrupts();

    // Debug flow rate
    Serial.print("Flow Rate: ");
    Serial.print(flowRate);
    Serial.println(" L/min");

    GetColors();                                     //Execute the GetColors function  to get the value of each RGB color
    Serial.println();
  }

  // Check sensors
  checkSensors();
  delay(2000);
}

void flowMeterISR() {
  flowPulseCount++;
}

// Function to check temperature
void checkTemperature() {
  // Fetch the temperature in Celsius:
  float tempC = sensors.getTempCByIndex(0);  // Index 0 for the first device

  // Print the temperature to the Serial Monitor:
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print(" Â°C | ");
  
  // Simulate heating control:
  if (tempC > 30) {
    digitalWrite(LED_temp, LOW);  // Heating off if temperature > 30°C
  } else {
    digitalWrite(LED_temp, HIGH); // Heating on if temperature <= 30°C
  }
}
void checkSensors() {

  // Fetch the temperature in Celsius:
  float tempC = sensors.getTempCByIndex(0);  // Index 0 for the first device

  // Print the temperature to the Serial Monitor:
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print(" Â°C | ");  

  // Read LDR value
  int ldrValue = analogRead(ldrPin);
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // Simulate color sensor reading
  int bloodLeakValue = analogRead(A2); 
  Serial.print("Blood Leak Value: ");
  Serial.println(bloodLeakValue);

  // Check conditions and trigger alarms if needed
  if (tempC > 30){
    triggerAlarm("High Temperature Detected!");
  }


  if (flowRate < flowRateThreshold) {
    triggerAlarm("Low Flow Rate Detected!");
    digitalWrite(pumpRelayPin, HIGH);
  }

  if (ldrValue > ldrThreshold) {
    triggerAlarm("Air in Line Detected!");
  }
  
  if (Red <=100 && Green >50 && Blue >50){
      triggerAlarm("Blood Leak Detected!");
      Serial.print(Red);     
      Serial.print(", Green = ");
      Serial.print(Green);   
      Serial.print(", Blue = ");
      Serial.println(Blue);     
  }
    else{
      Serial.print("Red");     
      Serial.print(Red);     
      Serial.print(", Green = ");
      Serial.print(Green);   
      Serial.print(", Blue = ");
      Serial.println(Blue); 
      }

    delay(2000);                  // Alarm duration
}

void triggerAlarm(const char* message) {
  Serial.println(message);
   digitalWrite(buzzerPin, HIGH);  // Turn on buzzer
   digitalWrite(pumpRelayPin, LOW); // Stop the flow

  delay(2000);                  // Alarm duration
  digitalWrite(buzzerPin, LOW);  // Turn off buzzer
  digitalWrite(pumpRelayPin, HIGH);

}

void GetColors()  
{    
  digitalWrite(s2,  LOW);                                           
  digitalWrite(s3, LOW);                                           
  Red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);       
  delay(20);  
  digitalWrite(s3, HIGH);                                         
  Blue = pulseIn(out, digitalRead(out) == HIGH ? LOW  : HIGH);
  delay(20);  
  digitalWrite(s2, HIGH);  
  Green = pulseIn(out,  digitalRead(out) == HIGH ? LOW : HIGH);
  delay(20);  
}


float readAxis(uint8_t reg) {
  Wire.beginTransmission(ADXL345_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);

  Wire.requestFrom(ADXL345_ADDR, 2);
  int16_t rawData = Wire.read() | (Wire.read() << 8);

  // Convert to g (1 g = 9.8 m/s^2)
  return rawData * 0.004; // ADXL345 sensitivity = 4 mg/LSB
}