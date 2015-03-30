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
typedef uint8_t index_t;

const int EVENT_COUNT_MAX = 32;
const int DEFAULT_INDEX = 255;

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
const Event default_event;

struct EventId
{
  index_t index;
  Callback callback;
  EventId() :
    index(DEFAULT_INDEX),
    callback(NULL) {}
};
const EventId default_event_id;

struct EventIdPair
{
  EventId event_id_0;
  EventId event_id_1;
  EventIdPair() :
    event_id_0(default_event_id),
    event_id_1(default_event_id) {}
};
const EventIdPair default_event_id_pair;

class EventController
{
public:
  void setup();
  uint32_t getTime();
  void setTime(const uint32_t time=0);
  EventId addEvent(const Callback callback);
  EventId addRecurringEvent(const Callback callback, const uint32_t period_ms, const uint16_t count);
  EventId addInfiniteRecurringEvent(const Callback callback, const uint32_t period_ms);
  EventId addEventUsingTime(const Callback callback, const uint32_t time);
  EventId addRecurringEventUsingTime(const Callback callback, const uint32_t time, const uint32_t period_ms, const uint16_t count);
  EventId addInfiniteRecurringEventUsingTime(const Callback callback, const uint32_t time, const uint32_t period_ms);
  EventId addEventUsingDelay(const Callback callback, const uint32_t delay);
  EventId addRecurringEventUsingDelay(const Callback callback, const uint32_t delay, const uint32_t period_ms, const uint16_t count);
  EventId addInfiniteRecurringEventUsingDelay(const Callback callback, const uint32_t delay, const uint32_t period_ms);
  EventId addEventUsingOffset(const Callback callback, const EventId event_id_origin, const uint32_t offset);
  EventId addRecurringEventUsingOffset(const Callback callback, const EventId event_id_origin, const uint32_t offset, const uint32_t period_ms, const uint16_t count);
  EventId addInfiniteRecurringEventUsingOffset(const Callback callback, const EventId event_id_origin, const uint32_t offset, const uint32_t period_ms);
  EventIdPair addPwmUsingTimePeriodOnDuration(const Callback callback_0, const Callback callback_1, uint32_t time, uint32_t period_ms, uint32_t on_duration_ms, uint16_t count);
  EventIdPair addPwmUsingDelayPeriodOnDuration(const Callback callback_0, const Callback callback_1, uint32_t delay, uint32_t period_ms, uint32_t on_duration_ms, uint16_t count);
  EventIdPair addPwmUsingOffsetPeriodOnDuration(const Callback callback_0, const Callback callback_1, const EventId event_id_origin, const uint32_t offset, uint32_t period_ms, uint32_t on_duration_ms, uint16_t count);
  EventIdPair addInfinitePwmUsingTimePeriodOnDuration(const Callback callback_0, const Callback callback_1, uint32_t time, uint32_t period_ms, uint32_t on_duration_ms);
  EventIdPair addInfinitePwmUsingDelayPeriodOnDuration(const Callback callback_0, const Callback callback_1, uint32_t delay, uint32_t period_ms, uint32_t on_duration_ms);
  EventIdPair addInfinitePwmUsingOffsetPeriodOnDuration(const Callback callback_0, const Callback callback_1, const EventId event_id_origin, const uint32_t offset, uint32_t period_ms, uint32_t on_duration_ms);
  void removeEvent(const EventId event_id);
  void removeEventPair(const EventIdPair event_id_pair);
  void removeAllEvents();
  void enableEvent(const EventId event_id);
  void enableEventPair(const EventIdPair event_id_pair);
  void disableEvent(const EventId event_id);
  void disableEventPair(const EventIdPair event_id_pair);
  Event getEvent(const EventId event_id);
  bool activeEvents();
  int countActiveEvents();
  int getEventCountMax();
private:
  volatile uint32_t millis_;
  Array<Event,EVENT_COUNT_MAX> event_array_;
  bool startTimer();
  index_t findAvailableEventIndex();
  void update();
  void removeEvent(const index_t event_index);
  void enableEvent(const index_t event_index);
  void disableEvent(const index_t event_index);
  friend void eventControllerUpdate();
};
}

extern EventController::EventController event_controller;

inline void EventController::eventControllerUpdate() {event_controller.update();}

#endif
