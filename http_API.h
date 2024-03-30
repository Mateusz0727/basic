#include "WiFi.h"
#include <HTTPClient.h>
const char* ssid = "Dom68";
const char* password = "staszekz68";
const char* ssid_p = "iPhone (Mateusz)";
const char* password_p = "12345678";

const String serverUrl = "http://192.168.0.148";
const int ledPin = 4;
 String AuthorizationToken ="2345678";
String login(){
  HTTPClient http;
  
  http.begin(serverUrl+"/login");
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.POST("{\"email\": \"mati68a@gmail.com\", \"password\": \"zaq1@WSX\"}");
  if (httpCode > 0) {
    Serial.printf("HTTP status code: %d\n", httpCode);
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    AuthorizationToken = http.getString();
  
  } else {
    
    Serial.println("HTTP request failed");
  }
  http.end();
  return AuthorizationToken;
}
void connectToWiFi() {
  
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("Connected to WiFi");

}

int sendHttpRequest(const String jsonData) {
    DynamicJsonDocument doc(1024);
  HTTPClient http;
  
  Serial.println("Sending HTTP request...");
  http.begin(serverUrl+"/api/qrCode");
  deserializeJson(doc, AuthorizationToken);
  Serial.println(doc["token"].as<String>());
  http.addHeader("Authorization", "Bearer "+ doc["token"].as<String>());
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.POST(jsonData);
  if (httpCode > 0) {
    Serial.printf("HTTP status code: %d\n", httpCode);
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
  } else {
    
    Serial.println("HTTP request failed");
  }

  http.end();
  
  return httpCode;
}
