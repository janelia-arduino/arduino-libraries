// ----------------------------------------------------------------------------
// SavedVariable.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "SavedVariable.h"


#ifdef __AVR__
SavedVariable::SavedVariable()
{
}

void SavedVariable::setName(const ConstantString &name)
{
  name_ptr_ = &name;
}

void SavedVariable::setDefaultValue()
{
  const byte* p = (const byte*)(const void*)default_value_ptr_;
  int ee = eeprom_index_;
  int i;
  for (i = 0; i < size_; i++)
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

int SavedVariable::getSize()
{
  return size_;
}

boolean SavedVariable::compareName(const ConstantString &name_to_compare)
{
  return (&name_to_compare == name_ptr_);
}
#endif
