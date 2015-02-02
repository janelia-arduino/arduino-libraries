// ----------------------------------------------------------------------------
// InputCapture.h
//
//
// Author: Peter Polidoro
// ----------------------------------------------------------------------------

#ifndef INPUT_CAPTURE_H_
#define INPUT_CAPTURE_H_
#include <util/atomic.h>
#include <avr/wdt.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

class InputCapture {
 public:
  InputCapture();

  void init();
  void update();
  void addCycleTask(void (*userFunc)(uint16_t period, uint16_t onDuration));
  void removeCycleTask();

 private:
  struct task_t {
    bool enabled;
    void (*func)(uint16_t period, uint16_t onDuration);
  };
  task_t cycleTask;
  volatile uint16_t captureTime;
  volatile uint16_t duration;
  volatile uint16_t riseTimePrevious;
  volatile uint16_t onDuration;
  volatile uint16_t period;

  void startTimer();
};

extern InputCapture inputCapture;

inline void InputCapture::update() {
  noInterrupts();
  captureTime = ICR5;
  TCCR5B ^= _BV(ICES5); // toggle capture edge
  interrupts();

  // check for rollover
  if (captureTime > riseTimePrevious) {
    duration = captureTime - riseTimePrevious;
  } else {
    duration = captureTime + (0xffff - riseTimePrevious) + 1;
  }

  if (TCCR5B & _BV(ICES5)) { // captured falling edge
    onDuration = duration;
  } else { // captured rising edge
    riseTimePrevious = captureTime;
    period = duration;
    if (cycleTask.enabled) {
      (*cycleTask.func)(period, onDuration);
    }
  }

}


#endif // INPUT_CAPTURE_H_



