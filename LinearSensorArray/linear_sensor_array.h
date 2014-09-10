// ----------------------------------------------------------------------------
// LinearSensorArray.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------

#ifndef LINEAR_SENSOR_ARRAY_H
#define LINEAR_SENSOR_ARRAY_H

#include "LinearSensorArrayImage.h"

class LinearSensorArray
{
public:
  LinearSensorArray();
  LinearSensorArray(uint8_t si_pin, uint8_t clk_pin, const uint8_t analog_pins[]);

  void init();
  void getImage(LinearSensorArrayImage* image);

private:
  uint8_t si_pin_;
  uint8_t clk_pin_;

  const uint8_t *analog_pins_;

  volatile uint8_t *si_out_;
  volatile uint8_t *clk_out_;

  uint8_t si_bitmask_;
  uint8_t clk_bitmask_;

};

#endif // LINEAR_SENSOR_ARRAY_H
