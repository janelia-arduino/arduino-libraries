// ----------------------------------------------------------------------------
// EventController.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef EVENT_CONTROLLER_H
#define EVENT_CONTROLLER_H
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <util/atomic.h>
#include "Array.h"

#include "Streaming.h"

namespace EventController
{
void eventControllerUpdate();
typedef void (*Callback)(void);

const int EVENT_COUNT_MAX = 32;

struct Event
{
  Callback callback;
  uint32_t time;
  boolean free;
  boolean enabled;
  boolean infinite;
  uint32_t period_ms;
  uint16_t count;
  uint16_t inc;
  Event() :
    callback(NULL),
    time(0),
    free(true),
    enabled(false),
    infinite(false),
    period_ms(0),
    count(0),
    inc(0) {}
};

class EventController
{
public:
  void setup();
  uint32_t getTime();
  void setTime(const uint32_t time=0);
  uint8_t addEvent(const Callback callback);
  uint8_t addRecurringEvent(const Callback callback, const uint32_t period_ms, const uint16_t count);
  uint8_t addInfiniteRecurringEvent(const Callback callback, const uint32_t period_ms);
  uint8_t addEventUsingTime(const Callback callback, const uint32_t time);
  uint8_t addRecurringEventUsingTime(const Callback callback, const uint32_t time, const uint32_t period_ms, const uint16_t count);
  uint8_t addInfiniteRecurringEventUsingTime(const Callback callback, const uint32_t time, const uint32_t period_ms);
  uint8_t addEventUsingDelay(const Callback callback, const uint32_t delay);
  uint8_t addRecurringEventUsingDelay(const Callback callback, const uint32_t delay, const uint32_t period_ms, const uint16_t count);
  uint8_t addInfiniteRecurringEventUsingDelay(const Callback callback, const uint32_t delay, const uint32_t period_ms);
  uint8_t addEventUsingOffset(const Callback callback, const uint8_t event_id_origin, const uint32_t offset);
  uint8_t addRecurringEventUsingOffset(const Callback callback, const uint8_t event_id_origin, const uint32_t offset, const uint32_t period_ms, const uint16_t count);
  uint8_t addInfiniteRecurringEventUsingOffset(const Callback callback, const uint8_t event_id_origin, const uint32_t offset, const uint32_t period_ms);
  void removeEvent(const uint8_t event_id);
  void removeAllEvents();
  void enableEvent(const uint8_t event_id);
  void disableEvent(const uint8_t event_id);
  Event getEventDetails(const uint8_t event_id);
  bool activeEvents();
  int countActiveEvents();
  int getEventCountMax();
private:
  volatile uint32_t millis_;
  Array<Event,EVENT_COUNT_MAX> event_array_;
  const Event default_event_;
  bool startTimer();
  uint8_t findAvailableEventId();
  void update();
  friend void eventControllerUpdate();
};
}

extern EventController::EventController event_controller;

inline void EventController::eventControllerUpdate() {event_controller.update();}

#endif
