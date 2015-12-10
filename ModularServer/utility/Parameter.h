// ----------------------------------------------------------------------------
// Parameter.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef _MODULAR_DEVICE_PARAMETER_H_
#define _MODULAR_DEVICE_PARAMETER_H_
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "ConstantVariable.h"
#include "JsonStream.h"
#include "Constants.h"


namespace ModularDevice
{
class Command;
class ModularDevice;

class Parameter
{
public:
  Parameter();
  Parameter(const ConstantString &name);
  void setName(const ConstantString &name);
  void setUnits(const ConstantString &name);
  void setTypeLong();
  void setTypeDouble();
  void setTypeBool();
  void setTypeString();
  void setTypeObject();
  void setTypeArray();
  template<typename T>
  void setRange(const T min, const T max)
  {
    min_.l = (long)min;
    max_.l = (long)max;
    setTypeLong();
    range_is_set_ = true;
  }
  void setRange(const double min, const double max);
  void setRange(const float min, const float max);
  void removeRange();
private:
  const ConstantString *name_ptr_;
  const ConstantString *units_ptr_;
  JsonStream::JsonTypes type_;
  JsonStream::JsonTypes array_element_type_;
  constants::NumberType min_;
  constants::NumberType max_;
  bool range_is_set_;
  bool compareName(const char *name_to_compare);
  bool compareName(const ConstantString &name_to_compare);
  const ConstantString& getName();
  const ConstantString& getUnits();
  JsonStream::JsonTypes getType();
  JsonStream::JsonTypes getArrayElementType();
  bool rangeIsSet();
  constants::NumberType getMin();
  constants::NumberType getMax();
  friend class Method;
  friend class Server;
};
}
#endif
