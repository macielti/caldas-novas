#include <Thermal_Printer.h>

void feedPaper (JSONVar command) {
  int scanLines = command["scan-lines"];
  tpFeed(scanLines);
}

void printText (JSONVar command) {
  String text = command["content"];
  char buffer[900];
  text.toCharArray(buffer, sizeof(buffer));
  tpAlign(ALIGN_LEFT);
  tpPrint(buffer);
}

void useThermalPrinter(JSONVar commands) {

  int length = commands.length();
  
  if (tpScan()) {
    Serial.println(F("Found a printer!, connecting..."));
    if (tpConnect()){
      Serial.println(F("Printer Connected!"));
      for (int i = 0; i < length; i++) {
        JSONVar currentCommand = commands[i];
        String commandType = currentCommand["type"];
        if (commandType == "feed-paper") {
          feedPaper(currentCommand);
        } else if (commandType == "print-text") {
          printText(currentCommand);
        } else {
          Serial.println(F("[ERROR]: Command not implemented."));
        }
      }
      tpDisconnect();
      delay(1000);
    } else {
      Serial.println(F("Printer not found. Restarting..."));
      ESP.restart();
    }
  }
}