// ----------------------------------------------------------------------------
// IndexedSetDefinitions.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef INDEXED_SET_DEFINITIONS_H
#define INDEXED_SET_DEFINITIONS_H


template <typename T, int max_size_>
IndexedSet<T,max_size_>::IndexedSet()
{
  clear();
}

template <typename T, int max_size_>
T& IndexedSet<T, max_size_>::operator[](const int i)
{
  if ((i >= 0) && !available_[i])
  {
    return values_[i];
  }
}

template <typename T, int max_size_>
T& IndexedSet<T, max_size_>::at(const int i)
{
  if ((i >= 0) && !available_[i])
  {
    return values_.at(i);
  }
}

template <typename T, int max_size_>
void IndexedSet<T, max_size_>::clear()
{
  size_ = 0;
  for (int i=0;i<max_size_;++i)
  {
    available_[i] = true;
  }
}

template <typename T, int max_size_>
int IndexedSet<T, max_size_>::findIndex(const T &value)
{
  bool exists = false;
  int index = -1;
  while (!exists && (++index < max_size_))
  {
    exists = !available_[index] && (value == values_[index]);
  }
  if (exists)
  {
    return index;
  }
  return -1;
}

template <typename T, int max_size_>
int IndexedSet<T, max_size_>::add(const T &value)
{
  int index = findIndex(value);
  if (index >= 0)
  {
    return index;
  }
  if (size_ < max_size_)
  {
    bool found_available = false;
    int index = -1;
    while (!found_available && (++index < max_size_))
    {
      found_available = available_[index];
    }
    if (found_available)
    {
      values_[index] = value;
      available_[index] = false;
      ++size_;
      return index;
    }
  }
  return -1;
}

template <typename T, int max_size_>
void IndexedSet<T, max_size_>::removeUsingIndex(const int index)
{
  if (!available_[index])
  {
    available_[index] = true;
    --size_;
  }
}

template <typename T, int max_size_>
void IndexedSet<T, max_size_>::removeUsingValue(const T &value)
{
  int index = findIndex(value);
  if (index >= 0)
  {
    available_[index] = true;
    --size_;
  }
}

template <typename T, int max_size_>
bool IndexedSet<T, max_size_>::indexHasValue(const int index)
{
  return !available_[index];
}

template <typename T, int max_size_>
int IndexedSet<T, max_size_>::size()
{
  return size_;
}

template <typename T, int max_size_>
int IndexedSet<T, max_size_>::max_size()
{
  return max_size_;
}

template <typename T, int max_size_>
bool IndexedSet<T, max_size_>::empty()
{
  return size_ == 0;
}

template <typename T, int max_size_>
bool IndexedSet<T, max_size_>::full()
{
  return size_ == max_size_;
}

#endif
