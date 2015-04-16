// ----------------------------------------------------------------------------
// IndexedContainer.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef INDEXED_CONTAINER_H
#define INDEXED_CONTAINER_H
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Array.h"


template <typename T, int max_size_>
class IndexedContainer
{
public:
  IndexedContainer();
  virtual T& operator[](const int i);
  virtual T& at(const int i);
  virtual void clear();
  virtual int add(const T &value);
  virtual void remove(const int index);
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
#include "IndexedContainerDefinitions.h"

#endif
