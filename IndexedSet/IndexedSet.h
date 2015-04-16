// ----------------------------------------------------------------------------
// IndexedSet.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef INDEXED_SET_H
#define INDEXED_SET_H
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Array.h"


template <typename T, int max_size_>
class IndexedSet
{
public:
  IndexedSet();
  virtual T& operator[](const int i);
  virtual T& at(const int i);
  virtual void clear();
  virtual int findIndex(const T &value);
  virtual int add(const T &value);
  virtual void removeUsingIndex(const int index);
  virtual void removeUsingValue(const T &value);
  virtual bool indexHasValue(const int index);
  virtual int size();
  virtual int max_size();
  virtual bool empty();
  virtual bool full();

private:
  Array<T,max_size_> values_;
  Array<bool,max_size_> available_;
  int size_;
};
#include "IndexedSetDefinitions.h"

#endif
