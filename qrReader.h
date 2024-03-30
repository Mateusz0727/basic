#include "http_API.h"
#include <ESP32QRCodeReader.h>

ESP32QRCodeReader reader(CAMERA_MODEL_AI_THINKER);
struct UserQrCode {
  String Id;
  String Token;
  time_t ExpiredTime;
};

void onQrCodeTask(void *pvParameters) {
  struct QRCodeData qrCodeData;
  DynamicJsonDocument doc(1024);
  
  while (true) {
    if (reader.receiveQrCode(&qrCodeData, 100)) {
      Serial.println("Found QRCode");
      
      if (qrCodeData.valid) {
        Serial.print("Payload: ");
        Serial.println((const char *)qrCodeData.payload);
        
        String payloadStr = String((const char *)qrCodeData.payload);
        
        // Deserializacja danych JSON
        deserializeJson(doc, payloadStr);
        
        // Sprawdzenie, czy dane zostały poprawnie zdeserializowane
        if (doc.containsKey("ExpiredTime") && doc.containsKey("Id") && doc.containsKey("Token")) {
          String id = doc["Id"].as<String>();
          String token = doc["Token"].as<String>();
          time_t expiredTime = doc["ExpiredTime"].as<time_t>();
          
          // Utworzenie obiektu UserQrCode
          UserQrCode userQrCode = {id, token, expiredTime};
          Serial.println(payloadStr);
          // Wyświetlenie danych
          Serial.print("UserQrCode: ");
          Serial.print("Id: ");
          Serial.println(userQrCode.Id);
          Serial.print("Token: ");
          Serial.println(userQrCode.Token);
          Serial.print("ExpiredTime: ");
          Serial.println(userQrCode.ExpiredTime);
        Serial.println(  sendHttpRequest(payloadStr));
        } else {
          Serial.println("Błąd podczas deserializacji danych QRCode.");
        }
      } else {
        Serial.print("Invalid: ");
        Serial.println((const char *)qrCodeData.payload);
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}
