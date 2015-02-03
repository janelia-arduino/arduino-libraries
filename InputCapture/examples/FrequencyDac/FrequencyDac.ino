#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <SPI.h>
#include <Streaming.h>
#include "InputCapture.h"
#include "AD57X4R.h"


// Writes frequency value to AD57X4R DAC analog output.
// <80Hz = 0V
// >=80Hz && <=300Hz : 100Hz = 1V, 250Hz = 2.5V...
// >300Hz : ignore

// Attach function generator to ICP5 (pin 48 on Arudino Mega 2560) and
// use 0-5V square wave from ~31-400Hz (~32-2.5ms period).

const int BAUDRATE = 9600;
const int DAC_CS = 49;
const int FREQ_MIN = 80;
const int FREQ_MAX = 300;
const int LOOP_DELAY = 1000;

unsigned int dac_value_min;
unsigned int dac_value_max;

unsigned int period_display;
unsigned int on_duration_display;
unsigned int freq_display;
unsigned int dac_value_display;

AD57X4R dac = AD57X4R(DAC_CS);

void writeFreqDac(unsigned int period_us, unsigned int on_duration_us) {
  period_display = period_us;
  on_duration_display = on_duration_us;
  unsigned int dac_value;
  unsigned int freq = 1000000/period_us;
  freq_display = freq;
  if (freq <= FREQ_MAX) {
    if (freq >= FREQ_MIN) {
      dac_value = map(freq, FREQ_MIN, FREQ_MAX, dac_value_min, dac_value_max);
    } else {
      dac_value = 0;
    }
    dac_value_display = dac_value;
    dac.analogWrite(AD57X4R::A,dac_value);
  }
  else
  {
    dac.analogWrite(AD57X4R::A,dac_value_max);
  }
}

// void watchdogSetup(void)
// {
//   // disable interrupts
//   cli();
//   // reset watchdog timer
//   wdt_reset();
//   /*
//     WDTCSR configuration:
//     WDIE = 1: Interrupt Enable
//     WDE = 1 :Reset Enable
//     See table for time-out variations:
//     WDP3 = 0 :For 1000ms Time-out
//     WDP2 = 1 :For 1000ms Time-out
//     WDP1 = 1 :For 1000ms Time-out
//     WDP0 = 0 :For 1000ms Time-out
//   */
//   // Enter Watchdog Configuration mode:
//   WDTCSR |= (1<<WDCE) | (1<<WDE);
//   // Set Watchdog settings:
//   WDTCSR = (1<<WDIE) | (1<<WDE) |
//     (0<<WDP3) | (1<<WDP2) | (1<<WDP1) |
//     (0<<WDP0);
//   sei();
// }

void setup()
{
  input_capture.init();

  // Initialize DAC
  dac.init(AD57X4R::AD5754R, AD57X4R::UNIPOLAR_5V);
  dac.analogWrite(AD57X4R::A,0);

  dac_value_min = (0.8/5.0)*dac.getMaxDacValue();
  dac_value_max = (3.0/5.0)*dac.getMaxDacValue();
  Serial.begin(BAUDRATE);
  Serial << "dac_value_min = " << dac_value_min << endl;
  Serial << "dac_value_max = " << dac_value_max << endl;
  input_capture.addCycleTask(writeFreqDac);
}


void loop()
{
  Serial << "period = " << period_display << endl;
  Serial << "on_duration = " << on_duration_display << endl;
  Serial << "freq = " << freq_display << endl;
  Serial << "dac_value = " << dac_value_display << endl;
  delay(LOOP_DELAY);
}
