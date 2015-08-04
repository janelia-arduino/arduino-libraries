// ----------------------------------------------------------------------------
// FilterSmoothDefinitions.h
//
//
// Authors:
// Paul Badger
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef FILTER_SMOOTH_DEFINITIONS_H
#define FILTER_SMOOTH_DEFINITIONS_H


template <uint8_t sample_count_>
FilterSmooth<sample_count_>::FilterSmooth()
{
  for (int i=0;i<sample_count_;++i)
  {
    raw_values_[i] = 0;
  }
  index_ = 0;
  total_ = 0;
}

template <uint8_t sample_count_>
void FilterSmooth<sample_count_>::addSample(const int &value)
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    total_ -= raw_values_[index_];
    raw_values_[index_] = value;
    total_ += value;
  }
  index_ = (index_ + 1) % sample_count_;
}

template <uint8_t sample_count_>
int FilterSmooth<sample_count_>::getFilteredValue()
{
  int filtered_value = 0;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    filtered_value = total_/sample_count_;
  }
  return filtered_value;
}

#endif
