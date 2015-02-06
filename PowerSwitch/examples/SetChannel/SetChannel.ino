#include "Arduino.h"
#include "SPI.h"
#include "Streaming.h"
#include "PowerSwitch.h"

const int BAUDRATE = 9600;
const int LOOP_DELAY = 1000;
const int CS_PIN = 49;
const int IN_PIN = 48;
const int IC_COUNT = 2;
// Number of power switch IC chips connected in a daisy chain on the
// pcb. There are 8 power switch channels per IC.

// Setting SPI_RESET to true causes the SPI parameters to be reset
// every time before a command is issued over SPI. It could cause
// slight delays and should only be used when you are also
// communicating with other SPI devices with different SPI parameters
const boolean SPI_RESET = false;

// Instantiate PowerSwitch
PowerSwitch power_switch = PowerSwitch(CS_PIN, IN_PIN);
// If the IN_PIN is permanently tied to ground instead of an arduino
// pin you can instantiate it like this instead:
// PowerSwitch power_switch = PowerSwitch(CS_PIN);

int channel_count;

void setup()
{
  // Setup serial communications
  Serial.begin(BAUDRATE);

  power_switch.setup(IC_COUNT,SPI_RESET);
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
