#include "Arduino.h"
#include "Streaming.h"
#include "Array.h"
#include "EventController.h"


const int BAUDRATE = 9600;
const int LOOP_DELAY = 1000;
const int CLOCK_PERIOD = 1000;
const int CLOCK_START_DELAY = 2000;
const int CLOCK_MAX_COUNT = 25;
const int COUNTER_LIMIT = 10;
const int COUNTER_START_DELAY = 5000;
const int TRIGGER_OFFSET = 2000;
const int LED_PIN = 13;
const int LED_DELAY = 3000;
const int LED_PERIOD = 500;
const int LED_ON_DURATION = 250;
const int LED_COUNT = 5;
const int LED_2_DELAY = LED_DELAY*2 + LED_PERIOD*LED_COUNT;
const int LED_2_PERIOD = LED_PERIOD*2;
const int LED_2_ON_DURATION = LED_ON_DURATION*2;
const int LED_2_END_CLOCK = CLOCK_MAX_COUNT-5;
int clock = 0;
int counter = 0;
boolean triggered = false;

EventController::EventId clock_event_id;
EventController::EventId counter_event_id;
EventController::EventIdPair led_2_event_id_pair;

void clockUpdateEventCallback(int arg=-1)
{
  ++clock;
}

void counterUpdateEventCallback(int arg=-1)
{
  ++counter;
}

void triggerEventCallback(int arg=-1)
{
  triggered = true;
}

void ledOnEventCallback(int arg=-1)
{
  digitalWrite(LED_PIN, HIGH);
}

void ledOffEventCallback(int arg=-1)
{
  digitalWrite(LED_PIN, LOW);
}

void ledPwmStartEventCallback(int arg=-1)
{
  Serial << "led pwm start!" << endl;
}

void ledPwmStopEventCallback(int arg=-1)
{
  Serial << "led pwm stop!" << endl;
}

void setup()
{
  Serial.begin(BAUDRATE);
  delay(1000);

  pinMode(LED_PIN, OUTPUT);
  ledOffEventCallback();

  EventController::event_controller.setup();
  clock_event_id = EventController::event_controller.addInfiniteRecurringEventUsingDelay(clockUpdateEventCallback,
                                                                                         CLOCK_START_DELAY,
                                                                                         CLOCK_PERIOD);
  counter_event_id = EventController::event_controller.addRecurringEventUsingDelay(counterUpdateEventCallback,
                                                                                   COUNTER_START_DELAY,
                                                                                   CLOCK_PERIOD,
                                                                                   COUNTER_LIMIT);
  EventController::event_controller.addEventUsingOffset(triggerEventCallback,counter_event_id,TRIGGER_OFFSET);
  EventController::event_controller.addPwmUsingDelayPeriodOnDuration(ledOnEventCallback,
                                                                     ledOffEventCallback,
                                                                     LED_DELAY,
                                                                     LED_PERIOD,
                                                                     LED_ON_DURATION,
                                                                     LED_COUNT,
                                                                     -1,
                                                                     ledPwmStartEventCallback,
                                                                     ledPwmStopEventCallback);
  led_2_event_id_pair = EventController::event_controller.addInfinitePwmUsingDelayPeriodOnDuration(ledOnEventCallback,
                                                                                                   ledOffEventCallback,
                                                                                                   LED_2_DELAY,
                                                                                                   LED_2_PERIOD,
                                                                                                   LED_2_ON_DURATION);
}


void loop()
{
  Serial << "clock: " << clock << endl;
  Serial << "counter: " << counter << endl;
  Serial << "triggered: " << triggered << endl;
  Serial << "countActiveEvents: " << EventController::event_controller.countActiveEvents() << endl;
  Serial << endl;
  if (clock == CLOCK_MAX_COUNT)
  {
    EventController::event_controller.removeEvent(clock_event_id);
  }
  if (clock >= LED_2_END_CLOCK)
  {
    EventController::event_controller.removeEventPair(led_2_event_id_pair);
  }
  delay(LOOP_DELAY);
}
