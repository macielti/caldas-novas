#include <WiFi.h>
#include <Arduino_JSON.h>

#define WIFI_SSID "<Wifi Network Name>"
#define WIFI_PASSWORD "<WiFi Password>"

#define SERVER_NAME "<URL for API with endpoint>"

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println(F("Connecting Wifi..."));
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  
  String raw = fetchDocument(SERVER_NAME);
  JSONVar jsonResponse = JSON.parse(raw);
  JSONVar document = jsonResponse["document"];
  JSONVar commands = document["commands"];

  Serial.print(F("JSON object = "));
  Serial.println(commands);

  useThermalPrinter(commands);

  ESP.restart();
}
