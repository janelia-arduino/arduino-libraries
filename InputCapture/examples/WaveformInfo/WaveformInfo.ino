#include "Arduino.h"
#include "InputCapture.h"
#include <Streaming.h>

// Writes period and on_duration values to serial port for display.

// Attach function generator to ICP5 (pin 48 on Arudino Mega 2560) and
// use 0-5V square wave from ~31-100Hz (~32-10ms period). Multiply
// period and on_duration values by 500 to get units of nanoseconds.

const int BAUDRATE = 9600;
const int LOOP_DELAY = 300;

unsigned int period_display;
unsigned int on_duration_display;
unsigned int duty_cycle_display;
unsigned int freq_display;

void updateWaveformMeasurements(unsigned long period_us, unsigned long on_duration_us)
{
  period_display = period_us;
  on_duration_display = on_duration_us;
  duty_cycle_display = (100*on_duration_us)/period_us;
  freq_display = 1000000/period_us;
}

void setup()
{
  input_capture.setup();

  // Setup serial communications
  Serial.begin(BAUDRATE);

  input_capture.addCycleTask(updateWaveformMeasurements);
}


void loop()
{
  Serial << "period (microseconds) = " << period_display << endl;
  Serial << "on_duration (microseconds) = " << on_duration_display << endl;
  Serial << "duty_cycle (%) = " << duty_cycle_display << endl;
  Serial << "freq (Hz)= " << freq_display << endl;
  delay(LOOP_DELAY);
}
