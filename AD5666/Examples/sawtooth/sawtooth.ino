#include "Arduino.h"
#include <SPI.h>
#include <Streaming.h>
#include "AD5666.h"

#define LOOP_DELAY 10
#define DAC_CS 53

const uint16_t value_min = 0;
uint16_t value_max;
const uint16_t value_inc = 6554;

AD5666 dac = AD5666(DAC_CS);
uint16_t value = value_min;

void setup()
{
  // Setup serial communications
  Serial.begin(115200);

  // Initialize DAC
  dac.init();
  value_max = dac.getMaxDacValue();
}


void loop()
{
  Serial << "value = " << _DEC(value) << endl;
  if (value <= value_max)
  {
    value += value_inc;
  }
  else
  {
    value = value_min;
  }
  dac.analogWrite(AD5666::ALL,value);
  delay(LOOP_DELAY);
}
