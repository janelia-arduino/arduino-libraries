// ----------------------------------------------------------------------------
// MultiArray.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "MultiArray.h"

MultiArray::MultiArray()
{
  int x_array[constants::X_SIZE] = {1,2,3};
  x_.fill(x_array);
  int y_array[constants::Y_SIZE] = {4,5,6,7};
  y_.fill(y_array);
  int z_array[constants::Z_SIZE] = {8,9,10,11,12};
  z_.fill(z_array);
}

void MultiArray::print()
{
  Serial << "x:" << endl;
  Serial << "{";
  for (int i=0; i<constants::X_SIZE; i++)
  {
    if (i != 0)
    {
      Serial << ",";
    }
    Serial << x_[i];
  }
  Serial << "}" << endl;

  Serial << "y:" << endl;
  Serial << "{";
  for (int i=0; i<constants::Y_SIZE; i++)
  {
    if (i != 0)
    {
      Serial << ",";
    }
    Serial << y_[i];
  }
  Serial << "}" << endl;

  Serial << "z:" << endl;
  Serial << "{";
  for (int i=0; i<constants::Z_SIZE; i++)
  {
    if (i != 0)
    {
      Serial << ",";
    }
    Serial << z_[i];
  }
  Serial << "}" << endl;
}
