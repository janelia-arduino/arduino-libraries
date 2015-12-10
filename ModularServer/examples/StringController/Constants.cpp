// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace constants
{
const unsigned int baudrate = 9600;

const unsigned int model_number = 1002;

// Use semantic versioning http://semver.org/
const unsigned char firmware_major = 0;
const unsigned char firmware_minor = 1;
const unsigned char firmware_patch = 0;

const int count_min = 1;
const int count_max = 100;

const int starting_chars_count_min = 1;
const int starting_chars_count_max = 10;
const int starting_chars_count_default = 2;

const int index_array_element_min = 0;
const int index_array_element_max = 10;

CONSTANT_STRING(index_error,"Invalid index.");

CONSTANT_STRING(device_name,"string_controller");

CONSTANT_STRING(string_parameter_name,"string");
CONSTANT_STRING(string2_parameter_name,"string2");
CONSTANT_STRING(count_parameter_name,"count");
CONSTANT_STRING(index_array_parameter_name,"index_array");
CONSTANT_STRING(double_echo_parameter_name,"double_echo");
CONSTANT_STRING(starting_chars_count_name,"starting_chars_count");

CONSTANT_STRING(echo_method_name,"echo");
CONSTANT_STRING(length_method_name,"length");
CONSTANT_STRING(starts_with_method_name,"startsWith");
CONSTANT_STRING(repeat_method_name,"repeat");
CONSTANT_STRING(chars_at_method_name,"charsAt");
CONSTANT_STRING(starting_chars_method_name,"startingChars");
CONSTANT_STRING(set_starting_chars_count_method_name,"setStartingCharsCount");
CONSTANT_STRING(get_starting_chars_count_method_name,"getStartingCharsCount");
CONSTANT_STRING(set_stored_string_method_name,"setStoredString");
CONSTANT_STRING(get_stored_string_method_name,"getStoredString");
}
