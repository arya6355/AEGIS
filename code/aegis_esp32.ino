/*
------------------------------------------------
PROJECT AEGIS
Autonomous Emergency Grid & Integrated Shelter
ESP32 Flood Emergency Booth
------------------------------------------------
Features:
- Water Level Monitoring
- LED Alert System
- Buzzer Siren
- Servo Door Control
- Smoke/Gas Detection
- SOS Button
- GPS Alert
- Solar Powered System
------------------------------------------------
*/

#include <ESP32Servo.h>

#define TRIG_PIN 5
#define ECHO_PIN 18

#define GREEN_LED 12
#define YELLOW_LED 13
#define ORANGE_LED 14
#define RED_LED 27

#define BUZZER 26
#define SOS_BUTTON 25
#define GAS_SENSOR 34

#define SERVO_PIN 33
#define FAN_PIN 32

Servo doorServo;

long duration;
float distance;

void setup() {

  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(ORANGE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  pinMode(BUZZER, OUTPUT);
  pinMode(SOS_BUTTON, INPUT_PULLUP);
  pinMode(FAN_PIN, OUTPUT);

  doorServo.attach(SERVO_PIN);
  doorServo.write(0);

  Serial.println("PROJECT AEGIS INITIALIZED");
}

void loop() {

  float waterLevel = getWaterLevel();

  int gasValue = analogRead(GAS_SENSOR);

  Serial.print("Water Distance: ");
  Serial.println(waterLevel);

  // SAFE LEVEL
  if (waterLevel > 100) {

    setAllOff();
    digitalWrite(GREEN_LED, HIGH);

    Serial.println("SAFE");

  }

  // WARNING LEVEL
  else if (waterLevel <= 100 && waterLevel > 70) {

    setAllOff();
    digitalWrite(YELLOW_LED, HIGH);

    Serial.println("WARNING");

  }

  // DANGER LEVEL
  else if (waterLevel <= 70 && waterLevel > 40) {

    setAllOff();
    digitalWrite(ORANGE_LED, HIGH);

    Serial.println("DANGER");

  }

  // CRITICAL LEVEL
  else {

    setAllOff();

    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH);

    doorServo.write(90);

    Serial.println("CRITICAL FLOOD LEVEL");

  }

  // GAS / SMOKE DETECTION
  if (gasValue > 2500) {

    digitalWrite(FAN_PIN, HIGH);

    Serial.println("SMOKE/GAS DETECTED");

  }
  else {

    digitalWrite(FAN_PIN, LOW);

  }

  // SOS BUTTON
  if (digitalRead(SOS_BUTTON) == LOW) {

    Serial.println("SOS ALERT SENT");
    sendGPSAlert();

  }

  delay(1000);
}

float getWaterLevel() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);

  distance = duration * 0.034 / 2;

  return distance;
}

void setAllOff() {

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(ORANGE_LED, LOW);
  digitalWrite(RED_LED, LOW);

  digitalWrite(BUZZER, LOW);
}

void sendGPSAlert() {

  // Placeholder GPS logic

  Serial.println("Fetching GPS Coordinates...");
  Serial.println("Sending Location to Rescue Team...");

}