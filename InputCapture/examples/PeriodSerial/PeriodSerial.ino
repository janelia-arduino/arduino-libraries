#include "Arduino.h"
#include "InputCapture.h"
#include <Streaming.h>

// Writes period and on_duration values to serial port for display.

// Attach function generator to ICP5 (pin 48 on Arudino Mega 2560) and
// use 0-5V square wave from ~31-100Hz (~32-10ms period). Multiply
// period and on_duration values by 500 to get units of nanoseconds.

const int BAUDRATE = 9600;

void writePeriodSerial(uint16_t period, uint16_t on_duration) {
  long period_ns = period*500L;
  long on_duration_ns = on_duration*500L;
  Serial << "period_ns = " << period_ns << ", on_duration_ns = " << on_duration_ns << endl;
}

void setup() {
  inputCapture.init();

  // Setup serial communications
  Serial.begin(BAUDRATE);

  inputCapture.addCycleTask(writePeriodSerial);
}


void loop() {
}
