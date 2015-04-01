// ----------------------------------------------------------------------------
// InputCapture.cppp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "InputCapture.h"


InputCapture::InputCapture()
{
}

void InputCapture::setup()
{
  TCCR5A = 0; // clear control register A
  TCCR5B = 0; // set mode 0: normal operation, stop the timer
  callback_enabled_ = false;
  callback_ = NULL;
  capture_time_ = 0;
  duration_ = 0;
  rise_time_prev_ = 0;
  on_duration_us_ = 0;
  period_us_ = 0;
  overflow_timer_ = 0;
  ul_max_ = 0UL - 1UL;
  begin();
}

void InputCapture::addCycleCallback(Callback callback)
{
  callback_ = callback;
  callback_enabled_ = true;
}

void InputCapture::removeCycleCallback()
{
  callback_enabled_ = false;
}

void InputCapture::begin()
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    TCCR5A = 0; // clear control register A
    TCCR5B = 0; // set mode 0: normal operation, stop the timer
    TCCR5B |= _BV(ICNC5); // activate noise canceler
    TCCR5B |= _BV(ICES5); // capture on rising edge
    TCCR5B |= _BV(CS51); // clk/8 for 0.5 uS resolution
    TIMSK5 = _BV(ICIE5) | _BV(TOIE5); // use input capture and overflow interrupts
  }
}

void InputCapture::update()
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    capture_time_ = ICR5;
    // toggle capture edge
    TCCR5B ^= _BV(ICES5);
    // after a change of the edge, the Input Capture Flag (ICFn) must be
    // cleared by software
    TIFR5 |= _BV(ICF5);
    // check for rare race condition between interrupts
    if (!((TIFR5 & _BV(TOV5)) && (capture_time_ < 0x7FFF)))
    {
      capture_time_ += overflow_timer_;
    }
    else
    {
      // just missed an overflow
      Serial << "missed overflow!" << endl;
      capture_time_ += overflow_timer_ + 0x10000UL;
    }
  }

  // check for rollover
  if (capture_time_ > rise_time_prev_)
  {
    duration_ = capture_time_ - rise_time_prev_;
  }
  else
  {
    duration_ = capture_time_ + (ul_max_ - rise_time_prev_) + 1;
    Serial << "rollover!!" << endl;
  }

  if (TCCR5B & _BV(ICES5))
  { // captured falling edge
    // convert clk count to microseconds (/2)
    // lose one bit
    on_duration_us_ = duration_ >> 1;
  }
  else
  { // captured rising edge
    rise_time_prev_ = capture_time_;
    // convert clk count to microseconds (/2)
    // lose one bit
    period_us_ = duration_ >> 1;
    if (callback_enabled_)
    {
      (*callback_)(period_us_, on_duration_us_);
    }
  }
}

void InputCapture::updateOverflowTimer()
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    overflow_timer_ += 0x10000UL;
  }
}

InputCapture input_capture;

ISR(TIMER5_CAPT_vect)
{
  inputCaptureUpdate();
}

ISR(TIMER5_OVF_vect)
{
  inputCaptureUpdateOverflowTimer();
}
