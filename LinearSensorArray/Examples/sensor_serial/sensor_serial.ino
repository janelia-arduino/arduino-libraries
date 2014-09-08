#include "Arduino.h"
#include "StandardCplusplus.h"
#include "LinearSensorArray.h"
#include <Streaming.h>

const uint8_t si_pin = 2;
const uint8_t clk_pin = 3;
//const uint8_t pixel_per_sensor_count = 128;
const int pixel_per_sensor_count = 768;
//#define SENSOR_COUNT 3
#define SENSOR_COUNT 1
//const int analog_pins[SENSOR_COUNT] = {0,1,2};
const uint8_t analog_pins[SENSOR_COUNT] = {0};

// pixel values: 0-1023

LinearSensorArray  linear_sensor_array(si_pin, clk_pin, analog_pins);
LinearSensorArrayImage image(SENSOR_COUNT,pixel_per_sensor_count);


void setup()
{
  linear_sensor_array.init();

  // Setup serial communications
  Serial.begin(115200);

}


void loop()
{
  linear_sensor_array.getImage(&image);
  for (int s=0; s<image.getSensorCount(); s++)
    {
      for (int p=0; p<image.getPixelPerSensorCount(); p++)
        {
          Serial << image.getPixel(s,p) << ",";
        }
    }
  Serial << endl;
}
