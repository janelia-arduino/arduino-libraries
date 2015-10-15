// ----------------------------------------------------------------------------
// GenericSerial.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "GenericSerial.h"

GenericSerial::GenericSerial()
{
  serial_ptr_ = NULL;
}

#ifdef __AVR__

GenericSerial::GenericSerial(HardwareSerial &serial)
{
  setSerial(serial);
}

void GenericSerial::setSerial(HardwareSerial &serial)
{
  serial_ptr_ = &serial;
}

HardwareSerial& GenericSerial::getSerial()
{
  return *serial_ptr_;
}

#elif defined(__PIC32MX__)

GenericSerial::GenericSerial(HardwareSerial &serial)
{
  setSerial(serial);
}

void GenericSerial::setSerial(HardwareSerial &serial)
{
  serial_ptr_ = &serial;
}

HardwareSerial& GenericSerial::getSerial()
{
  return *serial_ptr_;
}

#else

GenericSerial::GenericSerial(usb_serial_class &serial)
{
  setSerial(serial);
}

void GenericSerial::setSerial(usb_serial_class &serial)
{
  serial_ptr_ = &serial;
}

usb_serial_class& GenericSerial::getSerial()
{
  return *serial_ptr_;
}

#endif
