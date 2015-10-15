// ----------------------------------------------------------------------------
// SavedVariable.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "SavedVariable.h"


SavedVariable::SavedVariable()
{
}

void SavedVariable::setName(const ConstantString &name)
{
  name_ptr_ = &name;
}

#ifndef ARDUINO_SAM_DUE
void SavedVariable::setDefaultValue()
{
  const byte* p = (const byte*)(const void*)default_value_ptr_;
  int ee = eeprom_index_;
  for (unsigned int i = 0; i < size_; i++)
  {
    if(EEPROM.read(ee)==*p)
    {
      ee++;
      p++;
    }
    else
    {
      EEPROM.write(ee++,*p++);
    }
  }
}
#else
void SavedVariable::setDefaultValue()
{
}
#endif

int SavedVariable::getSize()
{
  return size_;
}

boolean SavedVariable::compareName(const ConstantString &name_to_compare)
{
  return (&name_to_compare == name_ptr_);
}
