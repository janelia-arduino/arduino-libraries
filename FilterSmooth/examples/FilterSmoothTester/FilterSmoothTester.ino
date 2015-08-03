#include "Arduino.h"
#include "Streaming.h"
#include "FilterSmooth.h"


const int BAUDRATE = 9600;
const int SAMPLE_COUNT = 5;
const int SENSOR_PIN = 0;

FilterSmooth<SAMPLE_COUNT> filter;


void setup()
{
  Serial.begin(BAUDRATE);
  delay(2000);
}


void loop()
{
  int raw_value = analogRead(SENSOR_PIN);
  Serial << "Raw value: " << raw_value << endl;
  filter.addSample(raw_value);
  int filtered_value = filter.getFilteredValue();
  Serial << "Filtered value: " << filtered_value << endl;
  Serial << endl;
  delay(200);
}
