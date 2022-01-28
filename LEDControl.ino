#include "BLE.h"

#define WW_PIN 18
#define CW_PIN 19

int freq = 5000;
int wwChannel = 0;
int cwChannel = 1;
int resolution = 16;

BLE BT;

void setup() {
  Serial.begin(115200);
  Serial.print("HW v");
  Serial.print(HARDWARE_VERSION_MAJOR);
  Serial.print(".");
  Serial.println(HARDWARE_VERSION_MINOR);
  
  Serial.print("SW v");
  Serial.print(SOFTWARE_VERSION_MAJOR);
  Serial.print(".");
  Serial.print(SOFTWARE_VERSION_MINOR);
  Serial.print(".");
  Serial.println(SOFTWARE_VERSION_PATCH);

  Serial.println("Init BLE OTA");
  BT.begin("ESP32 BLE OTA Updates");
  
  Serial.println("Init LEDC driver");
  ledcSetup(wwChannel, freq, resolution);
  ledcSetup(cwChannel, freq, resolution);

  ledcAttachPin(WW_PIN, wwChannel);
  ledcAttachPin(CW_PIN, cwChannel);
  Serial.println("Init LEDC driver completed.");
}

void loop() {
  Serial.println("dimm up.");
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
    ledcWrite(wwChannel, dutyCycle);
    ledcWrite(cwChannel, dutyCycle);
    delay(7);
  }

  Serial.println("dimm down.");
  for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
    ledcWrite(wwChannel, dutyCycle);
    ledcWrite(cwChannel, dutyCycle);
    delay(7);
  }
}
