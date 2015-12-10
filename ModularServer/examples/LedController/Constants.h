// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "ConstantVariable.h"

namespace constants
{
extern const unsigned char led_pin;
extern const unsigned int baudrate;

extern const unsigned int model_number;

extern const unsigned char firmware_major;
extern const unsigned char firmware_minor;
extern const unsigned char firmware_patch;

extern HardwareSerial& serial2;
extern const unsigned char serial2_rx_pin;

extern const double duration_min;
extern const double duration_max;
extern const long count_min;
extern const long count_max;

extern ConstantString device_name;

extern ConstantString duration_on_parameter_name;
extern ConstantString duration_off_parameter_name;
extern ConstantString count_parameter_name;
extern ConstantString seconds_unit;

extern ConstantString led_on_method_name;
extern ConstantString led_off_method_name;
extern ConstantString get_led_pin_method_name;
extern ConstantString blink_led_method_name;
}
#endif
