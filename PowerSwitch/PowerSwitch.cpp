// ----------------------------------------------------------------------------
// PowerSwitch.cpp
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------

#include "PowerSwitch.h"


PowerSwitch::PowerSwitch()
{
  initialized_ = false;
}

PowerSwitch::PowerSwitch(const int cs_pin) :
  cs_pin_(cs_pin)
{
  initialized_ = false;

  pinMode(cs_pin_, OUTPUT);
  digitalWrite(cs_pin_, HIGH);
}

PowerSwitch::PowerSwitch(const int cs_pin, const int in_pin) :
  cs_pin_(cs_pin),
  in_pin_(in_pin)
{
  initialized_ = false;

  pinMode(cs_pin, OUTPUT);
  digitalWrite(cs_pin, HIGH);

  pinMode(in_pin,OUTPUT);
  digitalWrite(in_pin, LOW);
}

void PowerSwitch::setup(const int ic_count, const boolean spi_reset)
{
  spi_reset_ = spi_reset;
  if ((0 < ic_count) && (ic_count <= IC_COUNT_MAX))
  {
    ic_count_ = ic_count;
  }
  else
  {
    ic_count_ = IC_COUNT_MIN;
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
    for (int ic = (ic_count_ - 1); 0 <= ic; ic--) {
      SPI.transfer(CMD_WRITE + ADDR_CTL);
      SPI.transfer(channels_>>(ic*8));
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
      channels_ |= bit;
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
      channels_ &= ~bit;
    }
    setChannels(channels_);
  }
}

void PowerSwitch::toggleChannel(int channel)
{
  if ((0 <= channel) && (channel < CHANNEL_COUNT_MAX))
  {
    uint32_t bit = 1;
    bit = bit << channel;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
      channels_ ^= bit;
    }
    setChannels(channels_);
  }
}

void PowerSwitch::toggleChannels(uint32_t channels)
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    channels_ ^= channels;
  }
  setChannels(channels_);
}

void PowerSwitch::toggleAllChannels()
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    channels_ = ~channels_;
  }
  setChannels(channels_);
}

void PowerSwitch::setAllChannelsOn()
{
  uint32_t bit = 1;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    channels_ = (bit << getChannelCount()) - 1;
  }
  setChannels(channels_);
}

void PowerSwitch::setAllChannelsOff()
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    channels_ = 0;
  }
  setChannels(channels_);
}

void PowerSwitch::setChannelOnAllOthersOff(int channel)
{
  if ((0 <= channel) && (channel < CHANNEL_COUNT_MAX))
  {
    uint32_t bit = 1;
    bit = bit << channel;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
      channels_ = bit;
    }
    setChannels(channels_);
  }
}

void PowerSwitch::setChannelOffAllOthersOn(int channel)
{
  if ((0 <= channel) && (channel < CHANNEL_COUNT_MAX))
  {
    uint32_t bit = 1;
    bit = bit << channel;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
      channels_ = ~bit;
    }
    setChannels(channels_);
  }
}

void PowerSwitch::setChannelsOnAllOthersOff(uint32_t channels)
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    channels_ = channels;
  }
  setChannels(channels_);
}

void PowerSwitch::setChannelsOffAllOthersOn(uint32_t channels)
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    channels_ = ~channels;
  }
  setChannels(channels_);
}

uint32_t PowerSwitch::getChannelsOn()
{
  return channels_;
}

int PowerSwitch::getChannelCount()
{
  return ic_count_*CHANNEL_COUNT_PER_IC;
}

void PowerSwitch::spiBegin()
{
  SPI.setDataMode(SPI_MODE1);
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  SPI.setBitOrder(MSBFIRST);
  SPI.begin();
}

