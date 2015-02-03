#include "Arduino.h"
#include "InputCapture.h"
#include <Streaming.h>

// Writes period and on_duration values to serial port for display.

// Attach function generator to ICP5 (pin 48 on Arudino Mega 2560) and
// use 0-5V square wave from ~31-100Hz (~32-10ms period). Multiply
// period and on_duration values by 500 to get units of nanoseconds.

const int BAUDRATE = 9600;
const int LOOP_DELAY = 1000;

unsigned int period_display;
unsigned int on_duration_display;
unsigned int freq_display;

void writePeriodSerial(unsigned int period_us, unsigned int on_duration_us)
{
  period_display = period_us;
  on_duration_display = on_duration_us;
  unsigned int freq = 1000000/period_us;
  freq_display = freq;
}

void setup()
{
  input_capture.init();

  // Setup serial communications
  Serial.begin(BAUDRATE);

  input_capture.addCycleTask(writePeriodSerial);
}


void loop()
{
  Serial << "period = " << period_display << endl;
  Serial << "on_duration = " << on_duration_display << endl;
  Serial << "freq = " << freq_display << endl;
  delay(LOOP_DELAY);
}
