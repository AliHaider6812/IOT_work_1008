#include <Arduino.h>

#define LED_PIN 2

hw_timer_t *timer = NULL;
volatile bool ledState = false;

void IRAM_ATTR onTimer()
{
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
}

void setup()
{
  pinMode(LED_PIN, OUTPUT);

  // Timer 0, prescaler 80 -> 80 MHz / 80 = 1 MHz (1 tick = 1 Âµs)
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);

  // 1,000,000 ticks = 1 second, auto-reload
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
}

void loop()
{
}