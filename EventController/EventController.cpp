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
  millis_ = 0;
  Event default_event;
  event_array_.fill(default_event);
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

void EventController::setTime(uint32_t time)
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    millis_ = time;
  }
}

uint8_t EventController::addEvent(Callback callback)
{
  return addEventUsingTime(callback,0);
}

uint8_t EventController::addRecurringEvent(Callback callback, uint16_t period, uint16_t count)
{
  return addRecurringEventUsingTime(callback,0,period,count);
}

uint8_t EventController::addInfiniteRecurringEvent(Callback callback, uint16_t period)
{
  return addInfiniteRecurringEventUsingTime(callback,0,period);
}

uint8_t EventController::addEventUsingTime(Callback callback, uint32_t time)
{
  uint8_t event_id = findAvailableEventId();
  if (event_id < EVENT_COUNT_MAX)
  {
    events[event_id].callback = callback;
    events[event_id].time = time;
    events[event_id].free = false;
    events[event_id].enabled = true;
    events[event_id].infinite = false;
    events[event_id].count = 1;
    events[event_id].period = 0;
    events[event_id].inc = 0;
  }
  return event_id;
}

uint8_t EventController::addRecurringEventUsingTime(Callback callback, uint32_t time, uint16_t period, uint16_t count)
{
  uint8_t event_id = findAvailableEventId();
  if (event_id < EVENT_COUNT_MAX)
  {
    events[event_id].callback = callback;
    events[event_id].time = time;
    events[event_id].free = false;
    events[event_id].enabled = true;
    events[event_id].infinite = false;
    events[event_id].period = period;
    events[event_id].count = count;
    events[event_id].inc = 0;
  }
  return event_id;
}

uint8_t EventController::addInfiniteRecurringEventUsingTime(Callback callback, uint32_t time, uint16_t period)
{
  uint8_t event_id = findAvailableEventId();
  if (event_id < EVENT_COUNT_MAX)
  {
    events[event_id].callback = callback;
    events[event_id].time = time;
    events[event_id].free = false;
    events[event_id].enabled = true;
    events[event_id].infinite = true;
    events[event_id].period = period;
    events[event_id].count = 0;
    events[event_id].inc = 0;
  }
  return event_id;
}

uint8_t EventController::addEventUsingDelay(Callback callback, uint32_t delay)
{
  uint32_t time_now = getTime();
  uint32_t time = time_now + delay;
  return addEventUsingTime(callback,time);
}

uint8_t EventController::addRecurringEventUsingDelay(Callback callback, uint32_t delay, uint16_t period, uint16_t count)
{
  uint32_t time_now = getTime();
  uint32_t time = time_now + delay;
  return addRecurringEventUsingTime(callback,time,period,count);
}

uint8_t EventController::addInfiniteRecurringEventUsingDelay(Callback callback, uint32_t delay, uint16_t period)
{
  uint32_t time_now = getTime();
  uint32_t time = time_now + delay;
  return addInfiniteRecurringEventUsingTime(callback,time,period);
}

uint8_t EventController::addEventUsingOffset(Callback callback, uint8_t event_id_origin, uint32_t offset)
{
  uint32_t time_origin = event_array_[event_id_origin].time;
  uint32_t time = time_origin + offset;
  return addEventUsingTime(callback,time);
}

uint8_t EventController::addRecurringEventUsingOffset(Callback callback, uint8_t event_id_origin, uint32_t offset, uint16_t period, uint16_t count)
{
  uint32_t time_origin = event_array_[event_id_origin].time;
  uint32_t time = time_origin + offset;
  return addRecurringEventUsingTime(callback,time,period,count);
}

uint8_t EventController::addInfiniteRecurringEventUsingOffset(Callback callback, uint32_t offset, uint16_t period)
{
  uint32_t time_origin = event_array_[event_id_origin].time;
  uint32_t time = time_origin + offset;
  return addInfiniteRecurringEventUsingTime(callback,time,period);
}

void EventController::removeEvent(uint8_t event_id)
{
  if (event_id < EVENT_COUNT_MAX)
  {
    Event default_event;
    event_array_[event_id] = default_event;
  }
}

void EventController::removeAllEvents()
{
  Event default_event;
  event_array_.fill(default_event);
}

void EventController::enableEvent(uint8_t event_id)
{
  if (event_id < EVENT_COUNT_MAX)
  {
    event_array_[event_id].enabled = true;
  }
}

void EventController::disableEvent(uint8_t event_id)
{
  if (event_id < EVENT_COUNT_MAX)
  {
    event_array_[event_id].enabled = false;
  }
}

Event EventController::getEventDetails(uint8_t event_id)
{
  if (event_id < EVENT_COUNT_MAX)
  {
    return event_array_[event_id];
  }
  else
  {
    Event default_event;
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

EventController tts;

ISR(TIMER5_OVF_vect)
{
  tts.update();
}
}
