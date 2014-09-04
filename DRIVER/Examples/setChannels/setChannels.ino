#include "Arduino.h"
#include <SPI.h>
#include <Tle7232g.h>
#include <Streaming.h>

#define LOOP_DELAY 1000
#define RELAY_DRIVER_CS  49
#define RELAY_DRIVER_IN  48
#define RELAY_DRIVER_DEVICE_COUNT  2

TLE7232G relayDriver = TLE7232G(RELAY_DRIVER_CS, RELAY_DRIVER_IN);
uint32_t channels;
uint32_t bit;

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
  for (int channel = -1; channel < 16; channel++) {
    if (0 <= channel) {
      bit = 1;
      bit = bit << channel;
      channels = channels | bit;
    } else {
      channels = 0;
    }
    relayDriver.setChannels(channels);
    Serial << "channels = " << _BIN(channels) << endl;
    delay(LOOP_DELAY);
  }
}


