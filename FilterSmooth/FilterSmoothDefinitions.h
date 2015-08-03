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
  index_ = 0;
}

template <uint8_t sample_count_>
void FilterSmooth<sample_count_>::addSample(const int &value)
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    raw_values_[index_] = value;
  }
  index_ = (index_ + 1) % sample_count_;
}

template <uint8_t sample_count_>
int FilterSmooth<sample_count_>::getFilteredValue()
{
  long total = 0;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    for (int i=0; i<sample_count_; ++i)
    {
      total += raw_values_[i];
    }
  }
  return total/sample_count_;
}

#endif
