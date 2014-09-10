// ----------------------------------------------------------------------------
// power_switch.cpp
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "SPI.h"
#include "power_switch.h"

//---------- constructor ----------------------------------------------------

PowerSwitch::PowerSwitch()
{
  initialized_ = false;
}

PowerSwitch::PowerSwitch(int cs_pin) :
  cs_pin_(cs_pin)
{
  initialized_ = false;

  pinMode(cs_pin_, OUTPUT);
  digitalWrite(cs_pin_, HIGH);
}

PowerSwitch::PowerSwitch(int cs_pin, int in_pin) :
  cs_pin_(cs_pin),
  in_pin_(in_pin)
{
  initialized_ = false;

  pinMode(cs_pin, OUTPUT);
  digitalWrite(cs_pin, HIGH);

  pinMode(in_pin,OUTPUT);
  digitalWrite(in_pin, LOW);
}

//---------- public ----------------------------------------------------


void PowerSwitch::spiBegin()
{
  SPI.setDataMode(SPI_MODE1);
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  SPI.setBitOrder(MSBFIRST);
  SPI.begin();
}

void PowerSwitch::init(int device_count, bool spi_reset)
{
  spi_reset_ = spi_reset;
  if ((0 < device_count) && (device_count <= DEVICE_COUNT_MAX))
  {
    device_count_ = device_count;
  }
  else
  {
    device_count_ = DEVICE_COUNT_MIN;
  }
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    channels_ = 0;
  }
  spiBegin();
  setChannels(channels_);
  initialized_ = true;
}

void PowerSwitch::setChannels(uint32_t channels)
{
  if (spi_reset_)
  {
    spiBegin();
  }
  digitalWrite(cs_pin_, LOW);
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    channels_ = channels;
    for (int device = (device_count_ - 1); 0 <= device; device--) {
      SPI.transfer(CMD_WRITE + ADDR_CTL);
      SPI.transfer(channels_>>(device*8));
    }
  }
  digitalWrite(cs_pin_, HIGH);
  digitalRead(cs_pin_);
}

void PowerSwitch::setChannelOn(int channel)
{
  if ((0 <= channel) && (channel < CHANNEL_COUNT_MAX))
  {
    uint32_t bit = 1;
    bit = bit << channel;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
      channels_ = channels_ | bit;
    }
    setChannels(channels_);
  }
}

void PowerSwitch::setChannelOff(int channel)
{
  if ((0 <= channel) && (channel < CHANNEL_COUNT_MAX))
  {
    uint32_t bit = 1;
    bit = bit << channel;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
      channels_ = channels_ & ~bit;
    }
    setChannels(channels_);
  }
}

uint32_t PowerSwitch::getChannelsOn()
{
  return channels_;
}

int PowerSwitch::getChannelCount()
{
  return device_count_*CHANNEL_COUNT_PER_DEVICE;
}

//------------------ private -----------------------------------------------
