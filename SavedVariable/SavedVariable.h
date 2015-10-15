// ----------------------------------------------------------------------------
// SavedVariable.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef SAVED_VARIABLE_H
#define SAVED_VARIABLE_H
#include "ConstantVariable.h"

#ifndef ARDUINO_SAM_DUE
#include <EEPROM.h>
#endif


class SavedVariable
{
public:
  SavedVariable();
  template<typename T>
  SavedVariable(const ConstantString &name,
                const unsigned int eeprom_index,
                const T &default_value);
  template<typename T>
  SavedVariable(const ConstantString &name,
                const unsigned int eeprom_index,
                const T default_value[],
                const unsigned int array_length);
  void setName(const ConstantString &name);
  template<typename T>
  int setValue(const T &value);
  template<typename T>
  int setValue(const T value[], const unsigned int array_index);
  template<typename T>
  int getValue(T &value);
  template<typename T>
  int getValue(T value[], unsigned int array_index);
  void setDefaultValue();
  int getSize();
  boolean compareName(const ConstantString& name_to_compare);
private:
  const ConstantString *name_ptr_;
  unsigned int eeprom_index_;
  unsigned int size_;
  const void *default_value_ptr_;
  unsigned int array_length_;
  unsigned int array_element_size_;
};
#include "SavedVariableDefinitions.h"
#endif
