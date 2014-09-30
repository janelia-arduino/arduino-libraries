// ----------------------------------------------------------------------------
// power_switch.h
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------

#ifndef POWER_SWITCH_H
#define POWER_SWITCH_H
#include <util/atomic.h>

class PowerSwitch
{
public:
  PowerSwitch();
  PowerSwitch(int cs_pin);
  PowerSwitch(int cs_pin, int in_pin);

  void spiBegin();
  void init(int device_count=1, bool spi_reset=false);
  void setChannels(uint32_t channels);
  void setChannelOn(int channel);
  void setChannelOff(int channel);
  uint32_t getChannelsOn();
  int getChannelCount();

private:
  // Private Constants
  const static int DEVICE_COUNT_MIN = 1;
  const static int DEVICE_COUNT_MAX = 4;

  const static int CHANNEL_COUNT_PER_DEVICE = 8;
  const static int CHANNEL_COUNT_MAX = 32;

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

  int cs_pin_;
  int in_pin_;
  bool initialized_;
  uint32_t channels_;
  int device_count_;
  bool spi_reset_;
};

#endif // POWER_SWITCH_H
