#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <util/atomic.h>
#include "Streaming.h"
#include "SPI.h"
#include "AD57X4R.h"
#include "Watchdog.h"
#include "InputCapture.h"
#include "BetterMap.h"


// Writes frequency value to AD57X4R DAC analog output.
// <80Hz = 0V
// >=80Hz && <=300Hz : 90HZ = 0.9V, 100Hz = 1V, 250Hz = 2.5V ...
// >300Hz : 3V

// Attach function generator to ICP5 (pin 48 on Arudino Mega 2560) and
// use 0-5V square wave from ~31-400Hz (~32-2.5ms period).

const boolean use_serial = true;

const int DAC_CS = 49;
const int FREQ_MIN_HZ = 80;
const int FREQ_MAX_HZ = 300;
const double VOLT_MIN = 0.8;
const double VOLT_MAX = 3.0;
const double VOLT_RAIL = 5.0;

unsigned int dac_value_min;
unsigned int dac_value_max;
unsigned int dac_value;
unsigned int freq_hz;

AD57X4R dac = AD57X4R(DAC_CS);

void watchdogIsr()
{
  dac.analogWrite(AD57X4R::A,0);
}

void writeFreqDac(unsigned long period_us, unsigned long on_duration_us)
{
  watchdog.resetTimer();

  freq_hz = 1000000UL/period_us;
  if (freq_hz <= FREQ_MAX_HZ)
  {
    if (freq_hz >= FREQ_MIN_HZ)
    {
      dac_value = betterMap(freq_hz, FREQ_MIN_HZ, FREQ_MAX_HZ, dac_value_min, dac_value_max);
    }
    else
    {
      dac_value = 0;
    }
  }
  else
  {
    dac_value = dac_value_max;
  }
  dac.analogWrite(AD57X4R::A,dac_value);
}

void setup()
{
  input_capture.setup();

  // Initialize DAC
  dac.init(AD57X4R::AD5754R, AD57X4R::UNIPOLAR_5V);
  dac.analogWrite(AD57X4R::A,0);

  // Setup input_capture cycle callback
  dac_value_min = (VOLT_MIN/VOLT_RAIL)*dac.getMaxDacValue();
  dac_value_max = (VOLT_MAX/VOLT_RAIL)*dac.getMaxDacValue();
  input_capture.addCycleCallback(writeFreqDac);

  // Use watchdog to set dac to 0 when no edges detected
  // TIMEOUT_16MS : or frequency is < 62.5Hz (1/16ms)
  watchdog.enableIsr(watchdogIsr);
  watchdog.begin(Watchdog::TIMEOUT_16MS);
}


void loop()
{
}
