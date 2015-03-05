// ----------------------------------------------------------------------------
// Array.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef ARRAY_H
#define ARRAY_H
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#define __ASSERT_USE_STDERR
#include <assert.h>


// handle diagnostic informations given by assertion and abort program execution:
void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp);

template <typename T, unsigned int size>
class Array
{
public:
  Array();
  Array(const T &value);
  Array(T values[size]);
  T& operator[](const unsigned int i);
  T& at(const unsigned int i);
  void fill(const T &value);
  void fill(T values[size]);

private:
  T values_[size];
};

template <typename T, unsigned int size>
Array<T,size>::Array()
{}

template <typename T, unsigned int size>
Array<T,size>::Array(const T &value)
{
  fill(value);
}

template <typename T, unsigned int size>
Array<T, size>::Array(T values[size])
{
  fill(values);
}

template <typename T, unsigned int size>
T& Array<T, size>::operator[](const unsigned int i)
{
  return values_[i];
}

template <typename T, unsigned int size>
T& Array<T, size>::at(const unsigned int i)
{
  assert((i>=0) && (i<size));
  return values_[i];
}

template <typename T, unsigned int size>
void Array<T, size>::fill(const T &value)
{
  for (unsigned int i=0; i<size; i++)
  {
    values_[i] = value;
  }
}

template <typename T, unsigned int size>
void Array<T, size>::fill(T values[size])
{
  memcpy((void*) values_, (void*) values, size*sizeof(T));
}

#endif
