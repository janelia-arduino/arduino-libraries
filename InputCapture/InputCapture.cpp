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

void InputCapture::init()
{
  cycle_task_.enabled = false;
  capture_time_ = 0;
  duration = 0;
  rise_time_prev = 0;
  on_duration = 0;
  period = 0;

  startTimer();
}

void InputCapture::addCycleTask(void (*userFunc)(uint16_t period, uint16_t on_duration))
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
    // TCCR5B |= _BV(ICNC5); // activate noise canceler
    TCCR5B |= _BV(ICES5); // capture on rising edge
    TCCR5B |= _BV(CS51); // clk/8 for 0.5 uS resolution
    TIMSK5 = _BV(ICIE5); // use only input capture interrupt
  }
}

InputCapture input_capture;

ISR(TIMER5_CAPT_vect)
{
  input_capture.update();
}
