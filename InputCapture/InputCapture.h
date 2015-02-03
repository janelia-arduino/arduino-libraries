// ----------------------------------------------------------------------------
// InputCapture.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef INPUT_CAPTURE_H
#define INPUT_CAPTURE_H
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <util/atomic.h>


class InputCapture
{
public:
  InputCapture();
  void init();
  void update();
  void addCycleTask(void (*userFunc)(unsigned int period_us, unsigned int on_duration_us));
  void removeCycleTask();
private:
  struct task_t {
    bool enabled;
    void (*func)(unsigned int period_us, unsigned int on_duration_us);
  };
  task_t cycle_task_;
  volatile unsigned int capture_time_;
  volatile unsigned int duration_;
  volatile unsigned int rise_time_prev_;
  volatile unsigned int on_duration_us_;
  volatile unsigned int period_us_;

  void startTimer();
};

extern InputCapture input_capture;

inline void InputCapture::update()
{
  noInterrupts();
  capture_time_ = ICR5;
  TCCR5B ^= _BV(ICES5); // toggle capture edge
  interrupts();

  // check for rollover
  if (capture_time_ > rise_time_prev_)
  {
    duration_ = capture_time_ - rise_time_prev_;
  }
  else
  {
    duration_ = capture_time_ + (0xffff - rise_time_prev_) + 1;
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
#endif
