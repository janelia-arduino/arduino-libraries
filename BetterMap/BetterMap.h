// ----------------------------------------------------------------------------
// BetterMap.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef BETTER_MAP_H
#define BETTER_MAP_H
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

long betterMap(long x, long in_min, long in_max, long out_min, long out_max);

#endif
