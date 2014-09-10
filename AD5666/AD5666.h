// ----------------------------------------------------------------------------
// AD5666.h
//
// Provides an SPI based interface to the AD5666 Quad 16-Bit DACs.
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef _AD5666_H_
#define _AD5666_H_

class AD5666
{
public:
  enum channels {A, B, C, D, ALL};
  AD5666();
  AD5666(int cs_pin);
  void spiBegin();
  void init(bool standalone_mode=true, bool ref_off=false, bool spi_reset=false);
  void analogWrite(channels channel, uint16_t value);
  uint16_t getMaxDacValue();

private:
  int cs_pin_;
  bool spi_reset_;
};


#endif
