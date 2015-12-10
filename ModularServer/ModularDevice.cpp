// ----------------------------------------------------------------------------
// ModularDevice.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "ModularDevice.h"


namespace ModularDevice
{
ModularDevice::ModularDevice(Stream &stream) :
  server_(stream)
{
  Parameter& serial_number_parameter = modular_device.createParameter(constants::serial_number_constant_string);
  serial_number_parameter.setRange(constants::serial_number_min,constants::serial_number_max);

#ifdef __AVR__
  Method& get_memory_free_method = createMethod(constants::get_memory_free_method_name);
  get_memory_free_method.attachCallback(getMemoryFreeCallback);
  get_memory_free_method.setReturnTypeLong();
#endif

  Method& reset_defaults_method = createMethod(constants::reset_defaults_method_name);
  reset_defaults_method.attachCallback(resetDefaultsCallback);

  Method& set_serial_number_method = createMethod(constants::set_serial_number_method_name);
  set_serial_number_method.attachCallback(setSerialNumberCallback);
  set_serial_number_method.addParameter(serial_number_parameter);
}

void ModularDevice::addServerStream(Stream &stream)
{
  server_.addServerStream(stream);
}

void ModularDevice::setName(const ConstantString &device_name)
{
  server_.setName(device_name);
}

void ModularDevice::setModelNumber(const unsigned int model_number)
{
  server_.setModelNumber(model_number);
}

void ModularDevice::setFirmwareVersion(const unsigned char firmware_major,const unsigned char firmware_minor,const unsigned char firmware_patch)
{
  server_.setFirmwareVersion(firmware_major,firmware_minor,firmware_patch);
}

Method& ModularDevice::createMethod(const ConstantString &method_name)
{
  return server_.createMethod(method_name);
}

Method& ModularDevice::copyMethod(Method &method,const ConstantString &method_name)
{
  return server_.copyMethod(method,method_name);
}

Parameter& ModularDevice::createParameter(const ConstantString &parameter_name)
{
  return server_.createParameter(parameter_name);
}

Parameter& ModularDevice::copyParameter(Parameter &parameter,const ConstantString &parameter_name)
{
  return server_.copyParameter(parameter,parameter_name);
}

ArduinoJson::JsonVariant ModularDevice::getParameterValue(const ConstantString &parameter_name)
{
  return server_.getParameterValue(parameter_name);
}

void ModularDevice::writeNullToResponse()
{
  server_.writeNullToResponse();
}

void ModularDevice::writeResultKeyToResponse()
{
  server_.writeResultKeyToResponse();
}

void ModularDevice::beginResponseObject()
{
  server_.beginResponseObject();
}

void ModularDevice::endResponseObject()
{
  server_.endResponseObject();
}

void ModularDevice::beginResponseArray()
{
  server_.beginResponseArray();
}

void ModularDevice::endResponseArray()
{
  server_.endResponseArray();
}

void ModularDevice::startServer()
{
  server_.startServer();
}

void ModularDevice::stopServer()
{
  server_.stopServer();
}

void ModularDevice::handleServerRequests()
{
  server_.handleRequest();
}

void ModularDevice::resetDefaults()
{
  server_.resetDefaults();
}

void ModularDevice::setSerialNumber(const unsigned int serial_number)
{
  server_.setSerialNumber(serial_number);
}
}

ModularDevice::ModularDevice modular_device(Serial);

#ifdef __AVR__
void ModularDevice::getMemoryFreeCallback()
{
  modular_device.writeResultToResponse(freeMemory());
}
#endif

void ModularDevice::resetDefaultsCallback()
{
  modular_device.resetDefaults();
}

void ModularDevice::setSerialNumberCallback()
{
  unsigned int serial_number = (long)modular_device.getParameterValue(constants::serial_number_constant_string);
  modular_device.setSerialNumber(serial_number);
}
