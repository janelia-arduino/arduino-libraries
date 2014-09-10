// ----------------------------------------------------------------------------
// LinearSensorArray.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "LinearSensorArray.h"
#include <Streaming.h>


//---------- constructor ----------------------------------------------------

LinearSensorArray::LinearSensorArray()
{
}

LinearSensorArray::LinearSensorArray(uint8_t si_pin, uint8_t clk_pin, const uint8_t analog_pins[]) :
  si_pin_(si_pin),
  clk_pin_(clk_pin),
  analog_pins_(analog_pins)
{
  // digitalWrite too slow, use port manipulation instead
  uint8_t si_port = digitalPinToPort(si_pin_);
  uint8_t clk_port = digitalPinToPort(clk_pin_);

  si_out_ = portOutputRegister(si_port);
  clk_out_ = portOutputRegister(clk_port);

  si_bitmask_ = digitalPinToBitMask(si_pin_);
  clk_bitmask_ = digitalPinToBitMask(clk_pin_);

}

//---------- public ----------------------------------------------------

void LinearSensorArray::init()
{
  pinMode(si_pin_, OUTPUT);
  pinMode(clk_pin_, OUTPUT);
  *si_out_ &= ~si_bitmask_;
  *clk_out_ &= ~clk_bitmask_;
}

void LinearSensorArray::getImage(LinearSensorArrayImage* image)
{
  // dereference in advance to increase speed
  volatile uint8_t & si_out_deref_ = *si_out_;
  volatile uint8_t & clk_out_deref_ = *clk_out_;

  // first reset all cells by doing a dummy read

  // si_pin = 1, clk_pin = 0
  // digitalWrite(clk_pin,LOW);
  clk_out_deref_ &= ~clk_bitmask_;
  // digitalWrite(si_pin,HIGH);
  si_out_deref_ |= si_bitmask_;

  // si = 1, clk_pin = 1
  // digitalWrite(clk_pin,HIGH);
  clk_out_deref_ |= clk_bitmask_;

  // si_pin = 0, clk_pin = 0
  // digitalWrite(si_pin,LOW);
  si_out_deref_ &= ~si_bitmask_;
  // digitalWrite(clk_pin,LOW);
  clk_out_deref_ &= ~clk_bitmask_;

  for (int p=0; p<(image->getPixelPerSensorCount()+1); p++)
  {
    // si_pin = 0, clk_pin = 1
    // digitalWrite(clk_pin,HIGH);
    clk_out_deref_ |= clk_bitmask_;
    // si_pin = 0, clk_pin = 0
    // digitalWrite(clk_pin,LOW);
    clk_out_deref_ &= ~clk_bitmask_;
  }

  // do the integration pause

  // integration time in the range 0 - 32767
  int itime = 0;
  for (int i=0; i<itime; i++)
  {
    // si_pin = 0, clk_pin = 1
    // digitalWrite(clk_pin,HIGH);
    clk_out_deref_ |= clk_bitmask_;
    // si_pin = 0, clk_pin = 0
    // digitalWrite(clk_pin,LOW);
    clk_out_deref_ &= ~clk_bitmask_;
  }

  // read out the image
  // si_pin = 1, clk_pin = 0
  // digitalWrite(si_pin,HIGH);
  si_out_deref_ |= si_bitmask_;

  // si_pin = 1, clk_pin = 1
  // digitalWrite(clk_pin,HIGH);
  clk_out_deref_ |= clk_bitmask_;

  // si_pin = 0, clk_pin = 1
  // digitalWrite(si_pin,LOW);
  si_out_deref_ &= ~si_bitmask_;
  // si_pin = 0, clk_pin = 0
  // digitalWrite(clk_pin,LOW);
  clk_out_deref_ &= ~clk_bitmask_;

  for (int p=0; p<image->getPixelPerSensorCount(); p++)
  {
    // read the current pixel analog value from each sensor
    for (int s=0; s<image->getSensorCount(); s++)
    {
      image->setPixel(s, p, analogRead(analog_pins_[s]));
    }

    // clock out the next pixel from each sensor
    // si_pin = 0, clk_pin = 1
    // digitalWrite(clk_pin,HIGH);
    clk_out_deref_ |= clk_bitmask_;
    // si_pin = 0, clk_pin = 0
    // digitalWrite(clk_pin,LOW);
    clk_out_deref_ &= ~clk_bitmask_;
  }
  // extra clock at the end
  // si_pin = 0, clk_pin = 1 */
  // digitalWrite(clk_pin,HIGH);
  clk_out_deref_ |= clk_bitmask_;
  // si_pin = 0, clk_pin = 0 */
  // digitalWrite(clk_pin,LOW);
  clk_out_deref_ &= ~clk_bitmask_;

}
