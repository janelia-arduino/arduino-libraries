// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef _MODULAR_DEVICE_CONSTANTS_H_
#define _MODULAR_DEVICE_CONSTANTS_H_
#include "ConstantVariable.h"


namespace ModularDevice
{
namespace constants
{
enum{METHOD_COUNT_MAX=40}; //9 used internally
enum{PARAMETER_COUNT_MAX=17}; // 1 used internally
enum{SAVED_VARIABLE_COUNT_MAX=12}; // 2 used internally

enum{SERVER_STREAM_COUNT_MAX=4};

enum{STRING_LENGTH_REQUEST=257};
enum{STRING_LENGTH_ERROR=257};
enum{STRING_LENGTH_DEVICE_NAME=32};
enum{STRING_LENGTH_PARAMETER_NAME=24};
enum{STRING_LENGTH_PARAMETER_UNITS=8};
enum{STRING_LENGTH_PARAMETER_COUNT=8};
enum{STRING_LENGTH_METHOD_NAME=32};

enum {JSON_TOKEN_MAX=32};
enum {METHOD_PARAMETER_COUNT_MAX=6};

union NumberType
{
  long l;
  double d;
};

extern const unsigned char method_count_max;

extern const unsigned char eeprom_initialized_value;

extern const unsigned int serial_number_min;
extern const unsigned int serial_number_max;
extern const unsigned int serial_number_default;

extern ConstantString empty_constant_string;
extern ConstantString get_device_info_method_name;
extern ConstantString get_method_ids_method_name;
extern ConstantString get_response_codes_method_name;
extern ConstantString get_parameters_method_name;
extern ConstantString help_method_name;
extern ConstantString verbose_help_method_name;
extern ConstantString object_request_error_message;
extern ConstantString request_too_long_error_message;
extern ConstantString array_parse_error_message;
extern ConstantString eeprom_initialized_saved_variable_name;
extern ConstantString parameter_error_preamble_message;
extern ConstantString array_parameter_error_preamble_message;
extern ConstantString status_constant_string;
extern ConstantString error_message_constant_string;
extern ConstantString name_constant_string;
extern ConstantString type_constant_string;
extern ConstantString units_constant_string;
extern ConstantString result_constant_string;
extern ConstantString result_type_constant_string;
extern ConstantString array_element_type_constant_string;
extern ConstantString received_request_constant_string;
extern ConstantString method_id_constant_string;
extern ConstantString method_constant_string;
extern ConstantString methods_constant_string;
extern ConstantString method_info_constant_string;
extern ConstantString parameter_info_constant_string;
extern ConstantString parameters_constant_string;
extern ConstantString unknown_method_constant_string;
extern ConstantString unknown_parameter_constant_string;
extern ConstantString min_constant_string;
extern ConstantString max_constant_string;
extern ConstantString model_number_constant_string;
extern ConstantString serial_number_constant_string;
extern ConstantString firmware_version_constant_string;
extern ConstantString major_constant_string;
extern ConstantString minor_constant_string;
extern ConstantString patch_constant_string;
extern ConstantString response_success_constant_string;
extern ConstantString response_error_constant_string;
extern ConstantString device_info_constant_string;
extern ConstantString incorrect_parameter_number_constant_string;
extern ConstantString invalid_json_object_constant_string;
extern ConstantString invalid_json_array_constant_string;
extern ConstantString get_memory_free_method_name;
extern ConstantString reset_defaults_method_name;
extern ConstantString set_serial_number_method_name;
extern ConstantString memory_free_constant_string;
}
}
#endif
