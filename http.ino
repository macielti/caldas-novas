#include <HTTPClient.h>
#include <WiFiClientSecure.h>

String fetchDocument(const char* serverName) {    
   
  WiFiClientSecure client;
  client.setInsecure();
  HTTPClient http;

  String fullUrl = String(serverName) + "/api/documents";
  
  http.begin(client, fullUrl);
  
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

String ackDocument(const char* serverName, String documentId) {    
   
  WiFiClientSecure client;
  client.setInsecure();
  HTTPClient http;

  String fullUrl = String(serverName) + "/api/documents/" + documentId + "/ack";
  
  http.begin(client, fullUrl);
  
  int httpResponseCode = http.POST(documentId);
  
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