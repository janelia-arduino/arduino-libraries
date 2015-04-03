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
  typedef void (*Callback)(unsigned long period_us, unsigned long on_duration_us);
  InputCapture();
  void setup();
  void addCycleCallback(Callback callback);
  void removeCycleCallback();
  void begin();
private:
  boolean callback_enabled_;
  Callback callback_;
  volatile unsigned long overflow_timer_;
  volatile unsigned long capture_time_;
  volatile unsigned long rise_time_prev_;
  volatile unsigned long duration_;
  volatile unsigned long on_duration_us_;
  volatile unsigned long period_us_;
  unsigned long ul_max_;

  void update();
  void updateOverflowTimer();
  friend void inputCaptureUpdate();
  friend void inputCaptureUpdateOverflowTimer();
};

extern InputCapture input_capture;

inline void inputCaptureUpdate() {input_capture.update();}
inline void inputCaptureUpdateOverflowTimer() {input_capture.updateOverflowTimer();}

#endif
