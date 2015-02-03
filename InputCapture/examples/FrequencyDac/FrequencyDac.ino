#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "SPI.h"
#include "Streaming.h"
#include "AD57X4R.h"
#include "Watchdog.h"
#include "InputCapture.h"


// Writes frequency value to AD57X4R DAC analog output.
// <80Hz = 0V
// >=80Hz && <=300Hz : 100Hz = 1V, 250Hz = 2.5V...
// >300Hz : ignore

// Attach function generator to ICP5 (pin 48 on Arudino Mega 2560) and
// use 0-5V square wave from ~31-400Hz (~32-2.5ms period).

const int DAC_CS = 49;
const int FREQ_MIN = 80;
const int FREQ_MAX = 300;

unsigned int dac_value_min;
unsigned int dac_value_max;
unsigned int dac_value;
unsigned int freq;

AD57X4R dac = AD57X4R(DAC_CS);

void watchdog_isr()
{
  dac_value = 0;
  dac.analogWrite(AD57X4R::A,dac_value);
}

void writeFreqDac(unsigned int period_us, unsigned int on_duration_us) {
  freq = 1000000/period_us;
  if (freq <= FREQ_MAX) {
    if (freq >= FREQ_MIN) {
      dac_value = map(freq, FREQ_MIN, FREQ_MAX, dac_value_min, dac_value_max);
    } else {
      dac_value = 0;
    }
    dac.analogWrite(AD57X4R::A,dac_value);
  }
  else
  {
    dac.analogWrite(AD57X4R::A,dac_value_max);
  }
  watchdog.resetTimer();
}

void setup()
{
  input_capture.init();

  // Initialize DAC
  dac.init(AD57X4R::AD5754R, AD57X4R::UNIPOLAR_5V);
  dac.analogWrite(AD57X4R::A,0);

  // Use watchdog to set dac to 0 when no edges detected
  watchdog.enableIsr(watchdog_isr);
  watchdog.begin(Watchdog::TIMEOUT_16MS);

  // Setup input_capture cycle task
  dac_value_min = (0.8/5.0)*dac.getMaxDacValue();
  dac_value_max = (3.0/5.0)*dac.getMaxDacValue();
  input_capture.addCycleTask(writeFreqDac);
}


void loop()
{
}
