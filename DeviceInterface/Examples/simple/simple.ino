#include "Streaming.h"
#include "JsonParser.h"
#include "DeviceInterface.h"

void setup() {
  Serial.begin(9600);
  deviceInterface.setMessageStream(Serial);
}

void loop() {
  deviceInterface.processMessage();
}
