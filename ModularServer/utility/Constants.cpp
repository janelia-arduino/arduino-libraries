// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Constants.h"

namespace ModularDevice
{
namespace constants
{
const unsigned char method_count_max = 24;

const unsigned char eeprom_initialized_value = 123;

const unsigned int serial_number_min = 0;
const unsigned int serial_number_max = 65535;
const unsigned int serial_number_default = 0;

CONSTANT_STRING(empty_constant_string,"");
CONSTANT_STRING(get_device_info_method_name,"getDeviceInfo");
CONSTANT_STRING(get_method_ids_method_name,"getMethodIds");
CONSTANT_STRING(get_response_codes_method_name,"getResponseCodes");
CONSTANT_STRING(get_parameters_method_name,"getParameters");
CONSTANT_STRING(help_method_name,"?");
CONSTANT_STRING(verbose_help_method_name,"??");
CONSTANT_STRING(object_request_error_message,"JSON object requests not supported. Must use compact JSON array format for requests.");
CONSTANT_STRING(request_too_long_error_message,"Request length too long.");
CONSTANT_STRING(array_parse_error_message,"Parsing JSON array request failed! Could be invalid JSON or too many tokens.");
CONSTANT_STRING(eeprom_initialized_saved_variable_name,"eeprom_initialized");
CONSTANT_STRING(parameter_error_preamble_message,"Parameter value out of range: ");
CONSTANT_STRING(array_parameter_error_preamble_message,"Array parameter element value out of range: ");
CONSTANT_STRING(status_constant_string,"status");
CONSTANT_STRING(error_message_constant_string,"error_message");
CONSTANT_STRING(name_constant_string,"name");
CONSTANT_STRING(type_constant_string,"type");
CONSTANT_STRING(units_constant_string,"units");
CONSTANT_STRING(result_constant_string,"result");
CONSTANT_STRING(result_type_constant_string,"result_type");
CONSTANT_STRING(array_element_type_constant_string,"array_element_type");
CONSTANT_STRING(received_request_constant_string,"received_request");
CONSTANT_STRING(method_id_constant_string,"method_id");
CONSTANT_STRING(method_constant_string,"method");
CONSTANT_STRING(methods_constant_string,"methods");
CONSTANT_STRING(method_info_constant_string,"method_info");
CONSTANT_STRING(parameter_info_constant_string,"parameter_info");
CONSTANT_STRING(parameters_constant_string,"parameters");
CONSTANT_STRING(unknown_method_constant_string,"Unknown method.");
CONSTANT_STRING(unknown_parameter_constant_string,"Unknown parameter.");
CONSTANT_STRING(min_constant_string,"min");
CONSTANT_STRING(max_constant_string,"max");
CONSTANT_STRING(model_number_constant_string,"model_number");
CONSTANT_STRING(serial_number_constant_string,"serial_number");
CONSTANT_STRING(firmware_version_constant_string,"firmware_version");
CONSTANT_STRING(major_constant_string,"major");
CONSTANT_STRING(minor_constant_string,"minor");
CONSTANT_STRING(patch_constant_string,"patch");
CONSTANT_STRING(response_success_constant_string,"response_success");
CONSTANT_STRING(response_error_constant_string,"response_error");
CONSTANT_STRING(device_info_constant_string,"device_info");
CONSTANT_STRING(incorrect_parameter_number_constant_string,"Incorrect number of parameters. ")
CONSTANT_STRING(invalid_json_object_constant_string," is not a valid JSON object.")
CONSTANT_STRING(invalid_json_array_constant_string," is not a valid JSON array.")
CONSTANT_STRING(get_memory_free_method_name,"getMemoryFree");
CONSTANT_STRING(reset_defaults_method_name,"resetDefaults");
CONSTANT_STRING(set_serial_number_method_name,"setSerialNumber");
}
}
