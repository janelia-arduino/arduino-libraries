// ----------------------------------------------------------------------------
// InputCapture.cpp
//
//
// Author: Peter Polidoro
// ----------------------------------------------------------------------------
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "InputCapture.h"
#include <Streaming.h>

//---------- constructor ----------------------------------------------------

InputCapture::InputCapture() {
}

//---------- public ----------------------------------------------------

void InputCapture::init() {
  cycleTask.enabled = false;
  captureTime = 0;
  duration = 0;
  riseTimePrevious = 0;
  onDuration = 0;
  period = 0;

  startTimer();
}

void InputCapture::addCycleTask(void (*userFunc)(uint16_t period, uint16_t onDuration)) {
  cycleTask.func = userFunc;
  cycleTask.enabled = true;
}

void InputCapture::removeCycleTask() {
  cycleTask.enabled = false;
}

//------------------ private -----------------------------------------------

void InputCapture::startTimer() {
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    TCCR5A = 0; // clear control register A
    TCCR5B = 0; // set mode 0: normal operation, stop the timer
    // TCCR5B |= _BV(ICNC5); // activate noise canceler
    TCCR5B |= _BV(ICES5); // capture on rising edge
    TCCR5B |= _BV(CS51); // clk/8 for 0.5 uS resolution
    TIMSK5 = _BV(ICIE5); // use only input capture interrupt
  }
}

InputCapture inputCapture;

ISR(TIMER5_CAPT_vect) {
  inputCapture.update();
}
