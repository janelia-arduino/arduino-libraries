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
  cycle_task_.enabled = false;
  capture_time_ = 0;
  duration_ = 0;
  rise_time_prev_ = 0;
  on_duration_us_ = 0;
  period_us_ = 0;
  overflow_timer_ = 0;
  ul_max_ = 0UL - 1UL;

  startTimer();
}

void InputCapture::addCycleTask(void (*userFunc)(unsigned long period_us, unsigned long on_duration_us))
{
  cycle_task_.func = userFunc;
  cycle_task_.enabled = true;
}

void InputCapture::removeCycleTask()
{
  cycle_task_.enabled = false;
}

void InputCapture::startTimer()
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
  noInterrupts();
  capture_time_ = ICR5;
  TCCR5B ^= _BV(ICES5); // toggle capture edge
  capture_time_ += overflow_timer_;
  interrupts();

  // check for rollover
  if (capture_time_ > rise_time_prev_)
  {
    duration_ = capture_time_ - rise_time_prev_;
  }
  else
  {
    duration_ = capture_time_ + (ul_max_ - rise_time_prev_) + 1;
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
    if (cycle_task_.enabled)
    {
      (*cycle_task_.func)(period_us_, on_duration_us_);
    }
  }
}

void InputCapture::updateOverflowTimer()
{
  overflow_timer_ += 0x10000UL;
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
