#include "Arduino.h"
#include "SPI.h"
#include "Streaming.h"
#include "power_switch.h"

#define LOOP_DELAY 1000
#define CS_PIN  49
#define IN_PIN  48
#define DEVICE_COUNT  2

// If the IN_PIN is permanently tied to ground instead of an arduino
// pin you can instantiate it like this instead:
// PowerSwitch power_switch = PowerSwitch(CS_PIN);
PowerSwitch power_switch = PowerSwitch(CS_PIN, IN_PIN);

// Setting spi_reset to true causes the SPI parameters to be reset
// every time before a command is issued over SPI. It could cause
// slight delays and should only be used when you are also
// communicating with other SPI devices with different SPI parameters
bool spi_reset = false;
int channel_count;

void setup()
{
  // Setup serial communications
  Serial.begin(115200);

  power_switch.init(DEVICE_COUNT,spi_reset);
  channel_count = power_switch.getChannelCount();
}

void loop()
{
  for (int channel = 0; channel < channel_count; channel++)
  {
    if (channel%2 == 0)
    {
      power_switch.setChannelOn(channel);
      Serial << "set channel " << channel << " on" << endl;
    }
    else
    {
      if (channel > 0)
      {
        power_switch.setChannelOff(channel-1);
        Serial << "set channel " << (channel-1) << " off" << endl;
      }
      power_switch.setChannelOn(channel);
      Serial << "set channel " << (channel) << " on" << endl;
    }
    delay(LOOP_DELAY);
  }
  // Set all channels to off
  power_switch.setChannels(0);
}
