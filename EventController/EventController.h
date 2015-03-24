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
#include "Constants.h"

namespace EventController
{
typedef void (*Callback)(void);

const int EVENT_COUNT_MAX = 32;

struct Event
{
  Callback callback;
  uint32_t time;
  boolean free;
  boolean enabled;
  boolean infinite;
  uint16_t period;
  uint16_t count;
  uint16_t inc;
  Event() :
    callback(NULL),
    time(0),
    free(true),
    enabled(false),
    infinite(false),
    period(0),
    count(0),
    inc(0) {}
};

class EventController
{
public:
  void setup();
  uint32_t getTime();
  void setTime(uint32_t time=0);
  uint8_t addEvent(Callback callback);
  uint8_t addRecurringEvent(Callback callback, uint16_t period, uint16_t count);
  uint8_t addInfiniteRecurringEvent(Callback callback, uint16_t period);
  uint8_t addEventUsingTime(Callback callback, uint32_t time);
  uint8_t addRecurringEventUsingTime(Callback callback, uint32_t time, uint16_t period, uint16_t count);
  uint8_t addInfiniteRecurringEventUsingTime(Callback callback, uint32_t time, uint16_t period);
  uint8_t addEventUsingDelay(Callback callback, uint32_t delay);
  uint8_t addRecurringEventUsingDelay(Callback callback, uint32_t delay, uint16_t period, uint16_t count);
  uint8_t addInfiniteRecurringEventUsingDelay(Callback callback, uint32_t delay, uint16_t period);
  uint8_t addEventUsingOffset(Callback callback, uint8_t event_id_origin, uint32_t offset);
  uint8_t addRecurringEventUsingOffset(Callback callback, uint8_t event_id_origin, uint32_t offset, uint16_t period, uint16_t count);
  void removeEvent(uint8_t event_id);
  void removeAllEvents();
  void enableEvent(uint8_t event_id);
  void disableEvent(uint8_t event_id);
  Event getEventDetails(uint8_t event_id);
  bool activeEvents();
  int countActiveEvents();
  int getEventCountMax();
  void update();
private:
  volatile uint32_t millis_;
  Array<Event,EVENT_COUNT_MAX> event_array_;
  bool startTimer();
  uint8_t findAvailableEventId();
};
}
#endif
