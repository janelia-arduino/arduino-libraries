// ----------------------------------------------------------------------------
// Array.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef ARRAY_H
#define ARRAY_H
#define __ASSERT_USE_STDERR
#include <assert.h>


// handle diagnostic informations given by assertion and abort program execution:
void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp)
{
  // transmit diagnostic informations through serial link.
  // Serial.println(__func);
  // Serial.println(__file);
  // Serial.println(__lineno, DEC);
  // Serial.println(__sexp);
  Serial.println("Attempted to access out of bounds Array element!");
  Serial.println("Check indicies or increase Array size.");
  Serial.flush();
  // abort program execution.
  abort();
}

template <typename T, unsigned int size>
class Array
{
public:
  Array();
  Array(const T &value);
  Array(T values[size]);
  T& operator[](const unsigned int i);

private:
  T values_[size];
};

template <typename T, unsigned int size>
Array<T,size>::Array()
{}

template <typename T, unsigned int size>
Array<T,size>::Array(const T &value)
{
  for (unsigned int i=0; i<size; i++)
  {
    values_[i] = value;
  }
}

template <typename T, unsigned int size>
Array<T, size>::Array(T values[size])
{
  memcpy((void*) values_, (void*) values, size*sizeof(T));
}

template <typename T, unsigned int size>
T& Array<T, size>::operator[](const unsigned int i)
{
  assert((i>=0) && (i<size));
  if ((i>=0) && (i<size))
  {
    return values_[i];
  }
  else
  {
    T dummy;
    return dummy;
  }
}

#endif
