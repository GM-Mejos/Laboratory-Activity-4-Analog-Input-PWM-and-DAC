#include <Arduino.h>

// Example 4: PWM LED Control using Potentiometer
const uint8_t POT_PIN     = 34;
const uint8_t PWM_LED_PIN = 19;

const int PWM_FREQ       = 5000; // 5 kHz
const int PWM_RESOLUTION = 8;    // 8-bit (0 - 255)
const int PWM_CHANNEL    = 0;

void setup() {
  Serial.begin(115200);

  analogReadResolution(12);
  analogSetPinAttenuation(POT_PIN, ADC_11db);

  pinMode(PWM_LED_PIN, OUTPUT);
  digitalWrite(PWM_LED_PIN, LOW);

  // Compatible with both ESP32 Core v2.x and v3.x+
  #if defined(ESP_ARDUINO_VERSION_MAJOR) && (ESP_ARDUINO_VERSION_MAJOR >= 3)
    ledcAttach(PWM_LED_PIN, PWM_FREQ, PWM_RESOLUTION);
    ledcWrite(PWM_LED_PIN, 0);
  #else
    ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(PWM_LED_PIN, PWM_CHANNEL);
    ledcWrite(PWM_CHANNEL, 0);
  #endif

  Serial.println("PWM initialized successfully!");
}

void loop() {
  const int raw = analogRead(POT_PIN);
  const int duty = constrain(map(raw, 0, 4095, 0, 255), 0, 255);

  #if defined(ESP_ARDUINO_VERSION_MAJOR) && (ESP_ARDUINO_VERSION_MAJOR >= 3)
    ledcWrite(PWM_LED_PIN, duty);
  #else
    ledcWrite(PWM_CHANNEL, duty);
  #endif

  Serial.print("Raw: ");
  Serial.print(raw);
  Serial.print("\tPWM Duty: ");
  Serial.println(duty);

  delay(100);
}