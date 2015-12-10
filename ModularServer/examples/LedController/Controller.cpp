// ----------------------------------------------------------------------------
// Controller.cpp
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Controller.h"


Controller::Controller()
{
}

void Controller::setup()
{
  // Pin Setup
  pinMode(constants::led_pin, OUTPUT);
  pinMode(constants::serial2_rx_pin,INPUT);
  digitalWrite(constants::serial2_rx_pin,HIGH);

  // Device Info
  modular_device.setName(constants::device_name);
  modular_device.setModelNumber(constants::model_number);
  modular_device.setFirmwareVersion(constants::firmware_major,constants::firmware_minor,constants::firmware_patch);

  // Add Server Streams
  modular_device.addServerStream(constants::serial2);

  // Saved Variables

  // Parameters
  ModularDevice::Parameter& duration_on_parameter = modular_device.createParameter(constants::duration_on_parameter_name);
  duration_on_parameter.setUnits(constants::seconds_unit);
  duration_on_parameter.setRange(constants::duration_min,constants::duration_max);
  ModularDevice::Parameter& duration_off_parameter = modular_device.copyParameter(duration_on_parameter,constants::duration_off_parameter_name);
  ModularDevice::Parameter& count_parameter = modular_device.createParameter(constants::count_parameter_name);
  count_parameter.setRange(constants::count_min,constants::count_max);

  // Methods
  ModularDevice::Method& led_on_method = modular_device.createMethod(constants::led_on_method_name);
  led_on_method.attachCallback(callbacks::setLedOnCallback);

  ModularDevice::Method& led_off_method = modular_device.createMethod(constants::led_off_method_name);
  led_off_method.attachCallback(callbacks::setLedOffCallback);

  ModularDevice::Method& get_led_pin_method = modular_device.createMethod(constants::get_led_pin_method_name);
  get_led_pin_method.attachCallback(callbacks::getLedPinCallback);
  get_led_pin_method.setReturnTypeLong();

  ModularDevice::Method& blink_led_method = modular_device.createMethod(constants::blink_led_method_name);
  blink_led_method.attachCallback(callbacks::blinkLedCallback);
  blink_led_method.addParameter(duration_on_parameter);
  blink_led_method.addParameter(duration_off_parameter);
  blink_led_method.addParameter(count_parameter);

  // Setup Streams
  Serial.begin(constants::baudrate);
  constants::serial2.begin(constants::baudrate);

  // Start ModularDevice Server
  modular_device.startServer();
}

void Controller::update()
{
  modular_device.handleServerRequests();
  non_block_blink.update();
}

Controller controller;
