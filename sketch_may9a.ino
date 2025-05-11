#include <Servo.h>

// Pin definitions
const int triggerPin = 2;
const int echoPin = 3;
const int redLedAnodePin = 4;
const int redLedCathodePin = 8;
const int blueLedCathodePin = 7;
const int blueLedPin = 5;
const int servoPin = 6;
const int buzzerPin = 12;

// Constants
const float thresholdDistance = 20.0;   // Detection distance in cm
const int closedAngle = 0;
const int openAngle = 90;
const unsigned long closeDelay = 2000;  // Delay before closing
const unsigned long bumpOnTime = 100;   // Buzzer ON duration
const unsigned long bumpOffTime = 800;  // <-- Longer pause between bumps

// Variables
Servo myServo;
bool isOpen = false;
unsigned long lastDetectionTime = 0;
unsigned long lastBumpTime = 0;
bool isBuzzing = false;

void setup() {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLedAnodePin, OUTPUT);
  pinMode(redLedCathodePin, OUTPUT);
  pinMode(blueLedCathodePin, OUTPUT);
  digitalWrite(blueLedCathodePin, LOW);
  digitalWrite(redLedCathodePin, LOW);
  pinMode(blueLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  myServo.attach(servoPin);
  myServo.write(closedAngle);
  digitalWrite(redLedAnodePin, HIGH);
  digitalWrite(blueLedPin, LOW);
  digitalWrite(buzzerPin, LOW);
}

float getDistance() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration / 58.0;
}

void loop() {
  float distance = getDistance();
  unsigned long currentTime = millis();
  bool objectDetected = (distance < thresholdDistance);

  if (objectDetected) {
    if (!isOpen) {
      myServo.write(openAngle);
      isOpen = true;
      digitalWrite(blueLedPin, HIGH);
      digitalWrite(redLedAnodePin, LOW);
    }
    lastDetectionTime = currentTime;
  } else {
    if (isOpen && (currentTime - lastDetectionTime > closeDelay)) {
      myServo.write(closedAngle);
      isOpen = false;
      digitalWrite(redLedAnodePin, HIGH);
      digitalWrite(blueLedPin, LOW);
      digitalWrite(buzzerPin, LOW);
      isBuzzing = false;
    }
  }

  // Buzzer "bump bump" logic
  if (digitalRead(blueLedPin) == HIGH) {
    if (!isBuzzing && currentTime - lastBumpTime >= bumpOffTime) {
      digitalWrite(buzzerPin, HIGH);
      isBuzzing = true;
      lastBumpTime = currentTime;
    } else if (isBuzzing && currentTime - lastBumpTime >= bumpOnTime) {
      digitalWrite(buzzerPin, LOW);
      isBuzzing = false;
      lastBumpTime = currentTime;
    }
  }

  delay(50);
}
