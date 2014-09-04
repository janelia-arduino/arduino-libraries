// ----------------------------------------------------------------------------
// DRIVER.h
//
// Provides an SPI based interface to the TLE7232 eight channel
// low-side power switch for enhanced relay control
//
// Author: Peter Polidoro
// ----------------------------------------------------------------------------
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <SPI.h>
#include "DRIVER.h"
//#include <Streaming.h>

//---------- constructor ----------------------------------------------------

DRIVER::DRIVER() {
  initialized = false;
}

DRIVER::DRIVER(int csPin) {
  initialized = false;

  pinMode(csPin, OUTPUT);
  digitalWrite(csPin, HIGH);
  this->csPin = csPin;

}

//---------- public ----------------------------------------------------


// ----------------------------------------------------------------------------
// DRIVER::init
//
// ----------------------------------------------------------------------------
void DRIVER::init() {
  init(DEVICE_COUNT_MAX);
}

void DRIVER::init(int deviceCount) {
  if ((0 < deviceCount) && (deviceCount <= DEVICE_COUNT_MAX)) {
    this->deviceCount = deviceCount;
  } else {
    this->deviceCount = DEVICE_COUNT_MAX;
  }
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    channels = 0;
  }
  setChannels(channels);
  initialized = true;
}

void DRIVER::setChannels(uint32_t channels) {

  SPI.setDataMode(SPI_MODE1);  // set proper mode, clk idle low, falling edge = 0 => mode = 0
  digitalWrite(csPin, LOW);
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    this->channels = channels;
    for (int device = (deviceCount - 1); 0 <= device; device--) {
      SPI.transfer(CMD_WRITE + ADDR_CTL);
      SPI.transfer(channels>>(device*8));
    }
  }
  digitalWrite(csPin, HIGH);
  digitalRead(csPin);
}

void DRIVER::setChannelOn(int channel) {
  if ((0 <= channel) && (channel < 32)) {
    uint32_t bit = 1;
    bit = bit << channel;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
      channels = channels | bit;
    }
    setChannels(channels);
  }
}

void DRIVER::setChannelOff(int channel) {
  if ((0 <= channel) && (channel < 32)) {
    uint32_t bit = 1;
    bit = bit << channel;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
      channels = channels & ~bit;
    }
    setChannels(channels);
  }
}

uint32_t DRIVER::getChannelsOn() {
  return channels;
}

//------------------ private -----------------------------------------------

