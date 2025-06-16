#include <HTTPClient.h>
#include <WiFiClientSecure.h>

String fetchDocument(const char* serverName) {    
   
  WiFiClientSecure client;
  client.setInsecure();
  HTTPClient http;
  
  http.begin(client, serverName);
  
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print(F("HTTP Response code: "));
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print(F("Error code: "));
    Serial.println(httpResponseCode);
  }
  
  http.end();

  return payload;
}