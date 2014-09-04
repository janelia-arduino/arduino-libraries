// ----------------------------------------------------------------------------
// DRIVER.h
//
// Provides an SPI based interface to the TLE7232 eight channel
// low-side power switch for enhanced relay control
//
// Author: Peter Polidoro
// ----------------------------------------------------------------------------

#ifndef DRIVER_H_
#define DRIVER_H_
#include <util/atomic.h>

class DRIVER {
 public:
  DRIVER();

  // You must specify the clock select pin
  DRIVER(int csPin);

  void init();
  void init(int deviceCount);
  void setChannels(uint32_t channels);
  void setChannelOn(int channel);
  void setChannelOff(int channel);
  uint32_t getChannelsOn();

 private:
  // Private Constants
  const static int DEVICE_COUNT_MAX = 4;

  const static byte CMD_DIAGNOSIS = 0b11<<6;
  const static byte CMD_READ = 0b01<<6;
  const static byte CMD_RESET = 0b10<<6;
  const static byte CMD_WRITE = 0b11<<6;

  const static byte ADDR_IMCR = 0b001; // Input Mapping Configuration Register
  const static byte ADDR_BOCR = 0b010; // Boolean Operator Configuration Register
  const static byte ADDR_OLCR = 0b011; // Over Load Configuration Register
  const static byte ADDR_OTCR = 0b100; // Over Temperature Configuration Register
  const static byte ADDR_SRCR = 0b101; // Slew Rate Configuration Register
  const static byte ADDR_STA = 0b110; // Output Status Monitor
  const static byte ADDR_CTL = 0b111; // Output Control Register

  int csPin;
  int inPin;
  bool initialized;
  uint32_t channels;
  int deviceCount;
};

#endif // DRIVER_H_



