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
  event_array_.fill(default_event_);
  startTimer();
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

void EventController::setTime(const uint32_t time)
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    millis_ = time;
  }
}

uint8_t EventController::addEvent(const Callback callback)
{
  return addEventUsingTime(callback,0);
}

uint8_t EventController::addRecurringEvent(const Callback callback, const uint32_t period_ms, const uint16_t count)
{
  return addRecurringEventUsingTime(callback,0,period_ms,count);
}

uint8_t EventController::addInfiniteRecurringEvent(const Callback callback, const uint32_t period_ms)
{
  return addInfiniteRecurringEventUsingTime(callback,0,period_ms);
}

uint8_t EventController::addEventUsingTime(const Callback callback, const uint32_t time)
{
  uint8_t event_id = findAvailableEventId();
  if (event_id < EVENT_COUNT_MAX)
  {
    event_array_[event_id].callback = callback;
    event_array_[event_id].time = time;
    event_array_[event_id].free = false;
    event_array_[event_id].enabled = false;
    event_array_[event_id].infinite = false;
    event_array_[event_id].count = 1;
    event_array_[event_id].period_ms = 0;
    event_array_[event_id].inc = 0;
  }
  enableEvent(event_id);
  return event_id;
}

uint8_t EventController::addRecurringEventUsingTime(const Callback callback, const uint32_t time, const uint32_t period_ms, const uint16_t count)
{
  uint8_t event_id = findAvailableEventId();
  if (event_id < EVENT_COUNT_MAX)
  {
    event_array_[event_id].callback = callback;
    event_array_[event_id].time = time;
    event_array_[event_id].free = false;
    event_array_[event_id].enabled = false;
    event_array_[event_id].infinite = false;
    event_array_[event_id].period_ms = period_ms;
    event_array_[event_id].count = count;
    event_array_[event_id].inc = 0;
  }
  enableEvent(event_id);
  return event_id;
}

uint8_t EventController::addInfiniteRecurringEventUsingTime(const Callback callback, const uint32_t time, const uint32_t period_ms)
{
  uint8_t event_id = findAvailableEventId();
  if (event_id < EVENT_COUNT_MAX)
  {
    event_array_[event_id].callback = callback;
    event_array_[event_id].time = time;
    event_array_[event_id].free = false;
    event_array_[event_id].enabled = false;
    event_array_[event_id].infinite = true;
    event_array_[event_id].period_ms = period_ms;
    event_array_[event_id].count = 0;
    event_array_[event_id].inc = 0;
  }
  enableEvent(event_id);
  return event_id;
}

uint8_t EventController::addEventUsingDelay(const Callback callback, const uint32_t delay)
{
  uint32_t time_now = getTime();
  uint32_t time = time_now + delay;
  return addEventUsingTime(callback,time);
}

uint8_t EventController::addRecurringEventUsingDelay(const Callback callback, const uint32_t delay, const uint32_t period_ms, const uint16_t count)
{
  uint32_t time_now = getTime();
  uint32_t time = time_now + delay;
  return addRecurringEventUsingTime(callback,time,period_ms,count);
}

uint8_t EventController::addInfiniteRecurringEventUsingDelay(const Callback callback, const uint32_t delay, const uint32_t period_ms)
{
  uint32_t time_now = getTime();
  uint32_t time = time_now + delay;
  return addInfiniteRecurringEventUsingTime(callback,time,period_ms);
}

uint8_t EventController::addEventUsingOffset(const Callback callback, const uint8_t event_id_origin, const uint32_t offset)
{
  if (event_id_origin < EVENT_COUNT_MAX)
  {
    uint32_t time_origin = event_array_[event_id_origin].time;
    uint32_t time = time_origin + offset;
    return addEventUsingTime(callback,time);
  }
  else
  {
    return event_id_origin;
  }
}

uint8_t EventController::addRecurringEventUsingOffset(const Callback callback, const uint8_t event_id_origin, const uint32_t offset, const uint32_t period_ms, const uint16_t count)
{
  if (event_id_origin < EVENT_COUNT_MAX)
  {
    uint32_t time_origin = event_array_[event_id_origin].time;
    uint32_t time = time_origin + offset;
    return addRecurringEventUsingTime(callback,time,period_ms,count);
  }
  else
  {
    return event_id_origin;
  }
}

uint8_t EventController::addInfiniteRecurringEventUsingOffset(const Callback callback, const uint8_t event_id_origin, const uint32_t offset, const uint32_t period_ms)
{
  if (event_id_origin < EVENT_COUNT_MAX)
  {
    uint32_t time_origin = event_array_[event_id_origin].time;
    uint32_t time = time_origin + offset;
    return addInfiniteRecurringEventUsingTime(callback,time,period_ms);
  }
  else
  {
    return event_id_origin;
  }
}

void EventController::removeEvent(const uint8_t event_id)
{
  if (event_id < EVENT_COUNT_MAX)
  {
    event_array_[event_id] = default_event_;
  }
}

void EventController::removeAllEvents()
{
  event_array_.fill(default_event_);
}

void EventController::enableEvent(const uint8_t event_id)
{
  if ((event_id < EVENT_COUNT_MAX) && !event_array_[event_id].free)
  {
    event_array_[event_id].enabled = true;
  }
}

void EventController::disableEvent(const uint8_t event_id)
{
  if ((event_id < EVENT_COUNT_MAX) && !event_array_[event_id].free)
  {
    event_array_[event_id].enabled = false;
  }
}

Event EventController::getEventDetails(const uint8_t event_id)
{
  if (event_id < EVENT_COUNT_MAX)
  {
    return event_array_[event_id];
  }
  else
  {
    return default_event_;
  }
}

bool EventController::activeEvents()
{
  return (countActiveEvents() > 0);
}

int EventController::countActiveEvents()
{
  int active_events = 0;
  for (uint8_t event_id=0; event_id<event_array_.size(); ++event_id)
  {
    if ((!event_array_[event_id].free) && event_array_[event_id].enabled)
    {
      ++active_events;
    }
  }
  return active_events;
}

bool EventController::startTimer()
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    millis_ = 0;
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

uint8_t EventController::findAvailableEventId()
{
  uint8_t event_id = 0;
  while ((event_id < EVENT_COUNT_MAX) && !event_array_[event_id].free)
  {
    ++event_id;
  }
  return event_id;
}

void EventController::update()
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    ++millis_;
  }
  for (uint8_t event_id = 0; event_id < EVENT_COUNT_MAX; ++event_id)
  {
    if ((!event_array_[event_id].free) && (event_array_[event_id].time <= millis_))
    {
      if ((event_array_[event_id].infinite) || (event_array_[event_id].inc < event_array_[event_id].count))
      {
        while ((event_array_[event_id].period_ms > 0) &&
               (event_array_[event_id].time <= millis_))
        {
          event_array_[event_id].time += event_array_[event_id].period_ms;
        }
        if (event_array_[event_id].enabled)
        {
          (*event_array_[event_id].callback)();
          ++event_array_[event_id].inc;
        }
      }
      else
      {
        removeEvent(event_id);
      }
    }
  }
}
}

EventController::EventController event_controller;

ISR(TIMER5_OVF_vect)
{
  EventController::eventControllerUpdate();
}
