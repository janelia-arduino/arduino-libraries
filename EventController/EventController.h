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

namespace EventController
{
typedef void (*Callback)(void);

class EventController
{
public:
  void setup();
  uint32_t getTime();
  uint32_t setTime(uint32_t time=0);
  uint8_t addEventUsingTime(uint32_t time, Callback callback, bool check_conflict=false);
  uint8_t addRecurringEventsUsingTime(uint32_t time, Callback callback, uint16_t count, uint16_t period, bool check_conflict=false);
  uint8_t addEventUsingDelay(uint32_t delay, Callback callback, bool check_conflict=false);
  uint8_t addRecurringEventsUsingDelay(uint32_t delay, Callback callback, uint16_t count, uint16_t period, bool check_conflict=false);
  uint8_t addEventUsingOffset(uint8_t event_id_origin, uint32_t offset, Callback callback, bool check_conflict=false);
  uint8_t addRecurringEventsUsingOffset(uint8_t event_id_origin, uint32_t offset, Callback callback, uint16_t count, uint16_t period, bool check_conflict=false);
  bool removeEvent(uint8_t event_id);
  bool removeAllEvents();
  bool enableEvent(uint8_t event_id);
  bool disableEvent(uint8_t event_id);
  void update();
  bool getEventDetails(uint8_t event_id, uint32_t& time, uint16_t& count, uint16_t& period, bool& free, bool& enabled);
  bool activeEvents();
  int countActiveEvents();
private:
  volatile uint32_t millis_;
  uint32_t conflict_window_;
  struct event_t {
    uint32_t time;
    bool free;
    bool enabled;
    uint16_t period;
    uint16_t count;
    uint16_t inc;
    Callback callback;
  };
  event_t events[EVENT_COUNT_MAX];
  bool startTimer();
  uint8_t findAvailableEventId(uint32_t time, bool checkConflict);
};
}
#endif
