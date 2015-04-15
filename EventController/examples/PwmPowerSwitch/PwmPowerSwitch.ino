#include "Arduino.h"
#include "Streaming.h"
#include "Array.h"
#include "SPI.h"
#include "PowerSwitch.h"
#include "EventController.h"


const int BAUDRATE = 9600;
const int LOOP_DELAY = 4000;
const int CS_PIN = 49;
const int IN_PIN = 48;
const int IC_COUNT = 4;
const int CHANNEL = 1;

PowerSwitch power_switch = PowerSwitch(CS_PIN, IN_PIN);

void channelOnEventCallback(int channel)
{
  power_switch.setChannelOn(channel);
}

void channelOffEventCallback(int channel)
{
  power_switch.setChannelOff(channel);
}

void spikeAndHoldStartEventCallback(int channel)
{
  power_switch.setChannelOn(channel+2);
}

void spikeAndHoldStopEventCallback(int channel)
{
  power_switch.setChannelOff(channel+2);
}

void spikeAndHold(int channel)
{
  int delay_ms = 100;
  int period_ms = 2;
  int on_duration_ms = 1;
  int count = 5;
  EventController::EventIdPair pwm_event_id_pair_0;
  pwm_event_id_pair_0 =
    EventController::event_controller.addPwmUsingDelayPeriodOnDuration(channelOnEventCallback,
                                                                       channelOffEventCallback,
                                                                       delay_ms,
                                                                       period_ms,
                                                                       on_duration_ms,
                                                                       count,
                                                                       channel,
                                                                       spikeAndHoldStartEventCallback);
  int offset_ms = count*period_ms;
  period_ms = 4;
  EventController::EventIdPair pwm_event_id_pair_1;
  pwm_event_id_pair_1 =
    EventController::event_controller.addPwmUsingOffsetPeriodOnDuration(channelOnEventCallback,
                                                                        channelOffEventCallback,
                                                                        pwm_event_id_pair_0.event_id_0,
                                                                        offset_ms,
                                                                        period_ms,
                                                                        on_duration_ms,
                                                                        count*100,
                                                                        channel,
                                                                        NULL,
                                                                        spikeAndHoldStopEventCallback);
  Serial << "pwm_event_id_pair_0 == pwm_event_id_pair_0 : " << (pwm_event_id_pair_0 == pwm_event_id_pair_0) << endl;
  Serial << "pwm_event_id_pair_0 == pwm_event_id_pair_1 : " << (pwm_event_id_pair_0 == pwm_event_id_pair_1) << endl;
  Serial << endl;
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
