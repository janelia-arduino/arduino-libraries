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

  // Device Info
  modular_device.setName(constants::device_name);
  modular_device.setModelNumber(constants::model_number);
  modular_device.setFirmwareVersion(constants::firmware_major,constants::firmware_minor,constants::firmware_patch);

  // Add Server Streams

  // Saved Variables

  // Parameters

  // Methods

  // Setup Streams
  Serial.begin(constants::baudrate);

  // Start ModularDevice Server
  modular_device.startServer();
}

void Controller::update()
{
  modular_device.handleServerRequests();
}

Controller controller;
