// ----------------------------------------------------------------------------
// ConstantVariables.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef CONSTANT_VARIABLES_H
#define CONSTANT_VARIABLES_H
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#ifdef __AVR__
#include "Flash.h"

// Use these macros to define your flash-based data structures
// Example: CONSTANT_STRING(str, "Four score and seven years ago");
#define CONSTANT_STRING(name, value) \
static const char name##_flash[] PROGMEM = value; \
ConstantString name(name##_flash);

class ConstantString : public _FLASH_STRING
{
public:
  ConstantString(const char PROGMEM *arr) : _FLASH_STRING(arr){};
};

inline Print &operator <<(Print &stream, const ConstantString &printable)
{ printable.print(stream); return stream; }

#else

// Use these macros to define your flash-based data structures
// Example: CONSTANT_STRING(str, "Four score and seven years ago");
#define CONSTANT_STRING(name, value) \
static const char name##_const[] = value; \
ConstantString name(name##_const);

class ConstantString : public String
{
public:
  ConstantString(const char *arr) : String(arr){};
  void copy(const char* arr) {String::copy(arr,String(arr).length());}
};

#endif

#endif
