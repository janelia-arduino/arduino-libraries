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
// >=80Hz && <=300Hz : 90HZ = 0.9V, 100Hz = 1V, 250Hz = 2.5V ...
// >300Hz : 3V

// Attach function generator to ICP5 (pin 48 on Arudino Mega 2560) and
// use 0-5V square wave from ~31-400Hz (~32-2.5ms period).

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
  Serial << "watchdog!" << endl;
}

void writeFreqDac(unsigned int period_us, unsigned int on_duration_us)
{
  freq_hz = 1000000/period_us;
  if (freq_hz <= FREQ_MAX_HZ)
  {
    if (freq_hz >= FREQ_MIN_HZ)
    {
      dac_value = map(freq_hz, FREQ_MIN_HZ, FREQ_MAX_HZ, dac_value_min, dac_value_max);
    }
    else
    {
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
  input_capture.setup();

  Serial.begin(9600);

  // Initialize DAC
  dac.init(AD57X4R::AD5754R, AD57X4R::UNIPOLAR_5V);
  dac.analogWrite(AD57X4R::A,0);

  // Use watchdog to set dac to 0 when no edges detected
  watchdog.enableIsr(watchdogIsr);
  watchdog.begin(Watchdog::TIMEOUT_16MS);

  // Setup input_capture cycle task
  dac_value_min = (VOLT_MIN/VOLT_RAIL)*dac.getMaxDacValue();
  dac_value_max = (VOLT_MAX/VOLT_RAIL)*dac.getMaxDacValue();
  input_capture.addCycleTask(writeFreqDac);
}


void loop()
{
}
