
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C
#define SDA_PIN 21
#define SCL_PIN 22
#define BUTTON_PIN 18
const unsigned long DEBOUNCE_MS = 50;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int lastRawState = HIGH;
int stableState = HIGH;
unsigned long lastChangeTime = 0;
unsigned int pressCount = 0;
void updateDisplay()
{
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("ESP32 Button Counter");
  display.drawLine(0, 10, SCREEN_WIDTH - 1, 10, SSD1306_WHITE);
  display.setCursor(0, 18);
  display.print("Button: ");
  display.println(stableState == LOW ? "PRESSED" : "RELEASED");
  display.setTextSize(2);
  display.setCursor(0, 38);
  display.print("Count:");
  display.print(pressCount);
  display.display();
}
void setup()
{
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Wire.begin(SDA_PIN, SCL_PIN);
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS))
  {
    Serial.println("SSD1306 init failed - check wiring/address");
    while (true)
    {
      delay(1000);
    }
  }
  Serial.println("System ready. Press count = 0");
  updateDisplay();
}
void loop()
{
  int rawState = digitalRead(BUTTON_PIN);
  if (rawState != lastRawState)
  {
    lastChangeTime = millis();
    lastRawState = rawState;
  }
  if ((millis() - lastChangeTime) >= DEBOUNCE_MS && rawState != stableState)
  {
    stableState = rawState;
    if (stableState == LOW)
    {
      pressCount++;
      Serial.print("Accepted press. Count = ");
      Serial.println(pressCount);
    }
    else
    {
      Serial.println("Button released");
    }
    updateDisplay();
  }
}