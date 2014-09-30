// ----------------------------------------------------------------------------
// LinearSensorArrayImage.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "LinearSensorArrayImage.h"


//---------- constructor ----------------------------------------------------

LinearSensorArrayImage::LinearSensorArrayImage()
{
}

LinearSensorArrayImage::LinearSensorArrayImage(int sensor_count, int pixel_per_sensor_count) :
  sensor_count_(sensor_count),
  pixel_per_sensor_count_(pixel_per_sensor_count)
{
  // Set up data sizes. (sensor_count x pixel_per_sensor_count)
  data_.resize(sensor_count_);
  for (int s = 0; s < sensor_count_; ++s)
  {
    data_[s].resize(pixel_per_sensor_count_);
  }
}

//---------- public ----------------------------------------------------

int LinearSensorArrayImage::getPixel(int sensor, int pixel)
{
  return data_[sensor][pixel];
}

bool LinearSensorArrayImage::setPixel(int sensor, int pixel, int value)
{
  if ((sensor < sensor_count_) && (pixel < pixel_per_sensor_count_))
  {
    data_[sensor][pixel] = value;
    return true;
  }
  else
  {
    return false;
  }
}

int LinearSensorArrayImage::getSensorCount()
{
  return sensor_count_;
}

int LinearSensorArrayImage::getPixelPerSensorCount()
{
  return pixel_per_sensor_count_;
}
