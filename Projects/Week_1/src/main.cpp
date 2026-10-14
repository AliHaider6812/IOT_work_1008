// Week3-Lecture1
// Interrupt (External -Button)
// Embedded IoT System Fall-2025

// Name: ALI HAIDER                Reg#: 1008
#include <Arduino.h>

void setup()
{
  pinMode(2, OUTPUT);

  // Initialize serial communication at 115200 baud
  Serial.begin(115200);
  Serial.println("ESP32 Simulation Started!");
}

void loop()
{
  digitalWrite(2, HIGH);
  Serial.println("LED State: ON");
  delay(1000);

  digitalWrite(2, LOW);
  Serial.println("LED State: OFF");
  delay(1000);
}