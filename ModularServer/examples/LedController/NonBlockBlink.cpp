// ----------------------------------------------------------------------------
// NonBlockBlink.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "NonBlockBlink.h"

NonBlockBlink::NonBlockBlink(int led_pin) :
  led_pin_(led_pin)
{
  duration_on_ = 300;
  duration_off_ = 500;
  count_ = 10;
}

void NonBlockBlink::start()
{
  if (count_ > 0)
  {
    previous_time_ = millis();
    led_state_ = HIGH;
    digitalWrite(led_pin_, led_state_);
    interval_ = duration_on_;
    counter_ = 0;
    enabled_ = true;
  }
}

void NonBlockBlink::stop()
{
  enabled_ = false;
}

void NonBlockBlink::update()
{
  if (enabled_)
  {
    current_time_ = millis();

    if((current_time_ - previous_time_) > interval_)
    {
      previous_time_ = current_time_;
      if (led_state_ == LOW)
      {
        led_state_ = HIGH;
        interval_ = duration_on_;
      }
      else
      {
        led_state_ = LOW;
        interval_ = duration_off_;
        counter_++;
        if (counter_ >= count_)
        {
          stop();
        }
      }

      digitalWrite(led_pin_, led_state_);
    }
  }
}

void NonBlockBlink::setDurationOn(double value)
{
  duration_on_ = (int)(value*1000);
}

void NonBlockBlink::setDurationOff(double value)
{
  duration_off_ = (int)(value*1000);
}

void NonBlockBlink::setCount(long value)
{
  count_ = (long)value;
}

NonBlockBlink non_block_blink(constants::led_pin);
