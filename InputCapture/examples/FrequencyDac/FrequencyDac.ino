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
#include "BetterMap.h"


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

const int BAUDRATE = 9600;
const int LOOP_DELAY = 300;
unsigned long period_display;
unsigned int freq_display;
unsigned int dac_value_display;

void watchdogIsr()
{
  dac.analogWrite(AD57X4R::A,0);
}

void writeFreqDac(unsigned long period_us, unsigned long on_duration_us)
{
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
  watchdog.resetTimer();

  period_display = period_us;
  freq_display = freq_hz;
  dac_value_display = dac_value;
}

void setup()
{
  input_capture.setup();

  Serial.begin(BAUDRATE);

  // Initialize DAC
  dac.init(AD57X4R::AD5754R, AD57X4R::UNIPOLAR_5V);
  dac.analogWrite(AD57X4R::A,0);

  // Use watchdog to set dac to 0 when no edges detected
  // or frequency is < 62.5Hz (1/16ms)
  watchdog.enableIsr(watchdogIsr);
  watchdog.begin(Watchdog::TIMEOUT_16MS);

  // Setup input_capture cycle task
  dac_value_min = (VOLT_MIN/VOLT_RAIL)*dac.getMaxDacValue();
  dac_value_max = (VOLT_MAX/VOLT_RAIL)*dac.getMaxDacValue();
  input_capture.addCycleTask(writeFreqDac);
}


void loop()
{
  Serial << "period (microseconds) = " << period_display << endl;
  Serial << "freq (Hz)= " << freq_display << endl;
  Serial << "dac_value = " << dac_value_display << endl;
  Serial << endl;
  delay(LOOP_DELAY);
}
