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
// #include <avr/wdt.h>

class InputCapture
{
public:
  InputCapture();
  void init();
  void update();
  void addCycleTask(void (*userFunc)(uint16_t period, uint16_t on_duration));
  void removeCycleTask();
private:
  struct task_t {
    bool enabled;
    void (*func)(uint16_t period, uint16_t on_duration);
  };
  task_t cycle_task_;
  volatile uint16_t capture_time_;
  volatile uint16_t duration;
  volatile uint16_t rise_time_prev;
  volatile uint16_t on_duration;
  volatile uint16_t period;

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
  if (capture_time_ > rise_time_prev)
  {
    duration = capture_time_ - rise_time_prev;
  }
  else
  {
    duration = capture_time_ + (0xffff - rise_time_prev) + 1;
  }

  if (TCCR5B & _BV(ICES5))
  { // captured falling edge
    on_duration = duration;
  }
  else
  { // captured rising edge
    rise_time_prev = capture_time_;
    period = duration;
    if (cycle_task_.enabled)
    {
      (*cycle_task_.func)(period, on_duration);
    }
  }

}
#endif // INPUT_CAPTURE_H
