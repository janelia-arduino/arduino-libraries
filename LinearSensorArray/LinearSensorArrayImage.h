// ----------------------------------------------------------------------------
// LinearSensorArrayImage.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------

#ifndef LINEAR_SENSOR_ARRAY_IMAGE_H
#define LINEAR_SENSOR_ARRAY_IMAGE_H

#include <StandardCplusplus.h>
#include <vector>

class LinearSensorArrayImage
{
public:
  LinearSensorArrayImage();
  LinearSensorArrayImage(int sensor_count, int pixel_per_sensor_count);

  int getPixel(int sensor, int pixel);
  bool setPixel(int sensor, int pixel, int value);
  int getSensorCount();
  int getPixelPerSensorCount();

private:
  int sensor_count_;
  int pixel_per_sensor_count_;
  std::vector<std::vector<int> > data_;

};

#endif // LINEAR_SENSOR_ARRAY_IMAGE_H
