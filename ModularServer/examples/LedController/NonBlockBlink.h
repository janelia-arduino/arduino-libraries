// ----------------------------------------------------------------------------
// NonBlockBlink.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef _NON_BLOCK_BLINK_H_
#define _NON_BLOCK_BLINK_H_
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Constants.h"

class NonBlockBlink
{
public:
  NonBlockBlink(int led_pin);
  void start();
  void stop();
  void update();
  void setDurationOn(double value);
  void setDurationOff(double value);
  void setCount(long value);
private:
  int duration_on_;
  int duration_off_;
  int count_;
  int led_pin_;
  int led_state_;
  bool enabled_;
  unsigned int interval_;
  int counter_;
  unsigned long current_time_;
  unsigned long previous_time_;
};

extern NonBlockBlink non_block_blink;
#endif
