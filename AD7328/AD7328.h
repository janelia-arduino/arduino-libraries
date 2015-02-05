// ----------------------------------------------------------------------------
// AD7328.h
//
// Provides an SPI based interface to the AD7328 eight channel
// 12 bit plus sign ADC
//
// Authors:
// Steve Sawtelle sawtelles@janelia.hhmi.org
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef AD7328_H
#define AD7328_H
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <SPI.h>
#include <util/atomic.h>


class AD7328
{
public:
  AD7328(uint8_t cs_pin);
  void setRange(uint8_t channel, uint8_t range);
  uint8_t getRange(uint8_t channel);
  uint16_t read(uint8_t channel);

// range constants
#define BIP10  0x00 // +/-10V
#define BIP5   0x01 // +/-5V
#define BIP2V5 0x02 // +/-2.5
#define UNI10  0x03 // +10V

private:
  const static uint16_t RANGE_REG_L = 0x2000;  // chs 0-3
  const static uint16_t RANGE_REG_H = 0x4000;  // chs 4-7
  const static uint16_t READ_REG = 0x0000;
  const static uint16_t  WRITE_REG = 0x8000;
  const static uint16_t CH0_MASK = 0b1110011111111111;
  const static uint16_t CH1_MASK = 0b1111100111111111;
  const static uint16_t CH2_MASK = 0b1111111001111111;
  const static uint16_t CH3_MASK = 0b1111111110011111;
  const static uint16_t CH4_MASK = 0b1110011111111111;
  const static uint16_t CH5_MASK  = 0b1111100111111111;
  const static uint16_t CH6_MASK = 0b1111111001111111;
  const static uint16_t CH7_MASK = 0b1111111110011111;

  int cs_pin_;
  uint16_t range_l_;
  uint16_t range_h_;
};

#endif
