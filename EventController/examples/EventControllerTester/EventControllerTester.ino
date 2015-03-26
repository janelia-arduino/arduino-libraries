#include "Arduino.h"
#include "Streaming.h"
#include "Array.h"
#include "EventController.h"


const int BAUDRATE = 9600;
const int LOOP_DELAY = 1000;
const int CLOCK_PERIOD = 1000;
const int COUNTER_LIMIT = 10;
const int COUNTER_DELAY = 5000;
const int TRIGGER_OFFSET = 2000;
int clock = 0;
int counter = 0;
boolean triggered = false;

void clockUpdate()
{
  ++clock;
}

void counterUpdate()
{
  ++counter;
}

void trigger()
{
  triggered = true;
}

void setup()
{
  Serial.begin(BAUDRATE);
  delay(1000);
  event_controller.setup();
  event_controller.addInfiniteRecurringEvent(clockUpdate,CLOCK_PERIOD);
  uint8_t counter_event_id = event_controller.addRecurringEventUsingDelay(counterUpdate,COUNTER_DELAY,CLOCK_PERIOD,COUNTER_LIMIT);
  event_controller.addEventUsingOffset(trigger,counter_event_id,TRIGGER_OFFSET);
}


void loop()
{
  Serial << "clock: " << clock << endl;
  Serial << "counter: " << counter << endl;
  Serial << "triggered: " << triggered << endl;
  Serial << "countActiveEvents: " << event_controller.countActiveEvents() << endl;
  Serial << endl;
  delay(LOOP_DELAY);
}
