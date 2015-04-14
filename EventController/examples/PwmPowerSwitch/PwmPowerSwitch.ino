#include "Arduino.h"
#include "Streaming.h"
#include "Array.h"
#include "SPI.h"
#include "PowerSwitch.h"
#include "EventController.h"


const int BAUDRATE = 9600;
const int LOOP_DELAY = 1000;
const int CS_PIN = 49;
const int IN_PIN = 48;
const int IC_COUNT = 4;
const int CHANNEL = 1;

PowerSwitch power_switch = PowerSwitch(CS_PIN, IN_PIN);

void channelOn(int channel)
{
  power_switch.setChannelOn(channel);
}

void channelOff(int channel)
{
  power_switch.setChannelOff(channel);
}

void spikeAndHold(int channel)
{
  int delay_ms = 100;
  int period_ms = 2;
  int on_duration_ms = 1;
  int count = 5;
  EventController::EventIdPair pwm_event_id_pair;
  pwm_event_id_pair =
    EventController::event_controller.addPwmUsingDelayPeriodOnDuration(channelOn,
                                                                       channelOff,
                                                                       delay_ms,
                                                                       period_ms,
                                                                       on_duration_ms,
                                                                       count,
                                                                       channel);
  int offset_ms = count*period_ms;
  period_ms = 4;
  pwm_event_id_pair =
    EventController::event_controller.addPwmUsingOffsetPeriodOnDuration(channelOn,
                                                                        channelOff,
                                                                        pwm_event_id_pair.event_id_0,
                                                                        offset_ms,
                                                                        period_ms,
                                                                        on_duration_ms,
                                                                        count,
                                                                        channel);
}

void setup()
{
  Serial.begin(BAUDRATE);

  power_switch.setup(IC_COUNT);

  EventController::event_controller.setup();
}


void loop()
{
  spikeAndHold(CHANNEL);
  delay(LOOP_DELAY);
  spikeAndHold(CHANNEL+1);
  delay(LOOP_DELAY);
}
