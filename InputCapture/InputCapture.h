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
#include "Streaming.h"


class InputCapture
{
public:
  InputCapture();
  void setup();
  void addCycleTask(void (*userFunc)(unsigned long period_us, unsigned long on_duration_us));
  void removeCycleTask();
private:
  struct task_t {
    bool enabled;
    void (*func)(unsigned long period_us, unsigned long on_duration_us);
  };
  task_t cycle_task_;
  volatile unsigned long long virtual_timer_;
  volatile unsigned long long capture_time_;
  volatile unsigned long long rise_time_prev_;
  volatile unsigned long duration_;
  volatile unsigned long on_duration_us_;
  volatile unsigned long period_us_;

  void startTimer();
  void update();
  void updateVirtualTimer();
  friend void inputCaptureUpdate();
  friend void inputCaptureUpdateVirtualTimer();
};

extern InputCapture input_capture;

inline void inputCaptureUpdate() {input_capture.update();}
inline void inputCaptureUpdateVirtualTimer() {input_capture.updateVirtualTimer();}

#endif
