// ----------------------------------------------------------------------------
// ConstantVariable.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef CONSTANT_VARIABLE_H
#define CONSTANT_VARIABLE_H
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#ifdef __AVR__
#include "Flash.h"

// Use these macros to define your constant data structures
// Example: CONSTANT_STRING(str, "Four score and seven years ago");
#define CONSTANT_STRING(name, value) \
static const char name##_flash[] PROGMEM = value; \
ConstantString name(name##_flash);

class ConstantString : public _FLASH_STRING
{
public:
  ConstantString(const char PROGMEM *arr) : _FLASH_STRING(arr){};
};

#else

// Use these macros to define your constant data structures
// Example: CONSTANT_STRING(str, "Four score and seven years ago");
#define CONSTANT_STRING(name, value) \
static const char name##_const[] = value; \
ConstantString name(name##_const);

class ConstantString
{
public:
  ConstantString(const char *arr) : str_(String(arr)){};
  size_t length() const
  {
    return str_.length();
  }
  char *copy(char *to, size_t size = -1, size_t offset = 0) const
  {
    if (size == -1)
    {
      str_.substring(offset).toCharArray(to,(str_.length()-offset));
    }
    else
    {
      str_.substring(offset).toCharArray(to,size);
    }
    return to;
  }
  char operator[](int index) const
  {
    return str_.charAt(index);
  }
  void print(Print &stream) const
  {
    stream.print(str_);
  }
private:
  const String str_;
};

#endif

inline Print &operator <<(Print &stream, const ConstantString &printable)
{ printable.print(stream); return stream; }

#endif
