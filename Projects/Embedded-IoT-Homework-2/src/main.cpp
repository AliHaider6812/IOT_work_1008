
// #include <Arduino.h>

// constexpr uint8_t LED1_PIN = 18;
// constexpr uint8_t LED2_PIN = 19;

// constexpr uint8_t PWM_CHANNEL1 = 0;
// constexpr uint8_t PWM_CHANNEL2 = 2;

// constexpr uint32_t PWM_FREQUENCY1 = 1000;
// constexpr uint32_t PWM_FREQUENCY2 = 5000;

// constexpr uint8_t PWM_RESOLUTION = 8;
// constexpr uint16_t PWM_MAX_DUTY = (1 << PWM_RESOLUTION) - 1;

// void setup()
// {
//     Serial.begin(115200);

//     double actualFreq1 = ledcSetup(
//         PWM_CHANNEL1, PWM_FREQUENCY1, PWM_RESOLUTION);

//     double actualFreq2 = ledcSetup(
//         PWM_CHANNEL2, PWM_FREQUENCY2, PWM_RESOLUTION);

//     if (actualFreq1 == 0 || actualFreq2 == 0)
//     {
//         Serial.println("ERROR: PWM setup failed.");
//         while (true)
//         {
//             delay(1000);
//         }
//     }

//     ledcAttachPin(LED1_PIN, PWM_CHANNEL1);
//     ledcAttachPin(LED2_PIN, PWM_CHANNEL2);

//     ledcWrite(PWM_CHANNEL1, 0);
//     ledcWrite(PWM_CHANNEL2, 0);

//     Serial.println("Dual LED PWM Fade Started");

//     Serial.print("LED 1 Frequency: ");
//     Serial.print(actualFreq1);
//     Serial.println(" Hz");

//     Serial.print("LED 2 Frequency: ");
//     Serial.print(actualFreq2);
//     Serial.println(" Hz");
// }

// void loop()
// {
//     // Fade in both LEDs
//     for (int duty = 0; duty <= PWM_MAX_DUTY; duty++)
//     {
//         ledcWrite(PWM_CHANNEL1, duty);
//         ledcWrite(PWM_CHANNEL2, duty);

//         delay(10);
//     }

//     // Fade out both LEDs
//     for (int duty = PWM_MAX_DUTY; duty >= 0; duty--)
//     {
//         ledcWrite(PWM_CHANNEL1, duty);
//         ledcWrite(PWM_CHANNEL2, duty);

//         delay(10);
//     }
// }

//----------------Task 2: OLED Monitoring--------------------

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(
    SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int LED1_PIN = 18;
const int LED2_PIN = 19;

const int CHANNEL1 = 0;
const int CHANNEL2 = 2;

const int FREQ1 = 1000;
const int FREQ2 = 5000;
const int RESOLUTION = 8;
const int MAX_DUTY = 255;

int duty1 = 0;
int duty2 = 0;

void showOLED()
{
    int percent1 = duty1 * 100 / MAX_DUTY;
    int percent2 = duty2 * 100 / MAX_DUTY;

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);

    display.setCursor(0, 0);
    display.println("PWM MONITOR");

    display.setCursor(0, 18);
    display.print("LED1: ");
    display.print(percent1);
    display.print("% F:");
    display.print(FREQ1);
    display.println("Hz");

    display.setCursor(0, 38);
    display.print("LED2: ");
    display.print(percent2);
    display.print("% F:");
    display.print(FREQ2);
    display.println("Hz");

    display.display();
}

void setup()
{
    Serial.begin(115200);

    Wire.begin(21, 22);

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS))
    {
        Serial.println("OLED initialization failed!");
        while (true)
        {
            delay(1000);
        }
    }

    ledcSetup(CHANNEL1, FREQ1, RESOLUTION);
    ledcSetup(CHANNEL2, FREQ2, RESOLUTION);

    ledcAttachPin(LED1_PIN, CHANNEL1);
    ledcAttachPin(LED2_PIN, CHANNEL2);

    ledcWrite(CHANNEL1, 0);
    ledcWrite(CHANNEL2, 0);

    Serial.println("Task 2: Dual LED PWM with OLED");

    showOLED();
}

void loop()
{
    for (duty1 = 0; duty1 <= MAX_DUTY; duty1++)
    {
        duty2 = duty1;

        ledcWrite(CHANNEL1, duty1);
        ledcWrite(CHANNEL2, duty2);

        showOLED();
        delay(10);
    }

    for (duty1 = MAX_DUTY; duty1 >= 0; duty1--)
    {
        duty2 = duty1;

        ledcWrite(CHANNEL1, duty1);
        ledcWrite(CHANNEL2, duty2);

        showOLED();
        delay(10);
    }
}
