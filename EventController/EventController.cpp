// ----------------------------------------------------------------------------
// EventController.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "EventController.h"


namespace EventController
{
void EventController::setup()
{
  // for (uint8_t eventId = 0; eventId < EVENT_COUNT_MAX; eventId++)
  // {
  //   removeEvent(eventId);
  // }
  // conflictWindow = 10;
  // timer5_millis = 0;
  // startTimer();
}

uint32_t EventController::getTime()
{
  uint32_t time;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    time = millis_;
  }
  return time;
}

uint32_t EventController::setTime(uint32_t time)
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    millis_ = time;
  }
}

uint8_t EventController::addEventUsingTime(uint32_t time, Callback callback, long period=-1, long count=-1, bool checkConflict=false) {
  uint8_t eventId = findAvailableEventId(time,checkConflict);
  if (eventId < EVENT_COUNT_MAX) {
    events[eventId].time = time;
    events[eventId].func = userFunc;
    // if (combineArgsIfConflict) {
    //   events[eventId].arg = arg & events[eventId].arg;
    // } else {
    //   events[eventId].arg = arg;
    // }
    events[eventId].arg = arg;
    events[eventId].period = period;
    events[eventId].count = count;
    events[eventId].inc = 0;
    events[eventId].enabled = true;
    events[eventId].free = false;
  }
  return eventId;
}

uint8_t EventController::addEventUsingDelay(uint32_t delay,  void (*userFunc)(int), int arg, long period=-1, long count=-1, bool checkConflict=false) {
  uint32_t time_now = ms();
  uint32_t time = time_now + delay;

  // Figure out how to use function pointers to make this work!
  // uint8_t eventId = addEventUsingTime(time, userFunc, arg, period, checkConflict);
  // return eventId;

  uint8_t eventId = findAvailableEventId(time,checkConflict);
  if (eventId < EVENT_COUNT_MAX) {
    events[eventId].time = time;
    events[eventId].func = userFunc;
    events[eventId].arg = arg;
    events[eventId].period = period;
    events[eventId].count = count;
    events[eventId].inc = 0;
    events[eventId].enabled = true;
    events[eventId].free = false;
  }
  return eventId;
}

uint8_t EventController::addEventUsingOffset(uint8_t eventIdOrigin, uint32_t offset,  void (*userFunc)(int), int arg, long period, long count, bool checkConflict) {
  uint32_t time_base = events[eventIdOrigin].time;
  uint32_t time = time_base + offset;

  // Figure out how to use function pointers to make this work!
  // uint8_t eventId = addEventUsingTime(time, userFunc, arg, period, checkConflict);
  // return eventId;

  uint8_t eventId = findAvailableEventId(time,checkConflict);
  if (eventId < EVENT_COUNT_MAX) {
    events[eventId].time = time;
    events[eventId].func = userFunc;
    events[eventId].arg = arg;
    events[eventId].period = period;
    events[eventId].count = count;
    events[eventId].inc = 0;
    events[eventId].enabled = true;
    events[eventId].free = false;
  }
  return eventId;
}

bool EventController::removeEvent(uint8_t eventId) {
  if (eventId < EVENT_COUNT_MAX) {
    events[eventId].time = 0;
    events[eventId].free = true;
    events[eventId].enabled = false;
    events[eventId].period = -1;
    events[eventId].count = -1;
    events[eventId].inc = 0;
    events[eventId].arg = 0;
  }
}

bool EventController::removeAllEvents() {
  for (uint8_t eventId = 0; eventId < EVENT_COUNT_MAX; eventId++) {
    removeEvent(eventId);
  }
}

bool EventController::enableEvent(uint8_t eventId) {
  if (eventId < EVENT_COUNT_MAX) {
    events[eventId].enabled = true;
  }
}

bool EventController::disableEvent(uint8_t eventId) {
  if (eventId < EVENT_COUNT_MAX) {
    events[eventId].enabled = false;
  }
}

bool EventController::getEventDetails(uint8_t eventId, uint32_t& time, int& arg, long& period, long& count, bool& free, bool& enabled) {
  time = events[eventId].time;
  arg = events[eventId].arg;
  period = events[eventId].period;
  count = events[eventId].count;
  free = events[eventId].free;
  enabled = events[eventId].enabled;
}

bool EventController::activeEvents() {
  bool active_events = false;
  uint8_t eventId = 0;
  while ((!active_events) && (eventId < EVENT_COUNT_MAX)) {
    if ((!events[eventId].free) && events[eventId].enabled) {
      active_events = true;
    }
    eventId++;
  }
  return active_events;
}

int EventController::countActiveEvents() {
  int active_events = 0;
  for (uint8_t eventId = 0; eventId < EVENT_COUNT_MAX; eventId++) {
    if ((!events[eventId].free) && events[eventId].enabled) {
      active_events++;
    }
  }
  return active_events;
}

bool EventController::startTimer() {
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    TCCR5A = 0;                 // clear control register A
    TCCR5B = _BV(WGM53);        // set mode 8: phase and frequency correct pwm, stop the timer
    long cycles = (F_CPU / 2000); // the counter runs backwards after TOP, interrupt is at BOTTOM so divide microseconds by 2
    unsigned char clockSelectBits = _BV(CS50);  // no prescale, full xtal
    ICR5 = cycles;                // ICR5 is TOP in p & f correct pwm mode

    TCCR5B &= ~(_BV(CS50) | _BV(CS51) | _BV(CS52));
    TCCR5B |= clockSelectBits;   // reset clock select register, and starts the clock
    TIMSK5 = _BV(TOIE5);         // sets the timer overflow interrupt enable bit
  }
}

uint8_t EventController::findAvailableEventId(uint32_t time, bool checkConflict) {
  uint8_t eventId = 0;
  // if (combineArgsIfConflict) {
  //   uint32_t time_event;
  //   for (eventId = 0; eventId < EVENT_COUNT_MAX; eventId++) {
  //     if (!events[eventId].free) {
  //       time_event = events[eventId].time;
  //       if (abs(time_event - time) < conflictWindow/2) {
  //         return eventId;
  //       }
  //     }
  //   }
  // }
  while (!events[eventId].free) {
    eventId++;
  }
  if (EVENT_COUNT_MAX <= eventId) {
    return 255;
  }
  return eventId;
}

EventController tts;

ISR(TIMER5_OVF_vect) {
  tts.update();
}
}
