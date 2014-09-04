#include "Arduino.h"
#include <SPI.h>
#include <Tle7232g.h>
#include <Streaming.h>

#define LOOP_DELAY 1000
#define RELAY_DRIVER_CS  49
#define RELAY_DRIVER_IN  48
#define RELAY_DRIVER_DEVICE_COUNT  2

TLE7232G relayDriver = TLE7232G(RELAY_DRIVER_CS, RELAY_DRIVER_IN);

void setup()
{
  // Initialize SPI:
  SPI.setDataMode(SPI_MODE1);
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  SPI.setBitOrder(MSBFIRST);
  SPI.begin();

  // Setup serial communications
  Serial.begin(115200);

  relayDriver.init(RELAY_DRIVER_DEVICE_COUNT);
}

void loop()
{
  for (int channel = 0; channel < 32; channel++) {
    if (channel < 16) {
      relayDriver.setChannelOn(channel);
      Serial << "set channel " << channel << " on" << endl;
    } else {
      relayDriver.setChannelOff(channel-16);
      Serial << "set channel " << (channel-16) << " off" << endl;
    }
    delay(LOOP_DELAY);
  }
}


