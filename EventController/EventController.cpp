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
  event_array_.fill(default_event);
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

EventId EventController::addEvent(const Callback callback)
{
  return addEventUsingTime(callback,0);
}

EventId EventController::addRecurringEvent(const Callback callback, const uint32_t period_ms, const uint16_t count)
{
  return addRecurringEventUsingTime(callback,0,period_ms,count);
}

EventId EventController::addInfiniteRecurringEvent(const Callback callback, const uint32_t period_ms)
{
  return addInfiniteRecurringEventUsingTime(callback,0,period_ms);
}

EventId EventController::addEventUsingTime(const Callback callback, const uint32_t time)
{
  index_t event_index = findAvailableEventIndex();
  if (event_index < EVENT_COUNT_MAX)
  {
    event_array_[event_index].callback = callback;
    event_array_[event_index].time = time;
    event_array_[event_index].free = false;
    event_array_[event_index].enabled = false;
    event_array_[event_index].infinite = false;
    event_array_[event_index].count = 1;
    event_array_[event_index].period_ms = 0;
    event_array_[event_index].inc = 0;
  }
  enableEvent(event_index);
  EventId event_id;
  event_id.index = event_index;
  event_id.callback = callback;
  return event_id;
}

EventId EventController::addRecurringEventUsingTime(const Callback callback, const uint32_t time, const uint32_t period_ms, const uint16_t count)
{
  index_t event_index = findAvailableEventIndex();
  if (event_index < EVENT_COUNT_MAX)
  {
    event_array_[event_index].callback = callback;
    event_array_[event_index].time = time;
    event_array_[event_index].free = false;
    event_array_[event_index].enabled = false;
    event_array_[event_index].infinite = false;
    event_array_[event_index].period_ms = period_ms;
    event_array_[event_index].count = count;
    event_array_[event_index].inc = 0;
  }
  enableEvent(event_index);
  EventId event_id;
  event_id.index = event_index;
  event_id.callback = callback;
  return event_id;
}

EventId EventController::addInfiniteRecurringEventUsingTime(const Callback callback, const uint32_t time, const uint32_t period_ms)
{
  index_t event_index = findAvailableEventIndex();
  if (event_index < EVENT_COUNT_MAX)
  {
    event_array_[event_index].callback = callback;
    event_array_[event_index].time = time;
    event_array_[event_index].free = false;
    event_array_[event_index].enabled = false;
    event_array_[event_index].infinite = true;
    event_array_[event_index].period_ms = period_ms;
    event_array_[event_index].count = 0;
    event_array_[event_index].inc = 0;
  }
  enableEvent(event_index);
  EventId event_id;
  event_id.index = event_index;
  event_id.callback = callback;
  return event_id;
}

EventId EventController::addEventUsingDelay(const Callback callback, const uint32_t delay)
{
  uint32_t time_now = getTime();
  uint32_t time = time_now + delay;
  return addEventUsingTime(callback,time);
}

EventId EventController::addRecurringEventUsingDelay(const Callback callback, const uint32_t delay, const uint32_t period_ms, const uint16_t count)
{
  uint32_t time_now = getTime();
  uint32_t time = time_now + delay;
  return addRecurringEventUsingTime(callback,time,period_ms,count);
}

EventId EventController::addInfiniteRecurringEventUsingDelay(const Callback callback, const uint32_t delay, const uint32_t period_ms)
{
  uint32_t time_now = getTime();
  uint32_t time = time_now + delay;
  return addInfiniteRecurringEventUsingTime(callback,time,period_ms);
}

EventId EventController::addEventUsingOffset(const Callback callback, const EventId event_id_origin, const uint32_t offset)
{
  index_t event_index_origin = event_id_origin.index;
  if (event_index_origin < EVENT_COUNT_MAX)
  {
    uint32_t time_origin = event_array_[event_index_origin].time;
    uint32_t time = time_origin + offset;
    return addEventUsingTime(callback,time);
  }
  else
  {
    return default_event_id;
  }
}

EventId EventController::addRecurringEventUsingOffset(const Callback callback, const EventId event_id_origin, const uint32_t offset, const uint32_t period_ms, const uint16_t count)
{
  index_t event_index_origin = event_id_origin.index;
  if (event_index_origin < EVENT_COUNT_MAX)
  {
    uint32_t time_origin = event_array_[event_index_origin].time;
    uint32_t time = time_origin + offset;
    return addRecurringEventUsingTime(callback,time,period_ms,count);
  }
  else
  {
    return default_event_id;
  }
}

EventId EventController::addInfiniteRecurringEventUsingOffset(const Callback callback, const EventId event_id_origin, const uint32_t offset, const uint32_t period_ms)
{
  index_t event_index_origin = event_id_origin.index;
  if (event_index_origin < EVENT_COUNT_MAX)
  {
    uint32_t time_origin = event_array_[event_index_origin].time;
    uint32_t time = time_origin + offset;
    return addInfiniteRecurringEventUsingTime(callback,time,period_ms);
  }
  else
  {
    return default_event_id;
  }
}

EventIdPair EventController::addPwmUsingTimePeriodOnDuration(const Callback callback_0, const Callback callback_1, uint32_t time, uint32_t period_ms, uint32_t on_duration_ms, uint16_t count)
{
  EventIdPair event_id_pair;
  event_id_pair.event_id_0 = addRecurringEventUsingTime(callback_0,time,period_ms,count);
  event_id_pair.event_id_1 = addRecurringEventUsingOffset(callback_1,event_id_pair.event_id_0,on_duration_ms,period_ms,count);
  return event_id_pair;
}

EventIdPair EventController::addPwmUsingDelayPeriodOnDuration(const Callback callback_0, const Callback callback_1, uint32_t delay, uint32_t period_ms, uint32_t on_duration_ms, uint16_t count)
{
  uint32_t time_now = getTime();
  uint32_t time = time_now + delay;
  return addPwmUsingTimePeriodOnDuration(callback_0,callback_1,time,period_ms,on_duration_ms,count);
}

EventIdPair EventController::addPwmUsingOffsetPeriodOnDuration(const Callback callback_0, const Callback callback_1, const EventId event_id_origin, const uint32_t offset, uint32_t period_ms, uint32_t on_duration_ms, uint16_t count)
{
  index_t event_index_origin = event_id_origin.index;
  if (event_index_origin < EVENT_COUNT_MAX)
  {
    uint32_t time_origin = event_array_[event_index_origin].time;
    uint32_t time = time_origin + offset;
    return addPwmUsingTimePeriodOnDuration(callback_0,callback_1,time,period_ms,on_duration_ms,count);
  }
  else
  {
    return default_event_id_pair;
  }
}

EventIdPair EventController::addInfinitePwmUsingTimePeriodOnDuration(const Callback callback_0, const Callback callback_1, uint32_t time, uint32_t period_ms, uint32_t on_duration_ms)
{
  EventIdPair event_id_pair;
  event_id_pair.event_id_0 = addInfiniteRecurringEventUsingTime(callback_0,time,period_ms);
  event_id_pair.event_id_1 = addInfiniteRecurringEventUsingOffset(callback_1,event_id_pair.event_id_0,on_duration_ms,period_ms);
  return event_id_pair;
}

EventIdPair EventController::addInfinitePwmUsingDelayPeriodOnDuration(const Callback callback_0, const Callback callback_1, uint32_t delay, uint32_t period_ms, uint32_t on_duration_ms)
{
  uint32_t time_now = getTime();
  uint32_t time = time_now + delay;
  return addInfinitePwmUsingTimePeriodOnDuration(callback_0,callback_1,time,period_ms,on_duration_ms);
}

EventIdPair EventController::addInfinitePwmUsingOffsetPeriodOnDuration(const Callback callback_0, const Callback callback_1, const EventId event_id_origin, const uint32_t offset, uint32_t period_ms, uint32_t on_duration_ms)
{
  index_t event_index_origin = event_id_origin.index;
  if (event_index_origin < EVENT_COUNT_MAX)
  {
    uint32_t time_origin = event_array_[event_index_origin].time;
    uint32_t time = time_origin + offset;
    return addInfinitePwmUsingTimePeriodOnDuration(callback_0,callback_1,time,period_ms,on_duration_ms);
  }
  else
  {
    return default_event_id_pair;
  }
}

void EventController::removeEvent(const EventId event_id)
{
  index_t event_index = event_id.index;
  if ((event_index < EVENT_COUNT_MAX) && (event_array_[event_index].callback == event_id.callback))
  {
    event_array_[event_index] = default_event;
  }
}

void EventController::removeEventPair(const EventIdPair event_id_pair)
{
  removeEvent(event_id_pair.event_id_0);
  removeEvent(event_id_pair.event_id_1);
}

void EventController::removeEvent(const index_t event_index)
{
  if (event_index < EVENT_COUNT_MAX)
  {
    event_array_[event_index] = default_event;
  }
}

void EventController::removeAllEvents()
{
  event_array_.fill(default_event);
}

void EventController::enableEvent(const EventId event_id)
{
  index_t event_index = event_id.index;
  if ((event_index < EVENT_COUNT_MAX) &&
      (event_array_[event_index].callback == event_id.callback) &&
      !event_array_[event_index].free)
  {
    event_array_[event_index].enabled = true;
  }
}

void EventController::enableEventPair(const EventIdPair event_id_pair)
{
  enableEvent(event_id_pair.event_id_0);
  enableEvent(event_id_pair.event_id_1);
}

void EventController::enableEvent(const index_t event_index)
{
  if ((event_index < EVENT_COUNT_MAX) && !event_array_[event_index].free)
  {
    event_array_[event_index].enabled = true;
  }
}

void EventController::disableEvent(const EventId event_id)
{
  index_t event_index = event_id.index;
  if ((event_index < EVENT_COUNT_MAX) &&
      (event_array_[event_index].callback == event_id.callback) &&
      !event_array_[event_index].free)
  {
    event_array_[event_index].enabled = false;
  }
}

void EventController::disableEventPair(const EventIdPair event_id_pair)
{
  disableEvent(event_id_pair.event_id_0);
  disableEvent(event_id_pair.event_id_1);
}

void EventController::disableEvent(const index_t event_index)
{
  if ((event_index < EVENT_COUNT_MAX) && !event_array_[event_index].free)
  {
    event_array_[event_index].enabled = false;
  }
}

Event EventController::getEvent(const EventId event_id)
{
  index_t event_index = event_id.index;
  if (event_index < EVENT_COUNT_MAX)
  {
    return event_array_[event_index];
  }
  else
  {
    return default_event;
  }
}

bool EventController::activeEvents()
{
  return (countActiveEvents() > 0);
}

int EventController::countActiveEvents()
{
  int active_events = 0;
  for (index_t event_index=0; event_index<event_array_.size(); ++event_index)
  {
    if ((!event_array_[event_index].free) && event_array_[event_index].enabled)
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

index_t EventController::findAvailableEventIndex()
{
  index_t event_index = 0;
  while ((event_index < EVENT_COUNT_MAX) && !event_array_[event_index].free)
  {
    ++event_index;
  }
  return event_index;
}

void EventController::update()
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    ++millis_;
  }
  for (index_t event_index = 0; event_index < EVENT_COUNT_MAX; ++event_index)
  {
    if ((!event_array_[event_index].free) && (event_array_[event_index].time <= millis_))
    {
      if ((event_array_[event_index].infinite) || (event_array_[event_index].inc < event_array_[event_index].count))
      {
        while ((event_array_[event_index].period_ms > 0) &&
               (event_array_[event_index].time <= millis_))
        {
          event_array_[event_index].time += event_array_[event_index].period_ms;
        }
        if (event_array_[event_index].enabled)
        {
          (*event_array_[event_index].callback)();
          ++event_array_[event_index].inc;
        }
      }
      else
      {
        removeEvent(event_index);
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
