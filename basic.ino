#include <Arduino.h>
#include <ArduinoJson.h>
#include <TimeLib.h>
#include "qrReader.h"
#include "WiFi.h"
#include <HTTPClient.h>

void setup() {
    Serial.begin(115200);
  connectToWiFi();
  login();

  Serial.println();
  
  reader.setup();
  Serial.println("Setup QRCode Reader");
  
  reader.beginOnCore(1);
  Serial.println("Begin on Core 1");
  pinMode(ledPin, OUTPUT);  
    Serial.println(AuthorizationToken);
  xTaskCreate(onQrCodeTask, "onQrCode", 4 * 1024, NULL, 4, NULL);
}

void loop() {
  delay(100);
}
