// ----------------------------------------------------------------------------
// BetterMap.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "BetterMap.h"

long betterMap(long x, long in_min, long in_max, long out_min, long out_max)
{
  long mapped_x = map(x,in_min,(in_max+1),out_min,(out_max+1));
  return constrain(mapped_x,out_min,out_max);
}

